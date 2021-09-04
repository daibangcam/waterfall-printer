/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: utility.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 16-June-13
 *	Description	    : Some miscellaneous firmware functions
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "utility.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/


/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     Array2Uint     
 * @brief  Convert array of bytes to unsigned integer (32bit)
 * @param  
 * @retval None
*******************************************************************************/
uint32_t Array2Uint32(uint8_t *a)
{
    return (uint32_t)((a[0] << 24) + (a[1] << 16) + (a[2] << 8) + (a[3]));
}


/*******************************************************************************
 * @fn     Int2Str     
 * @brief  Convert integer number to string with iLen is a length of integer part
 *          (length of the string = iLen + 1 since we add the sign of the integer)
 * @param  i: integer number
 * @param  pStr: pointer to string
 * @param  iLen: length of string
 * @retval None
*******************************************************************************/
void Int2Str(int32_t i, uint8_t *pStr, uint32_t iLen)
{
    uint32_t j, ti, ei;
    
    if (i < 0)
    {
        *pStr++ = '-';
        i = -i;
    }     
    else
    {
        *pStr++ = ' ';
    }

    for (j = 0, ei = 1; j < iLen; ei *= 10, j++);
    ti = ((uint32_t)i) % ei;
    
    for (j = 0; j < iLen; j++)
    {
        ei /= 10;
        *pStr++ = (ti / ei) % 10 + 0x30;
    }
}

/*******************************************************************************
 * @fn     DateTime2Str     
 * @brief  Convert DateTime struct to string
 * @param  t: DateTime struct
 * @param  mode: select the string type
 *          This parameter can be one of the following values:
 *          @arg MODE_DAY_DATE_TIME: Sat,22/06/13,22:28:10
 *          @arg MODE_DAY_DATE     : Sat,22/06/13
 *          @arg MODE_TIME         : 22:28:10
 *
 * @param  pStr: return the string
 * @param  l: return the length of string
 * @retval None
*******************************************************************************/
void DateTime2Str(RTCStruct t, uint8_t mode, uint8_t *pStr, uint8_t *l)
{
    uint8_t *day[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    uint8_t dayStr[3]; 
    uint8_t dateStr[8];
    uint8_t timeStr[8];
    uint8_t i;

    /* Day */
    dayStr[0] = day[t.day][0];
    dayStr[1] = day[t.day][1];
    dayStr[2] = day[t.day][2];

    /* Date */
    dateStr[0] = t.date / 10 + 0x30;
    dateStr[1] = t.date % 10 + 0x30;
    dateStr[2] = '/';
    dateStr[3] = t.month / 10 + 0x30;
    dateStr[4] = t.month % 10 + 0x30;   
    dateStr[5] = '/';
    dateStr[6] = t.year / 10 + 0x30;
    dateStr[7] = t.year % 10 + 0x30;   

    /* Time */
    timeStr[0] = t.hour / 10 + 0x30;
    timeStr[1] = t.hour % 10 + 0x30;
    timeStr[2] = ':';
    timeStr[3] = t.min / 10 + 0x30;   
    timeStr[4] = t.min % 10 + 0x30;  
    timeStr[5] = ':';
    timeStr[6] = t.sec / 10 + 0x30;
    timeStr[7] = t.sec % 10 + 0x30;   
    
    *l = 0;
    if (mode == MODE_DAY_DATE_TIME)
    {
        for (i = 0; i < 3; *pStr++ = dayStr[i], i++);
        *pStr++ = ',';
        *l = i + 1;
        for (i = 0; i < 8; *pStr++ = dateStr[i], i++);
        *pStr++ = ',';
        *l = *l + i + 1;
        for (i = 0; i < 8; *pStr++ = timeStr[i], i++);
        *l = *l + i;
    }
    else if (mode == MODE_TIME)
    {
        for (i = 0; i < 8; *pStr++ = timeStr[i], i++);
        *l = *l + i;
    }
        
}

