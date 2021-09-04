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

 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "sdcard.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/

/* Command definitions in SPI bus mode */
#define GO_IDLE_STATE           0
#define SEND_OP_COND            1
#define SWITCH_FUNC             6
#define SEND_IF_COND            8
#define SEND_CSD                9
#define SEND_CID                10
#define STOP_TRANSMISSION       12
#define SEND_STATUS             13
#define SET_BLOCKLEN            16
#define READ_SINGLE_BLOCK       17
#define READ_MULTIPLE_BLOCK     18
#define WRITE_SINGLE_BLOCK      24
#define WRITE_MULTIPLE_BLOCK    25
#define APP_CMD                 55
#define READ_OCR                58
#define CRC_ON_OFF              59

/* Application specific commands supported by SD.
All these commands shall be preceded with APP_CMD (CMD55). */
#define SD_STATUS               13
#define SD_SEND_OP_COND         41

/* R1 response bit flag definition */
#define R1_NO_ERROR         0x00
#define R1_IN_IDLE_STATE    0x01
#define R1_ERASE_RESET      0x02
#define R1_ILLEGAL_CMD      0x04
#define R1_COM_CRC_ERROR    0x08
#define R1_ERASE_SEQ_ERROR  0x10
#define R1_ADDRESS_ERROR    0x20
#define R1_PARA_ERROR       0x40
#define R1_MASK             0x7F


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/
uint8_t CardType;          /* card type */ 
CARDCONFIG CardConfig;      /* Card configuration */

uint8_t Sdcard_RBuf[SD_CARD_RX_BUF];
uint8_t Sdcard_WBuf[SD_CARD_TX_BUF];

uint32_t Sdcard_RSec;
uint32_t Sdcard_WSec;

uint32_t Sdcard_RFlag;
uint32_t Sdcard_WFlag = 1;

/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/
static volatile uint32_t Timer1, Timer2;	/* 100Hz decrement timer stopped at zero (disk_timerproc()) */

/** Select the card */
#define SD_Select()  do {SD_SPI_CS_Low();} while (0)
/** DeSelect the card */
#define SD_DeSelect() do {SD_SPI_CS_High();SD_SPI_RecvByte();} while (0)

/********************************************************************************
* 					           PRIVATE FUNCTIONS
********************************************************************************/
SD_BOOL     SD_ReadConfiguration (void);
uint8_t     SD_SendCommand (uint8_t cmd, uint32_t arg, uint8_t *buf, uint32_t len);
uint8_t     SD_SendACommand (uint8_t cmd, uint32_t arg, uint8_t *buf, uint32_t len);
SD_BOOL     SD_RecvDataBlock (uint8_t *buf, uint32_t len);
SD_BOOL     SD_SendDataBlock (const uint8_t *buf, uint8_t tkn, uint32_t len) ;
SD_BOOL     SD_WaitForReady (void);

/* 
* This function must be called from timer interrupt routine in period
* of 10 ms to generate card control timing.
*/
void disk_timerproc (void)
{
    uint32_t n;

	n = Timer1;						/* 100Hz decrement timer stopped at 0 */
	if (n) Timer1 = --n;
	n = Timer2;
	if (n) Timer2 = --n;               
}


/**
  * @brief  Initializes the memory card.
  *
  * @param  None
  * @retval SD_TRUE: Init OK.
  *         SD_FALSE: Init failed. 
  *
  * Note: Refer to the init flow at http://elm-chan.org/docs/mmc/sdinit.png
  */
