/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: mcu_board.h
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 16-June-13
 *	Description	    : Hardware abstract layer 
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/

#ifndef __MCU_BOARD_H
#define __MCU_BOARD_H
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "stm32f10x_conf.h"
#include "sdcard.h"
#include "type.h"
#include "conf.h"
#include "utility.h"

/********************************************************************************
* 							        TYPEDEF
********************************************************************************/

/********************************************************************************
* 							        DEFINE
********************************************************************************/
#define PCLK                32000000 // 32MHz

/* Button select */
#define BUT_SEL_PORT        GPIOA
#define BUT_SEL_PIN         GPIO_Pin_1

/* LED */
#define LED_PULSE_PORT      GPIOB
#define LED_PULSE_PIN       GPIO_Pin_0

/* Driver control */    
#define DRV_SPIx            SPI1
#define DRV_SPI_PORT        GPIOA
// SPI Configuration
#define DRV_SPI_OE_PIN      GPIO_Pin_4  // NSS: output enable
#define DRV_SPI_SRCLK_PIN   GPIO_Pin_5  // SCK: clock to transfer data
#define DRV_SPI_RCLK_PIN    GPIO_Pin_6  // MISO: clock to out data
#define DRV_SPI_SDI_PIN     GPIO_Pin_7  // MOSI: data out

#define DRV_SPI_BAUDRATE    1000        // 1M ???

/* CAN Communication */
#define COMM_CANx           CAN1
#define COMM_CAN_PORT       GPIOB
#define COMM_CAN_TX_PIN     GPIO_Pin_9
#define COMM_CAN_RX_PIN     GPIO_Pin_8
#define COMM_CAN_BAUDRATE   1000000    // 1Mbit/s
#define COMM_CAN_REMAP      GPIO_Remap1_CAN1

/* PC Serial communication */
#define PC_USARTx           USART1
#define PC_USART_PORT       GPIOA
#define PC_USART_TX_PIN     GPIO_Pin_9
#define PC_USART_RX_PIN     GPIO_Pin_10
#define PC_USART_BAUDRATE   115200


#define PC_USART_DATA_REG           (uint32_t)PC_USARTx + 0x04
#define PC_USART_TX_DMA_CHANNEL     DMA1_Channel4
#define PC_USART_TX_DMA_FLAG        DMA1_FLAG_TC4
#define PC_USART_TX_DMA_IRQn        DMA1_Channel4_IRQn
#define PC_USART_DMA_TX_Interrupt   DMA1_Channel4_IRQHandler
#define PC_USART_RX_DMA_CHANNEL     DMA1_Channel5
#define PC_USART_RX_DMA_FLAG        DMA1_FLAG_TC5
#define PC_USART_RX_DMA_IRQn        DMA1_Channel5_IRQn
#define PC_USART_DMA_RX_Interrupt   DMA1_Channel5_IRQHandler
#define PC_USART_DMA_RX_BUF_SIZE    (uint32_t)5000

/* Micro SD Card */
#define MSDC_SPIx           SPI2
#define MSDC_SPI_PORT       GPIOB
#define MSDC_SPI_NSS_PIN    GPIO_Pin_12
#define MSDC_SPI_SCK_PIN    GPIO_Pin_13
#define MSDC_SPI_MISO_PIN   GPIO_Pin_14
#define MSDC_SPI_MOSI_PIN   GPIO_Pin_15
#define MSDC_SPI_BAUDRATE   1              //?????

/* I2C backup */

/* USART backup */

/* System tick timer */

/* RTC */
#define RTC_BKP_CONFIG_DONE 0x01
#define RTC_BKP_CONFIG_NO   0x00
#define SEC_PER_DAY         86400
#define RTC_LSE_FREQ        32768
//default date-time: Sat, 22/06/13, 13:12:07
#define RTC_DAY_DEFAULT     1
#define RTC_DATE_DEFAULT    3
#define RTC_MONTH_DEFAULT   5
#define RTC_YEAR_DEFAULT    14
#define RTC_HOUR_DEFAULT    14
#define RTC_MIN_DEFAULT     00
#define RTC_SEC_DEFALUT     00

#define RTC_BKP_CONFIG_REG  BKP_DR1
#define RTC_BKP_DATE_REG    BKP_DR2
#define RTC_BKP_MONTH_REG   BKP_DR3
#define RTC_BKP_YEAR_REG    BKP_DR4


/********************************************************************************
* 					        GLOBAL VARIABLES
********************************************************************************/
extern uint32_t tick_count;
extern uint32_t TIM_REF_Tick1ms;
extern uint32_t TIM_REF_Tick10ms;
extern RTCStruct DateTime;
extern BOOL RTC_Int1sFlag;
extern BOOL COMM_CAN_RXFlag;
extern uint8_t PC_USART_DMA_RxBuf[PC_USART_DMA_RX_BUF_SIZE];


/********************************************************************************
* 					        PRIVATE VARIABLES
********************************************************************************/

/********************************************************************************
* 					        PUBLIC FUNCTIONS
********************************************************************************/
void MCU_BOARD_Init(void);

void MCU_ClockFreq_Init(void);

void BUT_SEL_Init(void);
BOOL BUT_SEL_IsPress(void);
BOOL BUT_SEL_IsPress_Debounce(void);

void LED_PULSE_Init(void);
void LED_PULSE_Set(void);
void LED_PULSE_Reset(void);
void LED_PULSE_Toggle(void);

void TIM_REF_Init(void);
void TIM_REF_DelayTms(uint32_t T);
void SysTick_Handler(void);
void TIM_REF_SetCallback(COM_pFunc pf, BOOL b);

void PC_USART_Init(void);
void PC_USART_ReadBytes(uint8_t *c, uint32_t l);
void PC_USART_WriteBytes(uint8_t *c, uint32_t l);
void PC_USART_DMA_ReadBytes(uint8_t *c, uint32_t l);
void PC_USART_DMA_WriteBytes(uint8_t *c, uint32_t l);
void PC_USART_DMA_TX_Interrupt(void);
void PC_USART_DMA_RX_Interrupt(void);

void MSDC_SPI_Init(void);
void MSDC_SPI_CS_Low(void);
void MSDC_SPI_CS_High(void);
void MSDC_SPI_CLK_Low(void);
void MSDC_SPI_CLK_High(void);
uint8_t MSDC_SPI_RecvByte(void);
void MSDC_SPI_SendByte (uint8_t data);
uint8_t MSDC_SPI_ExchangeByte(SPI_TypeDef* SPIx, uint8_t byte);

void RTC_Init(void);
void RTC_AutoCalib(void);
void RTC_ManualCalib(void);
void RTC_UpdateDateTime(void);
void RTC_Set(RTCStruct t);
RTCStruct RTC_Get(void);
void RTC_IRQHandler(void);

void COMM_CAN_Init(void);
uint8_t COMM_CAN_WriteBytes(uint8_t a, uint8_t * c, uint8_t l);
void COMM_CAN_ReadBytes(uint8_t * a, uint8_t * c, uint8_t *l);

void DRV_SPI_Init(void);
void DRV_SPI_WriteBytes(uint8_t *c, uint8_t l);
void DRV_SPI_Do(void);
void DRV_SPI_Eo(void);

#endif /* __BOARD_H */
