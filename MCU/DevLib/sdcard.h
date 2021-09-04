/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: sdcard.h
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 17-June-13
 *	Description	    : MicroSD Card Interface 
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
#ifndef __SDCARD_H
#define __SDCARD_H


/*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "stm32f10x_conf.h"
#include "mcu_board.h"

/********************************************************************************
* 							        TYPEDEF
********************************************************************************/
typedef unsigned char    SD_BOOL;
typedef struct tagCARDCONFIG
{
    uint32_t sectorsize;    /* size (in byte) of each sector, fixed to 512bytes */
    uint32_t sectorcnt;     /* total sector number */  
    uint32_t blocksize;     /* erase block size in unit of sector */     
	uint8_t  ocr[4];		/* OCR */
	uint8_t  cid[16];		/* CID */
	uint8_t  csd[16];		/* CSD */
} CARDCONFIG;

/********************************************************************************
* 							        DEFINE
********************************************************************************/
#define SD_TRUE     1
#define SD_FALSE    0

#ifndef NULL
 #ifdef __cplusplus              // EC++
  #define NULL          0
 #else
  #define NULL          ((void *) 0)
 #endif
#endif


/* Memory card type definitions */
#define CARDTYPE_UNKNOWN        0
#define CARDTYPE_MMC            1   /* MMC */
#define CARDTYPE_SDV1           2   /* V1.x Standard Capacity SD card */
#define CARDTYPE_SDV2_SC        3   /* V2.0 or later Standard Capacity SD card */
#define CARDTYPE_SDV2_HC        4   /* V2.0 or later High/eXtended Capacity SD card */

/* The sector size is fixed to 512bytes in most applications. */
#define SECTOR_SIZE 	    (uint32_t)512
#define MEM_SIZE            (uint32_t)511 // the last byte in sector is 'V'
#define SD_SECTOR_START     (uint32_t)50
#define SD_SECTOR_END       (uint32_t)1000000 // ???

/********************************************************************************
* 					        GLOBAL VARIABLES
********************************************************************************/
extern uint8_t CardType;
extern CARDCONFIG CardConfig;

/********************************************************************************
* 					        PUBLIC FUNCTIONS
********************************************************************************/
SD_BOOL SD_Init (void);
SD_BOOL SD_ReadConfiguration (void);
void    disk_timerproc (void);

SD_BOOL	SD_WriteBytes(uint32_t sect, uint8_t *buf);	// Write a sector
SD_BOOL	SD_ReadBytes(uint32_t sect, uint8_t *buf);


#endif /* __SDCARD_H */