SD_BOOL SD_Init (void)
{
    uint32_t i;
    uint8_t  r1, buf[4];

    /* Set card type to unknown */
    CardType = CARDTYPE_UNKNOWN;

    /* Init SPI interface */
    SD_SPI_Init ();

    /* Before reset, Send at least 74 clocks at low frequency 
    (between 100kHz and 400kHz) with CS high and DI (MISO) high. */
    SD_DeSelect();
    SD_SPI_CLK_Low();
    for (i = 0; i < 10; i++)    SD_SPI_SendByte (0xFF);

    /* Send CMD0 with CS low to enter SPI mode and reset the card.
    The card will enter SPI mode if CS is low during the reception of CMD0. 
    Since the CMD0 (and CMD8) must be sent as a native command, the CRC field
    must have a valid value. */
    if (SD_SendCommand (GO_IDLE_STATE, 0, NULL, 0) != R1_IN_IDLE_STATE) // CMD0
    {
        goto  init_end;
    }

    /* Now the card enters IDLE state. */

    /* Card type identification Start ... */

    /* Check the card type, needs around 1000ms */    
    r1 = SD_SendCommand (SEND_IF_COND, 0x1AA, buf, 4);  // CMD8
    if (r1 & 0x80) goto init_end;

    Timer1 = 100; // 1000ms
    if (r1 == R1_IN_IDLE_STATE) { /* It's V2.0 or later SD card */
        if (buf[2]!= 0x01 || buf[3]!=0xAA) goto init_end; 

        /* The card is SD V2 and can work at voltage range of 2.7 to 3.6V */

        do {
            r1 = SD_SendACommand (SD_SEND_OP_COND, 0x40000000, NULL, 0);  // ACMD41
            if      (r1 == 0x00) break;
            else if (r1 > 0x01)  goto init_end;            
        } while (Timer1);

        if (Timer1 && SD_SendCommand (READ_OCR, 0, buf, 4)==R1_NO_ERROR)  // CMD58
            CardType = (buf[0] & 0x40) ? CARDTYPE_SDV2_HC : CARDTYPE_SDV2_SC;
         
    } else { /* It's Ver1.x SD card or MMC card */

        /* Check if it is SD card */
        if (SD_SendCommand (APP_CMD, 0, NULL, 0) & R1_ILLEGAL_CMD)
        {   
            CardType = CARDTYPE_MMC; 
            while (Timer1 && SD_SendCommand (SEND_OP_COND, 0, NULL, 0));
        }  
        else 
        {   
            CardType = CARDTYPE_SDV1; 
            while (Timer1 && SD_SendACommand (SD_SEND_OP_COND, 0, NULL, 0));
        }

        if (Timer1 == 0) CardType = CARDTYPE_UNKNOWN;
    }

    /* For SDHC or SDXC, block length is fixed to 512 bytes, for others,
    the block length is set to 512 manually. */
    if (CardType == CARDTYPE_MMC ||
        CardType == CARDTYPE_SDV1 ||
        CardType == CARDTYPE_SDV2_SC )
    {
        if (SD_SendCommand (SET_BLOCKLEN, SECTOR_SIZE, NULL, 0) != R1_NO_ERROR)
            CardType = CARDTYPE_UNKNOWN;
    }

init_end:              
   SD_DeSelect();

    if (CardType == CARDTYPE_UNKNOWN)
    {
        return (SD_FALSE);
    }
    else     /* Init OK. use high speed during data transaction stage. */
    {
        SD_SPI_CLK_High();
        return (SD_TRUE);
    }
}


/**
  * @brief  Wait for the card is ready. 
  *
  * @param  None
  * @retval SD_TRUE: Card is ready for read commands.
  *         SD_FALSE: Card is not ready 
  */
SD_BOOL SD_WaitForReady (void)
{
    Timer2 = 50;    // 500ms
    SD_SPI_RecvByte(); /* Read a byte (Force enable DO output) */
    do {
        if (SD_SPI_RecvByte () == 0xFF) return SD_TRUE;
    } while (Timer2);

    return SD_FALSE;    
}

/**
  * @brief  Send a command and receive a response with specified format. 
  *
  * @param  cmd: Specifies the command index.
  * @param  arg: Specifies the argument.
  * @param  buf: Pointer to byte array to store the response content.
  * @param  len: Specifies the byte number to be received after R1 response.
  * @retval Value below 0x80 is the normal R1 response (0x0 means no error) 
  *         Value above 0x80 is the additional returned status code.
  *             0x81: Card is not ready
  *             0x82: command response time out error
  */
