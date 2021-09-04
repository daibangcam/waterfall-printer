/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: valve.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 04-Aug-13
 *	Description	    : Middle layer
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "valve.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/
uint8_t VALVE_IData[VALVE_ITOTAL];


/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/


/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     VALVE_Init     
 * @brief  Initialise valves to Idle state
 * @param  None
 * @retval None
*******************************************************************************/
void VALVE_Init(void)
{
    uint32_t i;
    
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);    
}

/*******************************************************************************
 * @fn     VALVE_Test     
 * @brief  Testing whether all valves are running well or not
 * @param  None
 * @retval None
*******************************************************************************/
void VALVE_Test(void)
{
//    uint16_t i,j;
		uint16_t i;
    /* Test 1: Turn on all valves in 5s */
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = ION, i++);    
    VALVE_SWrite();
    TIM_REF_DelayTms(5000);   
    DRV_SPI_Do();
    
    /* Test 2: Turn off all valves in 3s */
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
    VALVE_SWrite();
    TIM_REF_DelayTms(3000);   
    DRV_SPI_Do();
	
//	  /* Test 3: Run valves from left to right */
//    for (i = 0; i < VALVE_VTOTAL; i++)
//    {
//        VALVE_VSet(i, VON);
//        VALVE_SWrite();
//        TIM_REF_DelayTms(300);
//        DRV_SPI_Do();
//    }
//    
//		/* Test 4: Turn off all valves in 1s */
//    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
//    VALVE_SWrite();
//    TIM_REF_DelayTms(1000);   
//    DRV_SPI_Do();
		
//		/* Test 5: Run valves from right to left */
//    for (i = VALVE_VTOTAL; i >0; i--)
//    {
//        VALVE_VSet(i, VON);
//        VALVE_SWrite();
//        TIM_REF_DelayTms(200);
//        DRV_SPI_Do();
//    }
//    
//		/* Test 6: Turn off all valves in 2s */
//    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
//    VALVE_SWrite();
//    TIM_REF_DelayTms(2000);   
//    DRV_SPI_Do();
//		
//		/* Test 7: Turn on all valves in 100s */
//    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = ION, i++);    
//    VALVE_SWrite();
//    TIM_REF_DelayTms(100000);   
//    DRV_SPI_Do();
//    
//    /* Test 8: Turn off all valves in 60s */
//    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
//    VALVE_SWrite();
//    TIM_REF_DelayTms(60000);   
//    DRV_SPI_Do();
    
    /* Test 3: Toggle valves in 1s */
    /*
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < VALVE_ITOTAL; VALVE_IData[j] ^= 0xFF, j++);
        VALVE_SWrite();
        TIM_REF_DelayTms(100);
        DRV_SPI_Do();
    }
    */
    
    /* Test 2: Turn off all valves in 1s */
    /*
   for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
    VALVE_SWrite();
    TIM_REF_DelayTms(1000);   
    DRV_SPI_Do();
    */
    
    /* Test 4: Run valves from left to right */
    /*
    for (i = 0; i < VALVE_VTOTAL; i++)
    {
        for (j = 0; j < VALVE_ITOTAL; VALVE_IData[j] = IOFF, j++);
        VALVE_VSet(i, VON);
        VALVE_SWrite();
        TIM_REF_DelayTms(400);
        DRV_SPI_Do();
    }
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
    VALVE_SWrite();
    TIM_REF_DelayTms(2000);   
    DRV_SPI_Do();
    */
    
    /* Test 4: Run valves from left to right */
    /*
    for (j = 0; j < VALVE_ITOTAL; VALVE_IData[j] = IOFF, j++);
    j = 0;
    for (i = 0; i < VALVE_VTOTAL; i++)
    {
        VALVE_VSet(i, VON);
        VALVE_SWrite();
        TIM_REF_DelayTms(100);
        DRV_SPI_Do();
        
        j++;
        if (j >= 8)
        {
            for (j = 0; j < VALVE_ITOTAL; VALVE_IData[j] = IOFF, j++);
            j = 0;
        }
    }
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = IOFF, i++);
    VALVE_SWrite();
    TIM_REF_DelayTms(3000);   
    DRV_SPI_Do();
    */
}

/*******************************************************************************
 * @fn     VALVE_VSet     
 * @brief  Setting a state to each valve
 * @param  vn: valve position (from 0 to VALVE_TOTAL)
 * @param  s: valve state. It can be one of the values {VON, VOFF}
 * @retval None
*******************************************************************************/
void VALVE_VSet(uint16_t vn, uint8_t s)
{
    uint16_t in, bn;
    in = vn / 8;
    bn = vn % 8;
    bn = 7 - bn;
    VALVE_IData[in] &= (~(0x01 << bn)); // reset to 0
    VALVE_IData[in] |= (s << bn); // set to s
}
/*******************************************************************************
 * @fn     VALVE_SetAll     
 * @brief  Setting all valves are in the same state
 * @param  s: the value are setted to data. 
 * @retval None
*******************************************************************************/
void VALVE_ISet(uint16_t in, uint8_t s)
{
    VALVE_IData[in] = s;
}
/*******************************************************************************
 * @fn     VALVE_SSet     
 * @brief  Setting all valves are in the same state
 * @param  *s: pointer to the array that set to data. 
 * @retval None
*******************************************************************************/
void VALVE_SSet(uint8_t *s)
{
    uint8_t i;
    
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = *s++, i++);    
}
/*******************************************************************************
 * @fn     VALVE_Write     
 * @brief  Valve is running
 * @param  None
 * @retval None
*******************************************************************************/
void VALVE_SWrite(void)
{
    DRV_SPI_WriteBytes(VALVE_IData, VALVE_ITOTAL); //VALVE_ITOTAL
    TIM_REF_DelayTms(VALVE_CTRL_DT);  
}
/********************************************************************************
* 					            PRIVATE FUNCTIONS
********************************************************************************/


