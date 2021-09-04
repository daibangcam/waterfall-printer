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
#define SECTOR_SIZE 	(uint32_t)512
#define FILE_NUM		(uint32_t)5
#define SECTOR_START	(uint32_t)100
#define SECTOR_END		(uint32_t)990900 // Note last sector is 990976
#define SD_CARD_RX_BUF  (uint32_t)520
#define SD_CARD_TX_BUF  (uint32_t)520

#define RB_READ_SIZE    (uint32_t)510

/********************************************************************************
* 					        GLOBAL VARIABLES
********************************************************************************/
extern uint8_t CardType;
extern CARDCONFIG CardConfig;

extern uint8_t Sdcard_RBuf[SD_CARD_RX_BUF];  
extern uint8_t Sdcard_WBuf[SD_CARD_TX_BUF]; 

extern uint32_t Sdcard_RSec;
extern uint32_t Sdcard_WSec;

extern uint32_t Sdcard_RFlag;
extern uint32_t Sdcard_WFlag;


/********************************************************************************
* 					        PUBLIC FUNCTIONS
********************************************************************************/
SD_BOOL SD_Init (void);
SD_BOOL SD_ReadConfiguration (void);
void    disk_timerproc (void);

SD_BOOL	SD_Write(uint32_t sect, uint8_t *buf);	// Write a sector
SD_BOOL	SD_Read(uint32_t sect, uint8_t *buf);
void    SD_Run(void);
void 	SD_SendData(void);

/********************************************************************************
 * 			LOW-LEVEL LAYER FOR SD CARD
 *	SPI2_MOSI: PB15
 *	SPI2_MISO: PB14
 *	SPI2_SCK:  PB13 
 *	SPI2_NSS:  PB12
********************************************************************************/

void SD_SPI_Init(void);
void SD_SPI_CS_Low(void);
void SD_SPI_CS_High(void);
void SD_SPI_CLK_Low(void);
void SD_SPI_CLK_High(void);
uint8_t SD_SPI_RecvByte(void); 
void SD_SPI_SendByte (uint8_t data);
uint8_t SD_SPI_ExchangeByte(SPI_TypeDef* SPIx, uint8_t byte);

#endif /* __SDCARD_H */