uint8_t SD_SendCommand (uint8_t cmd, uint32_t arg, uint8_t *buf, uint32_t len) 
{
    uint32_t r1,i;
    uint8_t crc_stop;

    /* The CS signal must be kept low during a transaction */
    SD_Select();

    /* Wait until the card is ready to read (DI signal is High) */
    if (SD_WaitForReady() == SD_FALSE) return 0x81;

    /* Prepare CRC7 + stop bit. For cmd GO_IDLE_STATE and SEND_IF_COND, 
    the CRC7 should be valid, otherwise, the CRC7 will be ignored. */
    if      (cmd == GO_IDLE_STATE)  crc_stop = 0x95; /* valid CRC7 + stop bit */
    else if (cmd == SEND_IF_COND)   crc_stop = 0x87; /* valid CRC7 + stop bit */
    else                            crc_stop = 0x01; /* dummy CRC7 + Stop bit */

    /* Send 6-byte command with CRC. */ 
    SD_SPI_SendByte (cmd | 0x40);
    SD_SPI_SendByte (arg >> 24);
    SD_SPI_SendByte (arg >> 16);
    SD_SPI_SendByte (arg >> 8);
    SD_SPI_SendByte (arg);
    SD_SPI_SendByte (crc_stop); /* Valid or dummy CRC plus stop bit */

   
    /* The command response time (Ncr) is 0 to 8 bytes for SDC, 
    1 to 8 bytes for MMC. */
    for (i = 8; i; i--)
    {
        r1 = SD_SPI_RecvByte ();
        if (r1 != 0xFF) break;   /* received valid response */      
    }
    if (i == 0)  return (0x82); /* command response time out error */

    /* Read remaining bytes after R1 response */
    if (buf && len)
    {
        do 
		{   
            *buf++ = SD_SPI_RecvByte ();
        } while (--len);
    }

    return (r1);
}

/**
  * @brief  Send an application specific command for SD card 
  *         and receive a response with specified format. 
  *
  * @param  cmd: Specifies the command index.
  * @param  arg: Specifies the argument.
  * @param  buf: Pointer to byte array to store the response content.
  * @param  len: Specifies the byte number to be received after R1 response.
  * @retval Value below 0x80 is the normal R1 response(0x0 means no error)
  *         Value above 0x80 is the additional returned status code.
  *             0x81: Card is not ready
  *             0x82: command response time out error
  *
  * Note: All the application specific commands should be precdeded with APP_CMD
  */
uint8_t SD_SendACommand (uint8_t cmd, uint32_t arg, uint8_t *buf, uint32_t len)
{
    uint8_t r1;

    /* Send APP_CMD (CMD55) first */
	r1 = SD_SendCommand(APP_CMD, 0, NULL, 0);
	if (r1 > 1) return r1;    
    
    return (SD_SendCommand (cmd, arg, buf, len));
}

/**
  * @brief  Read card configuration and fill structure CaCardConfig
rdConfig.
  *
  * @param  None
  * @retval SD_TRUE or SD_FALSE. 
  */
SD_BOOL SD_ReadConfiguration ()
{
    uint8_t buf[16];
    uint32_t i, c_size, c_size_mult, read_bl_len;
    SD_BOOL retv;
  
    retv = SD_FALSE;

    /* Read OCR */
    if (SD_SendCommand(READ_OCR, 0, CardConfig.ocr, 4) != R1_NO_ERROR) goto end;

    /* Read CID */
    if ((SD_SendCommand(SEND_CID, 0, NULL, 0) != R1_NO_ERROR) ||
        SD_RecvDataBlock (CardConfig.cid, 16)==SD_FALSE) goto end;

    /* Read CSD */
    if ((SD_SendCommand(SEND_CSD, 0, NULL, 0) != R1_NO_ERROR) ||
        SD_RecvDataBlock (CardConfig.csd, 16)==SD_FALSE) goto end;

    /* sector size */
    CardConfig.sectorsize = 512;
    
    /* sector count */
    if (((CardConfig.csd[0]>>6) & 0x3) == 0x1) /* CSD V2.0 (for High/eXtended Capacity) */
    {
        /* Read C_SIZE */
        c_size =  (((uint32_t)CardConfig.csd[7]<<16) + ((uint32_t)CardConfig.csd[8]<<8) + CardConfig.csd[9]) & 0x3FFFFF;
        /* Calculate sector count */
       CardConfig.sectorcnt = (c_size + 1) * 1024;

    } else   /* CSD V1.0 (for Standard Capacity) */
    {
        /* C_SIZE */
        c_size = (((uint32_t)(CardConfig.csd[6]&0x3)<<10) + ((uint32_t)CardConfig.csd[7]<<2) + (CardConfig.csd[8]>>6)) & 0xFFF;
        /* C_SIZE_MUTE */
        c_size_mult = ((CardConfig.csd[9]&0x3)<<1) + ((CardConfig.csd[10]&0x80)>>7);
        /* READ_BL_LEN */
        read_bl_len = CardConfig.csd[5] & 0xF;
        /* sector count = BLOCKNR*BLOCK_LEN/512, we manually set SECTOR_SIZE to 512*/
        //CardConfig.sectorcnt = (c_size+1)*(1<<read_bl_len) * (1<<(c_size_mult+2)) / 512;
        CardConfig.sectorcnt = (c_size+1) << (read_bl_len + c_size_mult - 7);        
    }

    /* Get erase block size in unit of sector */
    switch (CardType)
    {
        case CARDTYPE_SDV2_SC:
        case CARDTYPE_SDV2_HC:
            if ((SD_SendACommand (SD_STATUS, 0, buf, 1) !=  R1_NO_ERROR) ||
                SD_RecvDataBlock(buf, 16) == SD_FALSE) goto end;      /* Read partial block */    
            for (i=64-16;i;i--) SD_SPI_RecvByte();  /* Purge trailing data */            
            CardConfig.blocksize = 16UL << (buf[10] >> 4); /* Calculate block size based on AU size */
            break;
        case CARDTYPE_MMC:
            CardConfig.blocksize = ((uint16_t)((CardConfig.csd[10] & 124) >> 2) + 1) * (((CardConfig.csd[10] & 3) << 3) + ((CardConfig.csd[11] & 224) >> 5) + 1);
            break;
        case CARDTYPE_SDV1:
            CardConfig.blocksize = (((CardConfig.csd[10] & 63) << 1) + ((uint16_t)(CardConfig.csd[11] & 128) >> 7) + 1) << ((CardConfig.csd[13] >> 6) - 1);
            break;
        default:
            goto end;                
    }

    retv = SD_TRUE;
end:
    SD_DeSelect ();

    return retv;
}

