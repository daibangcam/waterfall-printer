/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: com.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 05-Dec-13
 *	Description	    : Application layer
 *                      - Used for communicate with user/developer over RF
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "com.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/


/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/
BOOL COM_FrameIsReady;
COMStruct COM_Frame;


/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     COM_Init     
 * @brief  Communication initialization
 * @param  None
 * @retval None
*******************************************************************************/
void COM_Init(void)
{
    COM_BufferReset();
}

/*******************************************************************************
 * @fn     COM_BufferReset     
 * @brief  Reset MEM buffer
 * @param  None
 * @retval None
*******************************************************************************/
void COM_BufferReset(void)
{
    uint32_t i;
    
    for (i = 0; i < PC_USART_DMA_RX_BUF_SIZE; i++)
    {
        PC_USART_DMA_RxBuf[i] = 0; // reset buffer
    }
    DMA_Cmd(PC_USART_RX_DMA_CHANNEL, DISABLE);
    PC_USART_RX_DMA_CHANNEL->CNDTR = PC_USART_DMA_RX_BUF_SIZE;
    DMA_Cmd(PC_USART_RX_DMA_CHANNEL, ENABLE);
    
    COM_Frame.state = COM_WAITING_HEADER;
    COM_Frame.len = 0;   
    COM_Frame.cmd = COM_CMD_NULL;
    COM_Frame.timer = 0;    
}

/*******************************************************************************
 * @fn     COM_BufferIsEmpty     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
BOOL COM_BufferIsEmpty(void)
{
    if (PC_USART_RX_DMA_CHANNEL->CNDTR == PC_USART_DMA_RX_BUF_SIZE)
    {
        return FALSE;
    }
    return TRUE;
}


/*******************************************************************************
 * @fn     COM_SetReadInt     
 * @brief  
 * @param  pf: function to check the frame in time interrupt
 * @param: b
 *          @TRUE: Setting the system checking the frame by interrupt (Ex: in run mode)
 *                 Flag COM_FrameIsReady is set if the frame is ready.
 *          @TRUE: Setting the system checking the frame by polling (Ex: in interaction mode)
 *                 Read the function COM_ReadFrame
 * @retval None
*******************************************************************************/
void COM_SetReadInt(BOOL b)
{
    TIM_REF_SetCallback(COM_ReadFrame, b);
}


/*******************************************************************************
 * @fn     COM_ReadFrame     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
BOOL COM_ReadFrame(void)
{
    static BOOL enTim = FALSE;
    uint32_t len;
    BOOL res = FALSE;

    len = PC_USART_DMA_RX_BUF_SIZE - PC_USART_RX_DMA_CHANNEL->CNDTR;    
    if ((len) && (enTim == FALSE))
    {
        enTim = TRUE;
        TIM_REF_Tick1ms = 0;
    }
    switch (COM_Frame.state)
    {
        case COM_WAITING_HEADER:
            if (len >= COM_LEN_MIN)
            {
                if ((PC_USART_DMA_RxBuf[0] == COM_FRAME_STX) &&
                    (PC_USART_DMA_RxBuf[1] == COM_BKW_ID) &&
                    ((PC_USART_DMA_RxBuf[2] != 0) ||
                     (PC_USART_DMA_RxBuf[3] != 0)))
                {
                    // Valid header
                    COM_Frame.len = PC_USART_DMA_RxBuf[2] * 256 + PC_USART_DMA_RxBuf[3];
                    COM_Frame.cmd = (COM_CMD)PC_USART_DMA_RxBuf[4];
                    COM_Frame.state = COM_WAITING_DATA;
                }
                else
                {
                    // Invalid frame: reset buffer
                    TIM_REF_Tick1ms = COM_TIME_OUT;
                }
            }
            break;
        case COM_WAITING_DATA:
            if (len >= COM_Frame.len)
            {
                if (PC_USART_DMA_RxBuf[COM_Frame.len - 1] == COM_FRAME_ETX) 
                {
                    // Note: check CRC
                    // Valid frame
                    res = TRUE;
                    COM_Frame.pData = &PC_USART_DMA_RxBuf[5];
                    TIM_REF_Tick1ms = 0;
                    enTim = FALSE;
                    //COM_SetReadInt(FALSE);
                }
                else
                {
                    // Invalid frame --> Reset buffer
                    TIM_REF_Tick1ms = COM_TIME_OUT;
                }
            }
            else
            {
                //COM_Frame.timer++;
            }
            break;
        default:
            COM_Frame.state = COM_WAITING_HEADER;
            break;
    }
    
    if(enTim)
    {
        if (TIM_REF_Tick1ms >= COM_TIME_OUT)
        {
            COM_BufferReset();
            enTim = FALSE;
        }
    }
    
    COM_FrameIsReady = res;
    return res;
}

/*******************************************************************************
 * @fn     COM_Response     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
void COM_Response(COM_RES r)
{
    uint8_t cOK[4] = {0x0A,'T','0',0x0D};
    switch (r)
    {
        case COM_RES_OK:
            PC_USART_WriteBytes(&cOK[0], 4);
            break;
        default:
            break;
        
    }
}

/********************************************************************************
* 					            PRIVATE FUNCTIONS
********************************************************************************/


