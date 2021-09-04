/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: mem.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 15-Dec-13
 *	Description	    : Application layer
 *                      - Memory application
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "mem.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/
uint8_t MEM_Buf[MEM_BUF_SIZE];
MEMStruct MEM_Struct;

/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/

/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     MEM_Init     
 * @brief  Memory initialization
 * @param  None
 * @retval None
*******************************************************************************/
BOOL MEM_Init(void)
{
    BOOL loop = TRUE;
    BOOL res = FALSE;
    uint32_t count = 0;
    
    while (loop)
    {
        count++;
        if (count >= 100)
        {
            loop = FALSE;
        }
        if (SD_Init() == SD_TRUE)
        {
            if (SD_ReadConfiguration() == SD_TRUE) 
            {
                res = TRUE;
            }
            loop = FALSE;
        }
        tick_count = 0;
        while(tick_count <= 5); //delay 50ms
        LED_PULSE_Toggle();
    }
    return res;
}

/*******************************************************************************
 * @fn     MEM_Test     
 * @brief  Test the memory
 * @param  None
 * @retval None
*******************************************************************************/
BOOL MEM_Test(void)
{
    /*
    uint16_t l = 0;
    IMG img;
    IMG_LIST imgList;
    DISPStruct dp = {{5},{0},{0},{50}, {CENTER}};
    BOOL res = FALSE;
    
    res = MEM_Read(MEM_AREA_IMAGE, 1, &APP_ImgBuf[0], &l);
    if (res)
    {
        img = &APP_ImgBuf[0];
        imgList = &img;
        WAR_DispImage(imgList, 1, dp);
    }
    return res;
    */
    return TRUE;
}


/*******************************************************************************
 * @fn     MEM_Calib     
 * @brief  Load the calibration in memory
 * @param  None
 * @retval None
*******************************************************************************/
BOOL MEM_Calib(void)
{
    BOOL res = FALSE;   
    uint32_t t;
    uint16_t len;
    
    len = MEM_SIZE;
    MEM_Struct.ival = FALSE;
    /*
     * 1. Load AREA_CALIBRATION Memory (RO)
     */
    if (MEM_Read(MEM_AREA_NULL, CALIB_BASE_SEC_DEF, &MEM_Buf[0], &len))
    {
        res = TRUE;
        if ((MEM_Buf[0] == 'A') && 
            (MEM_Buf[1] == 'C') && (MEM_Buf[2] == 'A') && (MEM_Buf[3] == 'L'))
        {
            t = Array2Uint32(&MEM_Buf[4]);
            if (t > 0) MEM_Struct.aset.bsec = t;
            else res = FALSE;
            
            t = Array2Uint32(&MEM_Buf[8]);
            if (t > 0) MEM_Struct.aspt.bsec = t;
            else res = FALSE;
            
            t = Array2Uint32(&MEM_Buf[12]);
            if (t > 0) MEM_Struct.aimg.bsec = t;
            else res = FALSE;
            
            MEM_Struct.acal.bsec = CALIB_BASE_SEC_DEF;
        }
    }
    
    /*
     * 2. Load AREA_SETTING Memory (RW)
     */
    if (res)
    {
        res = FALSE;
        if (MEM_Read(MEM_AREA_NULL, MEM_Struct.aset.bsec, &MEM_Buf[0], &len))
        {
            if ((MEM_Buf[0] == 'A') && 
                (MEM_Buf[1] == 'S') && (MEM_Buf[2] == 'E') && (MEM_Buf[3] == 'T'))
            {
                MEM_Struct.aset.upwd[0] = MEM_Buf[4];
                MEM_Struct.aset.upwd[1] = MEM_Buf[5];
                MEM_Struct.aset.upwd[2] = MEM_Buf[6];
                MEM_Struct.aset.upwd[3] = MEM_Buf[7];
                MEM_Struct.aset.tvan = (uint16_t)((MEM_Buf[8] << 8) + MEM_Buf[9]);
                res = TRUE;
            }
        }
    }
    
    /*
     * 3. Load AREA_SCRIPT Memory (RW)
     */
    if (res)
    {
        res = FALSE;
        if (MEM_Read(MEM_AREA_NULL, MEM_Struct.aspt.bsec, &MEM_Buf[0], &len))
        {
            if ((MEM_Buf[0] == 'A') && 
                (MEM_Buf[1] == 'S') && (MEM_Buf[2] == 'P') && (MEM_Buf[3] == 'T'))
            {
                MEM_Struct.aspt.nspt = (uint16_t)((MEM_Buf[4] << 8) + MEM_Buf[5]);
                res = TRUE;
            }
        }
    }
    
    /*
     * 4. Load AREA_IMAGE Memory (RO)
     */
    if (res)
    {
        res = FALSE;
        if (MEM_Read(MEM_AREA_NULL, MEM_Struct.aimg.bsec, &MEM_Buf[0], &len))
        {
            if ((MEM_Buf[0] == 'A') && 
                (MEM_Buf[1] == 'I') && (MEM_Buf[2] == 'M') && (MEM_Buf[3] == 'G'))
            {
                MEM_Struct.aimg.nimg = (uint16_t)((MEM_Buf[4] << 8) + MEM_Buf[5]);
                MEM_Struct.aimg.nsec = MEM_Buf[6];
                res = TRUE;                
            }
        }
    }
    
    if (res) MEM_Struct.ival = TRUE;
    return res;
}


