/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: app.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 16-Dec-13
 *	Description	    : Application layer
 *                      - Memory application
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "app.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/
uint8_t APP_SptBuf[APP_SPT_BUF_SIZE];
uint8_t APP_ImgBuf[APP_IMG_BUF_SIZE];

/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/
uint8_t *MasterPassword = "2013";


/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     App_Init     
 * @brief  Memory initialization
 * @param  None
 * @retval None
*******************************************************************************/
void APP_Init(void)
{
    
}


/*******************************************************************************
 * @fn     APP_Process     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
BOOL APP_Process(SYS_STATE * ss, BOOL *reloadMem)
{
    uint32_t sec, add;
    uint16_t len;
    BOOL res = FALSE;
    
    DISPStruct conf = {0,0,50,0,CENTER};
    IMG img;
    IMG_LIST lst;

    switch(COM_Frame.cmd)
    {
        case COM_CMD_START_SYSTEM:
            break;
        case COM_CMD_LOGIN_USER_MODE:
             if ((*ss == SS_NULL) && 
                (MEM_Struct.ival == TRUE) &&
                (MEM_Struct.aset.upwd[0] == COM_Frame.pData[0]) &&
                (MEM_Struct.aset.upwd[1] == COM_Frame.pData[1]) &&
                (MEM_Struct.aset.upwd[2] == COM_Frame.pData[2]) &&
                (MEM_Struct.aset.upwd[3] == COM_Frame.pData[3]))
            {
                *ss = SS_INTERACT;
                res = TRUE;
            }
            break;
        case COM_CMD_LOGIN_MASTER_MODE:
             if ((*ss == SS_NULL) && 
                (MasterPassword[0] == COM_Frame.pData[0]) &&
                (MasterPassword[1] == COM_Frame.pData[1]) &&
                (MasterPassword[2] == COM_Frame.pData[2]) &&
                (MasterPassword[3] == COM_Frame.pData[3]))
            {
                *ss = SS_CONFIG;
                res = TRUE;
            }
            break;
        case COM_CMD_RUN_SCRIPT:
            /*
            if (*ss != SS_NULL)
            {
                res = APP_RunScript(&COM_Frame.pData[0]);
            }
            */
            res = APP_RunScript(&COM_Frame.pData[0]);
            break;
        case COM_CMD_DISP_IMG_ARRAY:
            if (*ss != SS_NULL)
            {                  
                conf.dlbefore = COM_Frame.pData[0];
                conf.repeat = COM_Frame.pData[1];
                img = &COM_Frame.pData[2];
                lst = &img;
                WAR_DispImage(lst, 1, conf);
                res = TRUE;
            }
            break;
        case COM_CMD_DOWN_ARRAY_TO_SEC:
            if (*ss == SS_CONFIG)
            {
                sec = (uint32_t)((COM_Frame.pData[0] << 24) + (COM_Frame.pData[1] << 16) + 
                                 (COM_Frame.pData[2] << 8) + (COM_Frame.pData[3]));
                len = COM_Frame.len - 12;
                res = MEM_Write(MEM_AREA_NULL, sec, &COM_Frame.pData[4], &len);
            }
            break;
        case COM_CMD_DOWN_ARRAY_TO_ADD:
            if (*ss == SS_CONFIG)
            {
                add = (uint32_t)((COM_Frame.pData[0] << 8) + (COM_Frame.pData[1]));
                len = COM_Frame.len - 11;
                res = MEM_Write((MEM_AREA)COM_Frame.pData[2], add, &COM_Frame.pData[3], &len);
            }
            break;
        case COM_CMD_RELOAD_MEM:
            if (*ss == SS_CONFIG)
            {
                //res = MEM_Calib();
                res = TRUE;
                *reloadMem = TRUE;
            }
            break;
        case COM_CMD_LOGOUT:
            *ss = SS_NULL;
            res = TRUE;
            break;
        default:
            break;
    }
    COM_BufferReset();
    if (res == TRUE) COM_Response(COM_RES_OK);
    return res;
}

