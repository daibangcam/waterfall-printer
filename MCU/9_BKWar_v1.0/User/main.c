/*****************************************************************************
 *
 * Project: Tranh man nuoc
 * 
 ****************************************************************************/

/*****************************************************************************
 *
 *	Module			: main.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: 28-Dec-2016
 *	Description	    : BKWar Firmware ver 1.0 (Initial version)
 *                      - Updated to version 2.0 with some changes
 *                         + Implement bluetooth protocol
 *                         + ...
 *				
 *	Author			: Ngo Dinh Duy Khanh		
 *				
 *****************************************************************************/
 
 /****************************************************************************
 * 							        IMPORT
 *****************************************************************************/
#include "mcu_board.h"
#include "valve.h"
#include "war.h"
#include "diag.h"
#include "com.h"
#include "app.h"

/****************************************************************************
 * 							        GLOBAL VARIABLES
 *****************************************************************************/
SYS_STATE SystemState;
SYS_STATE SystemNewState;

uint8_t spt_tmp[23] = {2,2,10,1,0,11,0,0,0,0,0,2,12,1,0,11,0,11,0,0,0,0,0};

/*****************************************************************************
* 							        DEFINE
******************************************************************************/
#define _TEST_ONLY_MODE_ 0

/*****************************************************************************
* 					            MAIN PROGRAM
******************************************************************************/
int main(void)
{
    /*
     * Flags to run flow chart
     */
    BOOL MemInitFlag = FALSE;
    BOOL MemLoadCalibFlag = FALSE;
    BOOL MemReloadFlag = FALSE;
    BOOL t = FALSE;
   
    /************************************************************************
    * HARDWARE INIT                                                         *
    *************************************************************************/
	// thiet lap cac ngoai vi 
	/*
	I/O cho led pusel 
	nhan an lua chon che do
	thiet lap thoi gian ngat time
	SPI 
	UART va DMA_RX 
	
	*/
    MCU_BOARD_Init();
		LED_PULSE_Set();
		// chon van va dua ve trang thai khong du lieu
    VALVE_Init();
		// reset du lieu va thiet lap thong so bo nho 
    COM_Init();
    SystemState = SS_INIT;
    SystemNewState = SS_NULL;
    
    
    /************************************************************************
    * INIT & TEST PHASE                                                     *
    *************************************************************************/
    
    #if (_TEST_ONLY_MODE_ == 1)
    {
        /* For testing only */
        while(1)
        {
            APP_BKPMode();
        }
        while(1)
        {
            VALVE_Test(); // Test 1: on, off, ... valves
        }
        while(1)
        {
            if (COM_ReadFrame())
            {
                SystemNewState = SS_NULL;
                APP_Process(&SystemNewState, 0);
            }
        }
    }
    #endif
    

		
		VALVE_Test();
		
//		WAR_Test();
    
//		APP_BKPMode();
//    LED_PULSE_Reset();

		
    /************************************************************************
    * RUNNING PHASE                                                        *
    *************************************************************************/
    
    
    
    while(1)
    {
        t = TRUE;
        if (MemInitFlag == FALSE)
        {
            if (MEM_Init()) // MEM_Init success
            {
                MemInitFlag = TRUE;
                DIAG_Raise(EV_MEM_INIT_SUC);
            }
            else // MEM_Init fail
            {
                t = FALSE;
                MemInitFlag = FALSE;
                DIAG_Raise(EV_MEM_INIT_ERR);           
            }
        }
        
        //if ((t) && (MEM_Calib()) && (MEM_Test())) // Memory initialization + cailbration + testing are all ok
        if ((t) && (MEM_Calib())) // Memory initialization + cailbration + testing are all ok
        {
            MemLoadCalibFlag = TRUE;
            SystemState = SS_RUN;
            DIAG_Raise(EV_MEM_LOAD_CALIB_SUC);
						LED_PULSE_Reset();
        }
        else
        {
            MemLoadCalibFlag = FALSE;
            SystemState = SS_BKP;
            DIAG_Raise(EV_MEM_LOAD_CALIB_ERR); 
						LED_PULSE_Set();					
        }
        
        MemReloadFlag = FALSE;
        while(MemReloadFlag == FALSE)
        {
            
            switch(SystemState)
            {
                case SS_BKP:
                    APP_BKPMode();
                    break;
                case SS_RUN:
                    COM_SetReadInt(TRUE); // go into run mode
                    APP_RunMode();
                    break;
                default:
                    break;
            }
            
            COM_SetReadInt(FALSE);
            SystemNewState = SS_NULL;
            if (COM_ReadFrame())
            if (COM_FrameIsReady == TRUE)
            {
                APP_Process(&SystemNewState, 0);
            }
            
            switch(SystemNewState)
            {
                case SS_CONFIG:
                    if (MemInitFlag)
                    {
                        DIAG_Raise(EV_CONFIG);
                        APP_ConfigMode(&MemReloadFlag);
                    }
                    DIAG_Raise(EV_CONFIG_DONE);
                    break;
                case SS_INTERACT:
                    if (MemLoadCalibFlag)
                    {
                        DIAG_Raise(EV_INTERACT);
                        APP_InteractMode();
                    }
                    DIAG_Raise(EV_INTERACT_DONE);
                    break;
                default:
                    break;
            }
            
        }        
    }
}