/*******************************************************************************
 * @fn     MEM_Write     
 * @brief  Write data to memory
 * @param  area: specific area in memory
 * @param  add: address to write
 * @param  c: pointer to data to write
 * @param  l: length of data
 * @retval None
*******************************************************************************/
BOOL MEM_Write(MEM_AREA area, uint32_t add, uint8_t *c, uint16_t *l)
{
    BOOL res = FALSE;
    uint16_t num_sec = *l / MEM_SIZE;
    uint32_t i, j;
    
    // Calculate the relative address
    switch (area)
    {
        case MEM_AREA_NULL: 
            // obsolute address, no need to convert
            break;
        case MEM_AREA_CALIB:
            break;
        case MEM_AREA_SETTING:
            break;
        case MEM_AREA_SCRIPT:
            add = MEM_Struct.aspt.bsec + add;
            break;
        case MEM_AREA_IMAGE:
            add = MEM_Struct.aimg.bsec + MEM_Struct.aimg.nsec * add;
            break;
        case MEM_AREA_USER:
            break;
        case MEM_AREA_BACKUP:
            break;
        default:
            break;
    }
    
    res = TRUE;
    /*
    * Write to sectors
    */
    for (i = 0; i < num_sec; i++)
    {
        // write to sector
        for (j = 0; j < MEM_SIZE; MEM_Buf[j++] = *c++);
        MEM_Buf[j] = 'V'; // end of sector
        if (SD_WriteBytes(add + i, &MEM_Buf[0]) == SD_FALSE)
        {
            res = FALSE;
        }
        *l -= MEM_SIZE;
    }
    
    // Remaining bytes will be writen to the next sector
    if (*l > 0)
    {        
        for (j = 0; j < *l; MEM_Buf[j++] = *c++); // copy to memory bufer
        for (; j < MEM_SIZE; MEM_Buf[j++] = 0); // padding zeros
        MEM_Buf[j] = 'V'; // end of sector
        if (SD_WriteBytes(add + i, &MEM_Buf[0]) == SD_FALSE) // write to sector
        {
            res = FALSE;
        }
    }
    
    return res;
}


/*******************************************************************************
 * @fn     MEM_Read     
 * @brief  Read data from memory
 * @param  area: specific area in memory
 * @param  add: address to read
 * @param  c: pointer to data to read
 * @param  l: length of data to read. 
 * @retval None
*******************************************************************************/
BOOL MEM_Read(MEM_AREA area, uint32_t add, uint8_t *c, uint16_t *l)
{
    BOOL res = FALSE;
    uint32_t i, j;
    uint16_t len;
    
    switch (area)
    {
        case MEM_AREA_NULL:
            // obsolute address, no need to convert
            break;
        case MEM_AREA_CALIB:
            break;
        case MEM_AREA_SETTING:
            break;
        case MEM_AREA_SCRIPT:
            add = MEM_Struct.aspt.bsec + add;
            break;
        case MEM_AREA_IMAGE:
            add = MEM_Struct.aimg.bsec + MEM_Struct.aimg.nsec * add;
            break;
        case MEM_AREA_USER:
            break;
        case MEM_AREA_BACKUP:
            break;
        default:
            break;
    }
    
    if ((SD_ReadBytes(add, &MEM_Buf[0]) == SD_TRUE) && (MEM_Buf[SECTOR_SIZE-1] == 'V'))
    {
        if (*l == 0)
        {
            *l = (uint16_t)((MEM_Buf[0] << 8) + MEM_Buf[1]);
        }        
        len = *l;
        
        res = TRUE;
        i = 1;
        while(len > MEM_SIZE)
        {
            for (j = 0; j < MEM_SIZE; *c++ = MEM_Buf[j++]);
            len -= MEM_SIZE;
            if ((SD_ReadBytes(add + i, &MEM_Buf[0]) == SD_TRUE) && (MEM_Buf[SECTOR_SIZE-1] == 'V'))
            {
                i++;
            }
            else
            {
                res = FALSE;
                break;
            }
        }
        // Remaining bytes
        for (j = 0; j < len; *c++ = MEM_Buf[j++]); // copy to memory bufer
    }
    return res;
}


/********************************************************************************
* 					            PRIVATE FUNCTIONS
********************************************************************************/