/*******************************************************************************
 * @fn     APP_RunScript     
 * @brief  Run a script
 * @param  
 * @retval BOOL
 *          @FALSE: receive the data, break the loop to process at once
*******************************************************************************/
BOOL APP_RunScript(SPT spt)
{
    uint8_t num_uspt = 0, i = 0, j = 0, k = 0, l = 0;
    USPT uspt;
    uint16_t ind = 0, pos = 0;
    uint16_t add = 0;
    IMG img[WAR_NUM_IMG_MAX];
    IMG_LIST imgList;
    uint16_t len = 0;
    uint8_t * pUspt;
    uint8_t rep;
    BOOL res = TRUE;
    
    num_uspt = spt[0];
    rep = spt[1] + 1; // repeat setting 1 means that system run 2 times
    for (l = 0; l < rep; l++) // repeat the script
    {
        ind = 2; // reset index
        for (i = 0; i < num_uspt; i++) // repeat the unit script
        {
            pUspt = &spt[ind];
            if (pUspt[0] == 0x02)
            {
                uspt.len = pUspt[1];
                uspt.type = pUspt[2];
                uspt.conf.dlafter = pUspt[uspt.len-1];
                uspt.conf.dlrepeat = pUspt[uspt.len-2];
                uspt.conf.dlbefore = pUspt[uspt.len-3];
                uspt.conf.repeat = pUspt[uspt.len-4];
                uspt.conf.align = (DISP_ALGN)pUspt[uspt.len-5];
                
                // image-based uscript
                if (uspt.type == 1) 
                {
                    pos = 0;
                    // Number of image on this unit script
                  
                    k = (uspt.len - 8) / 2;
                    // Load all images
                    for (j = 0; j < k; j++)
                    {
                        add = (uint16_t)((pUspt[3 + 2*j] << 8) + pUspt[4 + 2*j]);
                        len = 0;
                        img[j] = &APP_ImgBuf[pos];
                        MEM_Read(MEM_AREA_IMAGE, add, img[j], &len);
                        pos += len;
                        if (pos >= APP_IMG_BUF_SIZE)
                        {
                            // buffer is full
                            break;
                        }
                    }
                    imgList = &img[0];
                    WAR_DispImage(imgList, j, uspt.conf);
                    
                    // Checking the status of buffer
                    if (COM_FrameIsReady == TRUE)
                    {
                        // break the loop
                        //i = num_uspt;
                        //l = rep;
                        WAR_Write(0, 0, 0, 1); // disable valves
                        COM_FrameIsReady = FALSE;
                        return FALSE;
                    }
                }
            }
            ind += uspt.len;
        }
    }        
    return res;
    
}


/*******************************************************************************
 * @fn     APP_ConfigMode     
 * @brief  BKW system is in configuration mode
 * @param  
 * @retval None
*******************************************************************************/
void APP_ConfigMode(BOOL *reloadMem)
{
    BOOL loopStop = FALSE;
    SYS_STATE stmp = SS_CONFIG;
    
    TIM_REF_Tick10ms = 0; // timeout 10s
    while((loopStop == FALSE) && (TIM_REF_Tick10ms <= 1000))
    {
        if (COM_ReadFrame())
        {
            if (APP_Process(&stmp, reloadMem))
            {
                //COM_Response(COM_RES_OK);
                TIM_REF_Tick10ms = 0;
                if (stmp == SS_NULL)
                {
                    // Logout the system
                    loopStop = TRUE;
                }
            }
            else
            {
                loopStop = TRUE;
            }
        }
        //TIM_REF_Tick10ms = 0;
    }
}

/*******************************************************************************
 * @fn     APP_InteractMode     
 * @brief  BKW system is in interaction mode
 * @param  
 * @retval None
*******************************************************************************/
void APP_InteractMode(void)
{
    BOOL loopStop = FALSE;
    SYS_STATE stmp = SS_INTERACT;
    
    TIM_REF_Tick10ms = 0; // timeout 60s
    while((loopStop == FALSE)) // && (TIM_REF_Tick10ms <= 60000))
    {
        if (COM_ReadFrame())
        {
            if (APP_Process(&stmp, 0))
            {
                TIM_REF_Tick10ms = 0;
                if (stmp == SS_NULL)
                {
                    // Logout the system
                    loopStop = TRUE;
                }
            }
            else
            {
                loopStop = TRUE;
            }
        }
    }
    
}

/*******************************************************************************
 * @fn     APP_BKPMode     
 * @brief  BKW system is running in back up mode
 * @param  
 * @retval None
*******************************************************************************/
void APP_BKPMode(void)
{    
    static uint8_t ind;
    TIM_REF_Tick10ms = 0; //timeout 5s
    while ((ind < WAR_DISP_LIST_NUM) && (TIM_REF_Tick10ms <= 500))
    {
        WAR_DispList[ind++](1000);
    }
    if (ind >= WAR_DISP_LIST_NUM) ind = 0;
}

/*******************************************************************************
 * @fn     APP_RunMode     
 * @brief  BKW system is running in run mode
 * @param  
 * @retval None
*******************************************************************************/
void APP_RunMode(void)
{
    static uint8_t spt_add = 1;
    uint16_t len = 0;
    BOOL res;
    TIM_REF_Tick10ms = 0; //timeout 5s
    //for ( ; ((spt_add <= MEM_Struct.aspt.nspt) && (TIM_REF_Tick10ms <= 500)); spt_add++)
    for ( ; ((spt_add <= MEM_Struct.aspt.nspt) && (res == TRUE)); spt_add++)
    {
        len = MEM_SIZE - 1;
        res = MEM_Read(MEM_AREA_SCRIPT, spt_add, &APP_SptBuf[0], &len); // read 1 sector
        if (res)
        {
            res = APP_RunScript(&APP_SptBuf[0]);
        }
    }
    if (spt_add > MEM_Struct.aspt.nspt) spt_add = 1;
}



/********************************************************************************
* 					            PRIVATE FUNCTIONS
********************************************************************************/


