/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: type.h
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 22-June-13
 *	Description	    : Type definition
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
#ifndef __TYPE_H
#define __TYPE_H

/*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include <stdint.h>

/********************************************************************************
* 							        TYPEDEF
********************************************************************************/

typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed int          INT32;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned int        UINT32;

typedef struct
{
    uint8_t day;        /* from 0 (Sun) to 6 (Sat) */
    uint8_t date;       /* from 1 to 31 */
    uint8_t month;      /* from 1 to 12 */
    uint8_t year;       /* from (20)01 to (20)99 */
    uint8_t hour;       /* from 00 to 24 */
    uint8_t min;        /* from 00 to 59 */
    uint8_t sec;        /* from 00 to 59 */
}RTCStruct;

#ifndef BOOL
typedef enum
{
    FALSE = 0,
    TRUE
}BOOL;
#endif /* BOOL */

typedef enum 
{
    EV_MEM_INIT_ERR, /* MSDC can not be initialized */
    EV_MEM_INIT_SUC, /* MSDC is initialized successfully */
    EV_MEM_LOAD_CALIB_SUC,
    EV_MEM_LOAD_CALIB_ERR,
    EV_CONFIG,
    EV_CONFIG_DONE,
    EV_INTERACT,
    EV_INTERACT_DONE,
    EV_COM_ERR, /* The communication with devices is down */
    EV_SS_SWITCH_MODE_CONFIG,
    EV_SS_SWITCH_MODE_RUN,
    EV_SS_SWITCH_MODE_INTERACT
}EVENT;

typedef enum
{
    SS_NULL, /* Null state */ 
    SS_INIT, /* System is in innitialization and testing phase */
    SS_CONFIG, /* Systemm is in develop mode */
    SS_RUN, /* System is running correctly */
    SS_INTERACT, /* System is halted to interact with devices */ 
    SS_BKP /* System is switched to a backup mode in case that sd card is down*/ 
}SYS_STATE;

typedef enum
{
    COM_WAITING_HEADER = (uint8_t)0,
    COM_WAITING_DATA = (uint8_t)1
}COM_STATE;

typedef enum
{
    COM_CMD_NULL               = (uint8_t)0x00,
    COM_CMD_START_SYSTEM       = (uint8_t)0x01,
    COM_CMD_LOGIN_USER_MODE    = (uint8_t)0x02,
    COM_CMD_LOGIN_MASTER_MODE  = (uint8_t)0x03,
    COM_CMD_RUN_SCRIPT         = (uint8_t)0x04,
    COM_CMD_DISP_IMG_ARRAY     = (uint8_t)0x05,
    COM_CMD_DOWN_ARRAY_TO_SEC  = (uint8_t)0x06,
    COM_CMD_DOWN_ARRAY_TO_ADD  = (uint8_t)0x07,
    COM_CMD_RELOAD_MEM         = (uint8_t)0x08,
    COM_CMD_LOGOUT             = (uint8_t)0x09
}COM_CMD;

typedef struct
{    
    COM_STATE state;
    uint16_t len;
    COM_CMD cmd;
    uint8_t timer;
    uint8_t *pData; 
}COMStruct;

typedef enum
{
    COM_RES_OK,
    COM_RES_FAIL
}COM_RES;

typedef enum
{
    MEM_AREA_NULL = (uint8_t)0,
    MEM_AREA_CALIB = (uint8_t)1,
    MEM_AREA_SETTING = (uint8_t)2,
    MEM_AREA_SCRIPT = (uint8_t)3,
    MEM_AREA_IMAGE = (uint8_t)4,
    MEM_AREA_USER = (uint8_t)5,
    MEM_AREA_BACKUP = (uint8_t)6
}MEM_AREA;


typedef struct
{
    uint32_t bsec; // base sector in MSDC of Area Calibration
}MEM_AreaCalibrationStruct;

typedef struct
{
    uint32_t bsec;    // base sector in MSDC of Area Setting    
    uint32_t tvan;    // total valve in current system
    uint8_t  upwd[4]; // user password to connect to the BKW system
}MEM_AreaSettingStruct;

typedef struct
{
    uint8_t  nspt; // number of scripts (serially) in memory
    uint32_t bsec; // base sector in MSDC of Area Script
}MEM_AreaScriptStruct;

typedef struct
{
    uint32_t bsec; // base sector in MSDC of Area Image
    uint16_t nimg; // number of images in memory serially
    uint8_t  nsec; // number of sectors per an image 
}MEM_AreaImageStruct;

typedef struct
{
    MEM_AreaCalibrationStruct acal;
    MEM_AreaSettingStruct aset;
    MEM_AreaScriptStruct aspt;
    MEM_AreaImageStruct aimg;
    BOOL ival;
}MEMStruct;

typedef uint8_t*    IMG; // |NumOfBytes(2bytes)|NumOfCol(2bytes)|Row1(bytes)|Row2|.... 
typedef uint8_t**   IMG_LIST; // [Image1; Image2;...]
typedef struct
{
    uint16_t row;
    uint16_t col;
    uint8_t* pos;
}IMGStruct;

typedef enum
{
    LEFT = (uint8_t)0x00,
    RIGHT = (uint8_t)0x01,
    CENTER = (uint8_t)0x02
}DISP_ALGN;

typedef struct
{
    uint8_t repeat;
    uint8_t dlbefore; // x20ms
    uint8_t dlrepeat; // x20ms
    uint8_t dlafter;  // x20ms 
    DISP_ALGN align;  
}DISPStruct;

typedef struct
{
    uint8_t len;
    uint8_t type;
    DISPStruct conf;
    IMG_LIST imglist;
}USPT;

/*
Script:
--> |NumOfUnitScript(1byte)|UnitScript1|UnitScript2|...|UnitScriptN|
UnitScript:
--> 0x02|LengthScript(1byte)|ScriptType(1byte)|Data(multi-bytes)|RepeatTimes(1byte)|
    DelayBefore(x20ms)(1byte)|DelayRepeat(x20ms)(1byte)|DelayAfter(x20ms)(1byte)|
*/
typedef uint8_t*    SPT; 


// function pointer to check the COM-buffer
// this ensures to check the buffer in HAL but not break the SW Architecture
typedef BOOL (*COM_pFunc)(void); 

/********************************************************************************
* 							        DEFINE
********************************************************************************/

/********************************************************************************
* 					        GLOBAL VARIABLES
********************************************************************************/


/********************************************************************************
* 					        PRIVATE VARIABLES
********************************************************************************/

/********************************************************************************
* 					        PUBLIC FUNCTIONS
********************************************************************************/


#endif /* __TYPE_H */