/**
  * @brief  Receive a data block with specified length from SD/MMC. 
  *
  * @param  buf: Pointer to the data array to store the received data
  * @param  len: Specifies the length (in byte) to be received.
  *              The value should be a multiple of 4.
  * @retval SD_TRUE or SD_FALSE
  */
SD_BOOL SD_RecvDataBlock (uint8_t *buf, uint32_t len)
{
    uint8_t datatoken;
    uint32_t i;
	
    /* Read data token (0xFE) */
	Timer1 = 10;   /* Data Read Timerout: 100ms */
	do {							
		datatoken = SD_SPI_RecvByte ();
        if (datatoken == 0xFE) break;
	} while (Timer1);
	if(datatoken != 0xFE) return (SD_FALSE);	/* data read timeout */

    /* Read data block */
    for (i = 0; i < len; i++) {
        buf[i] = SD_SPI_RecvByte ();
    }

    /* 2 bytes CRC will be discarded. */
    SD_SPI_RecvByte ();
    SD_SPI_RecvByte ();
	
    return (SD_TRUE);
}

/**
  * @brief  Send a data block with specified length to SD/MMC. 
  *
  * @param  buf: Pointer to the data array to store the received data
  * @param  tkn: Specifies the token to send before the data block
  * @param  len: Specifies the length (in byte) to send.
  *              The value should be 512 for memory card.
  * @retval SD_TRUE or SD_FALSE
  */
SD_BOOL SD_SendDataBlock (const uint8_t *buf, uint8_t tkn, uint32_t len) 
{
    uint8_t recv;
    uint32_t i;

    /* Send Start Block Token */
    SD_SPI_SendByte (tkn);

    /* Send data block */
    for (i = 0; i < len; i++) 
    {
      SD_SPI_SendByte (buf[i]);
    }

    /* Send 2 bytes dummy CRC */
    SD_SPI_SendByte (0xFF);
    SD_SPI_SendByte (0xFF);

    /* Read data response to check if the data block has been accepted. */
    if (( (SD_SPI_RecvByte ()) & 0x0F) != 0x05)
        return (SD_FALSE); /* write error */

    /* Wait for wirte complete. */
    Timer1 = 20;  // 200ms
    do {
        recv = SD_SPI_RecvByte();
        if (recv == 0xFF) break;  
    } while (Timer1);

    if (recv == 0xFF) return SD_TRUE;       /* write complete */
    else              return (SD_FALSE);    /* write time out */
}

SD_BOOL	SD_Write(uint32_t sect, uint8_t *buf)
{
	SD_BOOL flag = SD_FALSE;
    uint32_t i;

    if (Sdcard_WSec > SECTOR_END) 
    {
        while(1); // end of file
    }
    
	while(Sdcard_WFlag == 0); // wait for ending previous session
	Sdcard_WFlag = 0;
        
	/* Convert sector-based address to byte-based address for non SDHC */
	if (CardType != CARDTYPE_SDV2_HC) sect <<= 9; 
    if (SD_SendCommand (WRITE_SINGLE_BLOCK, sect, NULL, 0) == R1_NO_ERROR) 
	{	
		/*
		* TRANSFER USING DMA: DMA2_Stream5
		*/
// 		/* 2 bytes in the end of sector to flag */
// 		buf[510] = 'S';
// 		buf[511] = 'D';
// 		/* 2 last bytes of frame are dummy CRC */
// 		buf[512] = 0xFF;
// 		buf[513] = 0xFF;
// 		/* dummy byte */
// 		buf[514] = 0xFF;
		
		// Send a token 0xFE
		SD_SPI_SendByte (0xFE);
		// Reenable the DMA
		DMA2_Stream5->M0AR = (uint32_t)buf;
		DMA2_Stream5->NDTR = SECTOR_SIZE;
		DMA_Cmd(DMA2_Stream5, ENABLE);
		flag = SD_TRUE;	
	}
    else
    {
        Sdcard_WFlag = 1;        
    }
    
    return (flag);	
}


// void DMA2_Stream5_IRQHandler(void)
// {
// 	// Transmission using SPI_DMA is completed
// 	DMA_ClearITPendingBit(DMA2_Stream5, DMA_FLAG_TCIF5);
// 	DMA_Cmd(DMA2_Stream5, DISABLE);
// 	// It is necessary to check the last byte of this session (see the manual)
// 	// Waiting for 	the last data is tranfered to SPI_DR
// 	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
// 	// Waiting for the last bit in data is tranfered out
// 	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);	

// 	// /* Read data response to check if the data block has been accepted. */
// 	// if (( (SD_SPI_RecvByte ()) & 0x0F) == 0x05)
// 	// {
// 		// Sdcard_WFlag = 1;       /* write complete */	
// 	// }
// 	// Dummmy CRC & Dummy bytes
//     SD_SPI_RecvByte();
//     SD_SPI_RecvByte();
//     SD_SPI_RecvByte();
//     SD_SPI_RecvByte();
//     SD_DeSelect();
//     
//     Sdcard_WFlag = 1;
//     RB_ReadIndex = (RB_ReadIndex + RB_READ_SIZE) % RB_SIZE;
//     Sdcard_WSec += FILE_NUM;
// }


SD_BOOL	SD_Read(uint32_t sect, uint8_t *buf)
{
    SD_BOOL flag;
	uint8_t datatoken;
	uint32_t i;

    /* Convert sector-based address to byte-based address for non SDHC */
    if (CardType != CARDTYPE_SDV2_HC) sect <<= 9;

    flag = SD_FALSE;    
	if (SD_SendCommand(READ_SINGLE_BLOCK, sect, NULL, 0) == R1_NO_ERROR) 
	{
		/* Read data token (0xFE) */
		Timer1 = 10;   /* Data Read Timerout: 100ms */
		do 
		{							
			datatoken = SD_SPI_RecvByte ();
			if (datatoken == 0xFE) break;
		} while (Timer1);
		
		if(datatoken == 0xFE) 
		{
			// RECEIVE DIRECTLY
			/* Read data block */
			for (i = 0; i < SECTOR_SIZE; i++) 
			{
				buf[i] = SD_SPI_RecvByte ();
			}
			/* 2 bytes CRC will be discarded. */
			SD_SPI_RecvByte ();
			SD_SPI_RecvByte ();
			flag = SD_TRUE;						
		}		
	}
	
    /* De-select the card */
    SD_DeSelect();
    return (flag);	
}


void SD_Run(void)
{
	uint32_t i, j;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// sd card init
	while (SD_Init() == SD_FALSE)
	{
		tick_count = 0;
		while(tick_count <= 5); //delay 50ms
		GPIO_ToggleBits(GPIOB, GPIO_Pin_1);
	}
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	if (SD_ReadConfiguration() == SD_FALSE)	while(1);
	
	// Detect which sector is free
	Sdcard_WSec = 0;
	for(i = 0; i < FILE_NUM; i++)
	{
		SD_Read(SECTOR_START + i, Sdcard_RBuf);
		if ((Sdcard_RBuf[0] == 0x00) && (Sdcard_RBuf[511] == 0x00))
		{
			Sdcard_WSec = SECTOR_START + i;
			break;
		}

	}
	
	
// 	/* Test SD Card */
// 	// GPIOD Periph clock enable 
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
// 	// Configure PDi = {Ouput, Speed-100mhz, push-pull, no pull}
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
// 	Sdcard_WBuf[0] = 'A';Sdcard_WBuf[1] = 'B';Sdcard_WBuf[2] = 'C';
// 	i = 300;
// 	GPIO_SetBits(GPIOD, GPIO_Pin_13);
// 	while(1)
// 	{
//         delay_01ms(50);
// 		if (SD_Write(i, Sdcard_WBuf))
//         {            
//             Sdcard_RBuf[0] = 0; Sdcard_RBuf[1] = 0; Sdcard_RBuf[2] = 0;
//             if (SD_Read(i, Sdcard_RBuf))
//             {
//                 if ((Sdcard_RBuf[0] == 'A') && (Sdcard_RBuf[1] == 'B') && (Sdcard_RBuf[2] == 'C'))
//                 {
//                     GPIO_SetBits(GPIOD, GPIO_Pin_13);
//                 }
//                 else
//                 {
//                     GPIO_ResetBits(GPIOD, GPIO_Pin_13);
//                 }
//             }
//         }
// 		i++;
// 		if (i > 1000) i = 300;
// 	}
    /* 
    * Sd Card Read files: Uncomment below code
    */
    SD_SendData();

	/*
	*	SD card is fulled
	*/
	if (Sdcard_WSec == 0)
	{
		while(1);
	}

}

void SD_SendData(void)
{
	uint32_t i, j;
	uint8_t c;
	
	while(1)
	{
		DMA_Cmd(DMA1_Stream7, DISABLE);
		
		while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);
		c = USART_ReceiveData(UART5);
		USART_SendData(UART5, c);
		while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == SET);
		
		if (c == 'F')
		{
			while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);
			c = USART_ReceiveData(UART5);
			USART_SendData(UART5, c);
			while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == SET);
		}
		c -= 0x30;
		Sdcard_RSec = 0;
		if (( c >= 0) && (c < FILE_NUM))
		{
			Sdcard_RSec = SECTOR_START + c;
		}
		else if (c == FILE_NUM)
		{
			if (Sdcard_WSec == 0) Sdcard_RSec = SECTOR_START + FILE_NUM - 1;
			else if (Sdcard_WSec == SECTOR_START) Sdcard_RSec = SECTOR_START;
			else Sdcard_RSec = Sdcard_WSec - 1;
		}
		
		if (Sdcard_RSec != 0)
		{
			// Send file			
			/* Send the header */
			Sdcard_RBuf[0] = 10;
			for (i = 0; i < 40; i++) { Sdcard_RBuf[i] = 0x30 + Sdcard_RSec - SECTOR_START;}
			for (; i < 80; i++) { Sdcard_RBuf[i] = '-';}
			Sdcard_RBuf[i] = 13;
			
			DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7);
			DMA1_Stream7->M0AR = (uint32_t)Sdcard_RBuf;
			DMA1_Stream7->NDTR = i+1;
			DMA_Cmd(DMA1_Stream7, ENABLE);

			tick_count= 0;
			while(tick_count < 100); // delay 1s
			
			while (Sdcard_RSec < SECTOR_END)
			{
				if ( SD_Read(Sdcard_RSec, Sdcard_RBuf) )
                {
                    if (Sdcard_RBuf[0] == 0)
                    {
                        break; // end of file: break loop
                    }
                    
                    // If this sector is valid, variable i must be RB_READ_SIZE
                    DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7);
                    DMA1_Stream7->M0AR = (uint32_t)Sdcard_RBuf;
                    DMA1_Stream7->NDTR = RB_READ_SIZE;
                    DMA_Cmd(DMA1_Stream7, ENABLE);
                    while (DMA_GetFlagStatus(DMA1_Stream7, DMA_FLAG_TCIF7) == RESET);
                    Sdcard_RSec += FILE_NUM;
                }

			}	
			
		}
        tick_count= 0;
        while(tick_count < 100); // delay 1s			
	}
	

	
// 	for (j = 0; j < FILE_NUM; j++)
// 	{
// 		// Send all the files here
// 		
// 		/* Send the header */
// 		Sdcard_RBuf[0] = 10;
// 		for (i = 0; i < 40; i++) { Sdcard_RBuf[i] = 0x31 + j;}
// 		for (; i < 80; i++) { Sdcard_RBuf[i] = '-';}
// 		Sdcard_RBuf[i] = 13;
// 		
// 		DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7);
// 		DMA1_Stream7->M0AR = (uint32_t)Sdcard_RBuf;
// 		DMA1_Stream7->NDTR = i+1;
// 		DMA_Cmd(DMA1_Stream7, ENABLE);

// 		tick_count= 0;
// 		while(tick_count < 10); // delay 100ms
// 		
// 		
// 		Sdcard_RSec = SECTOR_START + j;
// 		while (Sdcard_RSec < SECTOR_END)
// 		{
// 			SD_Read(Sdcard_RSec, Sdcard_RBuf);
// 			if (Sdcard_RBuf[0] == 0)
// 			{
// 				Sdcard_RSec = SECTOR_END; // end of file: break loop
// 			}
// 			else if ((Sdcard_RBuf[510] == 'S') && (Sdcard_RBuf[511] == 'D'))
// 			{
// 				// valid string
// 				for (i = 0; i < SECTOR_SIZE; i++)
// 				{
// 					if (Sdcard_RBuf[i] == 0) break;	// end of string
// 				}
// 				
// 				DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7);
// 				DMA1_Stream7->M0AR = (uint32_t)Sdcard_RBuf;
// 				DMA1_Stream7->NDTR = i;
// 				DMA_Cmd(DMA1_Stream7, ENABLE);
// 				
// 				while (DMA_GetFlagStatus(DMA1_Stream7, DMA_FLAG_TCIF7) == RESET);
// 				
// 				//tick_count= 0;
// 				//while(tick_count < 10); // delay 100ms
// 			}
// 			Sdcard_RSec += FILE_NUM;
// 		}
// 	}		
	while(1);
}



/********************************************************************************
 * 			LOW-LEVEL LAYER FOR SD CARD
 *	SPI2_MOSI: PB15
 *	SPI2_MISO: PB14
 *	SPI2_SCK:  PB13 
 *	SPI2_NSS:  PB12
********************************************************************************/

/*******************************************************************************
 * @fn     SD_SPI_CS_Low     
 * @brief  Pull down CS pin
 * @param  None
 * @retval None
*******************************************************************************/
 void SD_SPI_CS_Low(void)
 {
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
 }
 
 /*******************************************************************************
 * @fn     SD_SPI_CS_High     
 * @brief  Pull up CS pin
 * @param  None
 * @retval None
*******************************************************************************/
 void SD_SPI_CS_High(void)
 {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
 }
 
 /*******************************************************************************
 * @fn     SD_SPI_CLK_Low     
 * @brief  Set the SPI clock in low rate to initialise SD Card
 * @param  None
 * @retval None
*******************************************************************************/
 void SD_SPI_CLK_Low(void)
 {
	uint16_t tmpreg = 0;
	/* Get the SPIx CR1 value */
	tmpreg = SPI2->CR1;
	tmpreg = (tmpreg & (~0x0038)) | SPI_BaudRatePrescaler_256; // PCLK = 72M/2 = 36M; SPI_CLK = PCLK/256 = 328Kbps
	/* Write to SPIx CR1 */
	SPI2->CR1 = tmpreg;
 }
 
 /*******************************************************************************
 * @fn     SD_SPI_CLK_High     
 * @brief  Set the SPI clock in high rate to communicate with SD Card
 * @param  None
 * @retval None
*******************************************************************************/
 void SD_SPI_CLK_High(void)
 {
	uint16_t tmpreg = 0;
	/* Get the SPIx CR1 value */
	tmpreg = SPI2->CR1;
	tmpreg = (tmpreg & (~0x0038)) | SPI_BaudRatePrescaler_4; // PCLK = 72M/2 = 36M; SPI_CLK = PCLK/4 = 9Mbps
	/* Write to SPIx CR1 */
	SPI2->CR1 = tmpreg;
 }
 
 void SD_SPI_Init(void)
 {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef SPI_GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	DMA_InitTypeDef DmaSPI2TxStruct;
	
	/*
	*	Init SPI2 MISO, MOSI
	*	SPI2_TX = SD_MOSI at PB15
	*	SPI2_RX = SD_MISO at PB14
	*	SPI2_CLK = SD_CLK at PB13 
	*	SPI2_NSS = SD_CS at PB12
	*/
	//	Configure NSS, SCK, MOSI
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; 		//sua here
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_12); // Deselect CS pin

    //  SPI configuration 
	SPI_I2S_DeInit(SPI2);  
	SPI_InitStructure.SPI_Direction 	    = SPI_Direction_2Lines_FullDuplex; //	2-way
	SPI_InitStructure.SPI_DataSize 		    = SPI_DataSize_8b; //	8 bits
	SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_Low;							
	SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS 				= SPI_NSS_Soft;	//	pin Chip-select be controlled by software
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // APB1 = 72M/2 = 36, Prescale = 4 --> CLK = 36/4 = 9M
	SPI_InitStructure.SPI_FirstBit 			= SPI_FirstBit_MSB;	//	MSB bit first out
	SPI_InitStructure.SPI_CRCPolynomial 	= 7; //	0007 is reset value
	SPI_InitStructure.SPI_Mode 				= SPI_Mode_Master; //	master mode
	SPI_Init(SPI2, &SPI_InitStructure);
	//	Enable SPI2
    SPI_Cmd(SPI2, ENABLE);
    
	//	Enable DMA request	
	//SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx|SPI_I2S_DMAReq_Rx, ENABLE);
	//SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
	 
// 	/*
// 	*	DMA2 SPI2: TX Stream 5, channel 3
// 	*	Memory To Peripheral
// 	*
// 	*/
// 	//	Enable clock to DMA2
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
// 	//default reset state
// 	DMA_DeInit(DMA2_Stream5);				
// 	DmaSPI2TxStruct.DMA_Channel = DMA_Channel_3;
// 	DmaSPI2TxStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
// 	DmaSPI2TxStruct.DMA_Memory0BaseAddr = 0; 
//     DmaSPI2TxStruct.DMA_PeripheralBaseAddr = (uint32_t)SPI2 + 0x0C;  		 
// 	DmaSPI2TxStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
// 	DmaSPI2TxStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
// 	DmaSPI2TxStruct.DMA_Priority = DMA_Priority_Low;
// 	DmaSPI2TxStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;				//direct mode
// 	DmaSPI2TxStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
// 	DmaSPI2TxStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
// 	DmaSPI2TxStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
// 	DmaSPI2TxStruct.DMA_Mode = DMA_Mode_Normal;
// 	DmaSPI2TxStruct.DMA_BufferSize = 0;						//JUST init value
// 	DmaSPI2TxStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
// 	DmaSPI2TxStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
// 	DMA_Init(DMA2_Stream5, &DmaSPI2TxStruct);
// 	
// 	// ENABLE DMA2 STREAM5
// 	//DMA_Cmd(DMA2_Stream5, ENABLE); 
// 	
//  	/*
//  	*	DMA2 SPI2 TX Interrupt
// 	*/	
// 	NVIC_InitStruct.NVIC_IRQChannel = DMA2_Stream5_IRQn;
// 	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;		// in [0,15] highest priority = 0
// 	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 5;			    // in [0,15] highest priority = 0
// 	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStruct);
// 	//Enable DMA Stream Transfer Complete interrupt
// 	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);

 }
 
 uint8_t SD_SPI_RecvByte(void)
 {
	return SD_SPI_ExchangeByte(SPI2, 0xFF);
 }
 
 void SD_SPI_SendByte(uint8_t data)
 {
	SD_SPI_ExchangeByte(SPI2, data);
 }
 
 uint8_t SD_SPI_ExchangeByte(SPI_TypeDef* SPIx, uint8_t byte)
{
	// Loop while DR register in not emplty 
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	
	// Send byte through the SPIx peripheral
	SPI_I2S_SendData(SPIx, byte);
	
	//	Wait to receive a byte
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	
	// Return the byte read from the SPI bus 
	return SPI_I2S_ReceiveData(SPIx);
}
