/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: mcu_board.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 16-June-13
 *	Description	    : Hardware abstract layer 
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "mcu_board.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/
uint32_t tick_count = 0;
uint32_t TIM_REF_Tick1ms = 0;
uint32_t TIM_REF_Tick10ms = 0;
RTCStruct DateTime;
BOOL RTC_Int1sFlag = FALSE;
BOOL COMM_CAN_RXFlag = FALSE;
uint8_t PC_USART_DMA_RxBuf[PC_USART_DMA_RX_BUF_SIZE];
/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/
uint32_t  TIM_REF_Tick = 0;
BOOL TIM_REF_FlagCallback = FALSE;
COM_pFunc TIM_REF_Callback;

/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     MCU_BOARD_Init     
 * @brief  Initialise ports and peripherals that are used in application
 * @param  None
 * @retval None
*******************************************************************************/
void MCU_BOARD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    LED_PULSE_Init();
    BUT_SEL_Init();
    TIM_REF_Init();
    
#ifdef _USE_MSDC_SPI_
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
#endif /* _USE_MSDC_SPI_ */

#ifdef _USE_PC_USART_
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    PC_USART_Init();
#endif /* _USE_PC_USART_ */

#ifdef  _USE_RTC_
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
    RTC_Init();
#endif /* _USE_RTC_ */

#ifdef _USE_COMM_CAN_
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    COMM_CAN_Init();
#endif /* _USE_COMM_CAN_ */

#ifdef _USE_DRV_SPI_
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    DRV_SPI_Init();
#endif 

    TIM_REF_DelayTms(2000);

}

/*******************************************************************************
 * @fn     MCU_ClockFreq_Init     
 * @brief  The default system sets the clock based on XTAL 8Mhz, so that we must
            re-initialise clock using the XTAL 16Mhz.
 * @param  None
 * @retval None
*******************************************************************************/
void MCU_ClockFreq_Init(void)
{
    /* Setting System Clock to 72Mhz using PLL from HSE source */
    
    /* Settting HCLK clock to 72Mhz */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
}

/*******************************************************************************
 * @fn     BUT_SEL_Init     
 * @brief  Initialise pin to input type
 * @param  None
 * @retval None
*******************************************************************************/
void BUT_SEL_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = BUT_SEL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(BUT_SEL_PORT, &GPIO_InitStructure);	
}

/*******************************************************************************
 * @fn     BUT_SEL_IsPress     
 * @brief  Return the pin's state: value TRUE means that button is pressed
 * @param  None
 * @retval Button is pressed or not
 *      This return value can be one of the following values:
 *          @arg TRUE: button is pressed
 *          @arg FALSE
*******************************************************************************/
BOOL BUT_SEL_IsPress(void)
{
    BOOL ret = TRUE;
    if (BUT_SEL_PORT->IDR & BUT_SEL_PIN) ret = FALSE;
    return ret;
}

/*******************************************************************************
 * @fn     BUT_SEL_IsPress_Debounce     
 * @brief  Check the button is pressed or not with debounce
 * @param  None
 * @retval Button is pressed or not
 *      This return value can be one of the following values:
 *          @arg TRUE: button is pressed
 *          @arg FALSE
*******************************************************************************/
BOOL BUT_SEL_IsPress_Debounce(void)
{
    BOOL res = FALSE;
    
    if (BUT_SEL_IsPress())
    {
        TIM_REF_DelayTms(200);
        if (BUT_SEL_IsPress()) res = TRUE;
    }
    return res;
}

/*******************************************************************************
 * @fn     LED_PULSE_Init     
 * @brief  Initialise pin to output type
 * @param  None
 * @retval None
*******************************************************************************/
void LED_PULSE_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LED_PULSE_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PULSE_PORT, &GPIO_InitStructure);	   
}
/*******************************************************************************
 * @fn     LED_PULSE_Set     
 * @brief  Turn On the LED
 * @param  None
 * @retval None
*******************************************************************************/
void LED_PULSE_Set(void)
{
    GPIO_ResetBits(LED_PULSE_PORT, LED_PULSE_PIN);
}
/*******************************************************************************
 * @fn     LED_PULSE_Reset     
 * @brief  Turn Off the LED
 * @param  None
 * @retval None
*******************************************************************************/
void LED_PULSE_Reset(void)
{
    GPIO_SetBits(LED_PULSE_PORT, LED_PULSE_PIN);
}
/*******************************************************************************
 * @fn     LED_PULSE_Toggle     
 * @brief  Toggle the LED
 * @param  None
 * @retval None
*******************************************************************************/
void LED_PULSE_Toggle(void)
{
    LED_PULSE_PORT->ODR ^= LED_PULSE_PIN;
}
/*******************************************************************************
 * @fn     TIM_REF_Init     
 * @brief  Initialise system tick timer interrupt at every 1ms
 * @param  None
 * @retval None
*******************************************************************************/
void TIM_REF_Init(void)
{
    SysTick_Config(SystemCoreClock/1000);/* This sets the interrupt every 1ms */
    //SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}
/*******************************************************************************
 * @fn     TIM_REF_DelayTms     
 * @brief  Wait until timer value is set 
 * @param  T: the time delay is (T * 1ms)
 * @retval None
*******************************************************************************/
void TIM_REF_DelayTms(uint32_t T)
{
    TIM_REF_Tick = 0;
    while(TIM_REF_Tick < T);
}
/*******************************************************************************
 * @fn     SysTick_Handler     
 * @brief  System tick timer interrupt at every 1ms
 * @param  None
 * @retval None
*******************************************************************************/
void SysTick_Handler(void)
{
    static uint32_t count10ms = 0;
    static uint32_t count500ms = 0;
    static uint32_t countCheckdata = 0;
    
    count10ms++;
    count500ms++;
    countCheckdata++;
    
    // Generate the 10ms interrupt
    if (count10ms >= 10)
    {
        count10ms = 0;
        tick_count++;
        TIM_REF_Tick10ms++;
        disk_timerproc();
    }
    
    // Generate the 500ms interrupt
    if (count500ms >= 500)
    {
        count500ms = 0;
     //   LED_PULSE_Toggle();
    }
    
    // Generate the interrupt to check the frame is ready or not (1s)
    if (countCheckdata >= 1000) 
    {
        countCheckdata = 0;
        if (TIM_REF_FlagCallback == TRUE)
        {
            TIM_REF_Callback();
        }
    }
    
    TIM_REF_Tick1ms++;
    TIM_REF_Tick++;
}

/*******************************************************************************
 * @fn     SysTick_Handler     
 * @brief  System tick timer interrupt at every 1ms
 * @param  None
 * @retval None
*******************************************************************************/

void TIM_REF_SetCallback(COM_pFunc pf, BOOL b)
{
    TIM_REF_FlagCallback = b;
    TIM_REF_Callback = pf;
}

/*******************************************************************************
 * @fn     PC_USART_Init     
 * @brief  Initialise USART to communicate with PC
 * @param  None
 * @retval None
*******************************************************************************/
void PC_USART_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* TX, RX pins */
    GPIO_InitStructure.GPIO_Pin = PC_USART_RX_PIN; 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(PC_USART_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = PC_USART_TX_PIN; 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PC_USART_PORT, &GPIO_InitStructure);

    /* USART parameters */
    USART_InitStructure.USART_BaudRate = PC_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(PC_USARTx, &USART_InitStructure );
    USART_Cmd(PC_USARTx, ENABLE);
 
#ifdef _USE_PC_USART_TX_DMA_
    /* Initialise DMA TX */
    DMA_DeInit(PC_USART_TX_DMA_CHANNEL);  
    DMA_InitStructure.DMA_PeripheralBaseAddr = PC_USART_DATA_REG;
    DMA_InitStructure.DMA_MemoryBaseAddr = 0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(PC_USART_TX_DMA_CHANNEL, &DMA_InitStructure); 
    /* Enable USART DMA TX request */
    USART_DMACmd(PC_USARTx, USART_DMAReq_Tx, ENABLE);  
    /* Enable DMA TX Channel */
    DMA_Cmd(PC_USART_TX_DMA_CHANNEL, DISABLE);
    
    #ifdef _USE_PC_USART_TX_DMA_INT_
        DMA_Cmd(PC_USART_TX_DMA_CHANNEL, ENABLE);
        NVIC_InitStructure.NVIC_IRQChannel = PC_USART_TX_DMA_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        DMA_ITConfig(PC_USART_TX_DMA_CHANNEL, DMA_IT_TC, ENABLE);
    #endif /*_USE_PC_USART_TX_DMA_INT_*/
    
#endif /* _USE_PC_USART_TX_DMA_ */

#ifdef _USE_PC_USART_RX_DMA_
    /* Initialise DMA RX */
    DMA_DeInit(PC_USART_RX_DMA_CHANNEL); 
    DMA_InitStructure.DMA_PeripheralBaseAddr = PC_USART_DATA_REG;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)PC_USART_DMA_RxBuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = PC_USART_DMA_RX_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(PC_USART_RX_DMA_CHANNEL, &DMA_InitStructure); 
    /* Enable  request */
    USART_DMACmd(PC_USARTx, USART_DMAReq_Rx, ENABLE);  
    /* Enable DMA RX Channel */
    DMA_Cmd(PC_USART_RX_DMA_CHANNEL, DISABLE);
    
    #ifdef _USE_PC_USART_RX_DMA_INT_
        DMA_Cmd(PC_USART_RX_DMA_CHANNEL, ENABLE);
        NVIC_InitStructure.NVIC_IRQChannel = PC_USART_RX_DMA_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        DMA_ITConfig(PC_USART_RX_DMA_CHANNEL, DMA_IT_TC, ENABLE);
    #endif /*_USE_PC_USART_RX_DMA_INT_*/
    
#endif /* _USE_PC_USART_RX_DMA_ */
}

/*******************************************************************************
 * @fn     PC_USART_ReadBytes     
 * @brief  Read/Receive l bytes from PC
 * @param  c: pointer to array that will store bytes from PC
 * @param  l: length of the array
 * @retval None
*******************************************************************************/
void PC_USART_ReadBytes(uint8_t *c, uint32_t l)
{
    while(l)
    {
        /* Wait until reception complete */
        while(USART_GetFlagStatus(PC_USARTx, USART_FLAG_RXNE) == RESET);
        *c = (uint8_t)USART_ReceiveData(PC_USARTx);
        /* Receive the next byte */
        c++;
        l--;
    }
}

/*******************************************************************************
 * @fn     PC_USART_WriteBytes     
 * @brief  Write/Send l bytes to PC
 * @param  c: pointer to array that will be sent to PC
 * @param  l: length of the array
 * @retval None
*******************************************************************************/
void PC_USART_WriteBytes(uint8_t *c, uint32_t l)
{   
    while(l)
    {
        USART_SendData(PC_USARTx, (uint16_t)*c);
        /* Wait until transmission complete */
        while(USART_GetFlagStatus(PC_USARTx, USART_FLAG_TXE) == RESET);
        /* Send the next byte */
        c++;
        l--;
    }
}

/*******************************************************************************
 * @fn     PC_USART_DMA_ReadBytes     
 * @brief  Read/Receive l bytes from PC using DMA
 * @param  c: pointer to array that will store bytes from PC
 * @param  l: length of the array
 * @retval None
*******************************************************************************/
void PC_USART_DMA_ReadBytes(uint8_t *c, uint32_t l)
{
    PC_USART_RX_DMA_CHANNEL->CMAR = (uint32_t)c; //DMA_MemoryBaseAddr
    PC_USART_RX_DMA_CHANNEL->CNDTR = l; //DMA_BufferSize
    DMA_Cmd(PC_USART_RX_DMA_CHANNEL, ENABLE);
    
    #ifndef _USE_PC_USART_RX_DMA_INT_
        /* Wait until DMA Channel Transfer Complete */
        while (DMA_GetFlagStatus(PC_USART_RX_DMA_FLAG) == RESET); 
        DMA_ClearFlag(PC_USART_RX_DMA_FLAG);    
        DMA_Cmd(PC_USART_RX_DMA_CHANNEL, DISABLE);
    #endif /*_USE_PC_USART_RX_DMA_INT_*/
}

/*******************************************************************************
 * @fn     PC_USART_DMA_WriteBytes     
 * @brief  Write/Send l bytes to PC using DMA
 * @param  c: pointer to array that will be sent to PC
 * @param  l: length of the array
 * @retval None
*******************************************************************************/
void PC_USART_DMA_WriteBytes(uint8_t *c, uint32_t l)
{  
    PC_USART_TX_DMA_CHANNEL->CMAR = (uint32_t)c; //DMA_MemoryBaseAddr
    PC_USART_TX_DMA_CHANNEL->CNDTR = l; //DMA_BufferSize
    DMA_Cmd(PC_USART_TX_DMA_CHANNEL, ENABLE);
    
    #ifndef _USE_PC_USART_TX_DMA_INT_
        /* Wait until DMA Channel Transfer Complete */
        while (DMA_GetFlagStatus(PC_USART_TX_DMA_FLAG) == RESET);  
        DMA_ClearFlag(PC_USART_TX_DMA_FLAG);
        DMA_Cmd(PC_USART_TX_DMA_CHANNEL, DISABLE);
    #endif /*_USE_PC_USART_TX_DMA_INT_*/
}

/*******************************************************************************
 * @fn     PC_USART_TX_DMA_IRQn     
 * @brief  Interrupt handler
 * @param  None
 * @retval None
*******************************************************************************/
void PC_USART_DMA_TX_Interrupt(void)
{
    if (DMA_GetFlagStatus(PC_USART_TX_DMA_FLAG) == SET)
    {
        DMA_ClearFlag(PC_USART_TX_DMA_FLAG);
        DMA_Cmd(PC_USART_TX_DMA_CHANNEL, DISABLE);
    }
}

/*******************************************************************************
 * @fn     PC_USART_RX_DMA_IRQn     
 * @brief  Interrupt handler
 * @param  None
 * @retval None
*******************************************************************************/
void PC_USART_DMA_RX_Interrupt(void)
{
    if (DMA_GetFlagStatus(PC_USART_RX_DMA_FLAG) == SET)
    {
        // Reset buffer
        DMA_ClearFlag(PC_USART_RX_DMA_FLAG);
        DMA_Cmd(PC_USART_RX_DMA_CHANNEL, DISABLE);
        PC_USART_RX_DMA_CHANNEL->CNDTR = PC_USART_DMA_RX_BUF_SIZE;
        DMA_Cmd(PC_USART_RX_DMA_CHANNEL, ENABLE);
    }
}




/*******************************************************************************
 * @fn     MSDC_SPI_Init     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
void MSDC_SPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitTypeDef SPI_GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    //	Configure SCK, MOSI
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = MSDC_SPI_SCK_PIN | MSDC_SPI_MOSI_PIN;
    GPIO_Init(MSDC_SPI_PORT, &GPIO_InitStructure);
    
    //	Configure NSS
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = MSDC_SPI_NSS_PIN;
    GPIO_Init(MSDC_SPI_PORT, &GPIO_InitStructure);
    GPIO_SetBits(MSDC_SPI_PORT, MSDC_SPI_NSS_PIN); // Deselect CS pin
     
    //	Configure MISO
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = MSDC_SPI_MISO_PIN;
    GPIO_Init(MSDC_SPI_PORT, &GPIO_InitStructure);

    //  SPI configuration 
    SPI_I2S_DeInit(MSDC_SPIx);  
    SPI_InitStructure.SPI_Direction 	    = SPI_Direction_2Lines_FullDuplex; //	2-way
    SPI_InitStructure.SPI_DataSize 		    = SPI_DataSize_8b; //	8 bits
    SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_Low;							
    SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS 				= SPI_NSS_Soft;	//	pin Chip-select be controlled by software
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // APB1 = 72M/2 = 36, Prescale = 4 --> CLK = 36/4 = 9M
    SPI_InitStructure.SPI_FirstBit 			= SPI_FirstBit_MSB;	//	MSB bit first out
    SPI_InitStructure.SPI_CRCPolynomial 	= 7; //	0007 is reset value
    SPI_InitStructure.SPI_Mode 				= SPI_Mode_Master; //	master mode
    SPI_Init(MSDC_SPIx, &SPI_InitStructure);
    //	Enable SPI
    SPI_Cmd(MSDC_SPIx, ENABLE);

}

/*******************************************************************************
 * @fn     MSDC_SPI_CS_Low     
 * @brief  Pull down CS pin
 * @param  None
 * @retval None
*******************************************************************************/
void MSDC_SPI_CS_Low(void)
{
    GPIO_ResetBits(MSDC_SPI_PORT, MSDC_SPI_NSS_PIN);
}

/*******************************************************************************
 * @fn     MSDC_SPI_CS_High     
 * @brief  Pull up CS pin
 * @param  None
 * @retval None
*******************************************************************************/
void MSDC_SPI_CS_High(void)
{
    GPIO_SetBits(MSDC_SPI_PORT, MSDC_SPI_NSS_PIN);
}

/*******************************************************************************
 * @fn     MSDC_SPI_CLK_Low     
 * @brief  Set the SPI clock in low rate to initialise MSDC Card
 * @param  None
 * @retval None
*******************************************************************************/
void MSDC_SPI_CLK_Low(void)
{
    uint16_t tmpreg = 0;
    /* Get the SPIx CR1 value */
    tmpreg = MSDC_SPIx->CR1;
    tmpreg = (tmpreg & (~0x0038)) | SPI_BaudRatePrescaler_256; // PCLK = 72M/2 = 36M; SPI_CLK = PCLK/256 = 328Kbps
    /* Write to SPIx CR1 */
    MSDC_SPIx->CR1 = tmpreg;
}


 
 /*******************************************************************************
 * @fn     MSDC_SPI_CLK_High     
 * @brief  Set the SPI clock in high rate to communicate with MSDC Card
 * @param  None
 * @retval None
*******************************************************************************/
void MSDC_SPI_CLK_High(void)
{
    uint16_t tmpreg = 0;
    /* Get the SPIx CR1 value */
    tmpreg = MSDC_SPIx->CR1;
    tmpreg = (tmpreg & (~0x0038)) | SPI_BaudRatePrescaler_8; // PCLK = 72M/2 = 36M; SPI_CLK = PCLK/4 = 9Mbps
    /* Write to SPIx CR1 */
    MSDC_SPIx->CR1 = tmpreg;
}

/*******************************************************************************
 * @fn     MSDC_SPI_RecvByte     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
uint8_t MSDC_SPI_RecvByte(void)
{
    return MSDC_SPI_ExchangeByte(MSDC_SPIx, 0xFF);
}

/*******************************************************************************
 * @fn     MSDC_SPI_SendByte     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
void MSDC_SPI_SendByte(uint8_t data)
{
    MSDC_SPI_ExchangeByte(MSDC_SPIx, data);
}

/*******************************************************************************
 * @fn     MSDC_SPI_SendByte     
 * @brief  
 * @param  None
 * @retval None
*******************************************************************************/
uint8_t MSDC_SPI_ExchangeByte(SPI_TypeDef* SPIx, uint8_t byte)
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


/*******************************************************************************
 * @fn     RTC_Init     
 * @brief  Initialise RTC & BKP peripherals
 * @param  None
 * @retval None
*******************************************************************************/
void RTC_Init(void)
{
    RTCStruct t;
    NVIC_InitTypeDef NVIC_InitStructure;

    /*Allow access to Backup Registers*/
    PWR_BackupAccessCmd(ENABLE);
    
    /*Enable 32.768 kHz external oscillator */
    RCC_LSEConfig(RCC_LSE_ON);
    TIM_REF_DelayTms(10);
    /* Choose the LSE as a clock source for RTC */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    
    /* RTC Enabled */
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForLastTask();
    /*Wait for RTC registers synchronisation */
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
 

   /* Set default system time */
    t.day    = RTC_DAY_DEFAULT  ;
    t.date   = RTC_DATE_DEFAULT ;
    t.month  = RTC_MONTH_DEFAULT;
    t.year   = RTC_YEAR_DEFAULT ;
    t.hour   = RTC_HOUR_DEFAULT ;
    t.min    = RTC_MIN_DEFAULT  ;
    t.sec    = RTC_SEC_DEFALUT  ;
    
    RTC_Set(t);
    BKP_WriteBackupRegister(RTC_BKP_CONFIG_REG, RTC_BKP_CONFIG_DONE); 
    
//     /* Check whether this is the first time of RTC or not*/
//     if (BKP_ReadBackupRegister(RTC_BKP_CONFIG_REG) != RTC_BKP_CONFIG_DONE)
//     {
//         /* Set default system time */
//         t.day    = RTC_DAY_DEFAULT  ;
//         t.date   = RTC_DATE_DEFAULT ;
//         t.month  = RTC_MONTH_DEFAULT;
//         t.year   = RTC_YEAR_DEFAULT ;
//         t.hour   = RTC_HOUR_DEFAULT ;
//         t.min    = RTC_MIN_DEFAULT  ;
//         t.sec    = RTC_SEC_DEFALUT  ;
//         
//         RTC_Set(t);
//         BKP_WriteBackupRegister(RTC_BKP_CONFIG_REG, RTC_BKP_CONFIG_DONE); 
//     }
//     else
//     {
//         /* Update the Date & time is elapsed */
//         RTC_UpdateDateTime();
//     }
    
    /* Enable the RTC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Setting RTC Interrupts-Seconds interrupt enabled */
    RTC_ITConfig(RTC_IT_SEC , ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    
    /* Set RTC prescaler: set RTC period to 1 sec */
    RTC_SetPrescaler(RTC_LSE_FREQ-1);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

/*******************************************************************************
 * @fn     RTC_AutoCalib     
 * @brief  Calibrate the error of XTAL 32.768k automatically by comparing with
 *          a timer in MCU
 * @param  None
 * @retval None
*******************************************************************************/
void RTC_AutoCalib(void)
{
    
}

/*******************************************************************************
 * @fn     RTC_ManualCalib     
 * @brief  Calibrate the error of XTAL 32.768k manually using high precision 
 *          oscilloscope
 * @param  None
 * @retval None
*******************************************************************************/
void RTC_ManualCalib(void)
{
    
}

/*******************************************************************************
 * @fn     RTC_UpdateDateTime     
 * @brief  Update the date & time when initialise MCU or one day is elapsed
 * @param  None
 * @retval None
*******************************************************************************/
void RTC_UpdateDateTime(void)
{
    uint32_t count;
    uint16_t tmp1,tmp2,tmp3,tmp4,day_week, tmp_year;
    BOOL exit = FALSE;
    BOOL isLeapYear = FALSE;
    RTCStruct t;
    
    count = RTC_GetCounter();
    
    t.date  = BKP_ReadBackupRegister(RTC_BKP_DATE_REG);
    t.month = BKP_ReadBackupRegister(RTC_BKP_MONTH_REG);
    t.year  = BKP_ReadBackupRegister(RTC_BKP_YEAR_REG);

    if (count < (SEC_PER_DAY-1))
    {
        exit = TRUE;
    }
    
    while( exit == FALSE)
    {
        if ((t.month == 1) || (t.month == 3) || (t.month == 5) ||
            (t.month == 7) || (t.month == 8) || (t.month == 10) || 
            (t.month == 12))
        {
            /* These months have 31 days */
            if (t.date < 31)
            {
                /* The next day is still in this month */
                t.date++;
            }
            else if (t.month != 12)
            {
                /* The next day is in the next month & still in this year */
                t.date = 1;
                t.month++;
            }
            else
            {
                /* The next day is in the next month & in the next year */
                t.month = 1;
                t.date = 1;
                t.year++;
            }
        }
        else if (t.month == 2)
        {
            /* This month is Feb 
            * so that it has 28 or 29 days belong to the leap year 
            */
            /* Check whether this year is a leap year or not */
            if ((t.year % 400) == 0) isLeapYear = TRUE;
            else if ((t.year % 100) == 0) isLeapYear = FALSE;
            else if ((t.year % 4) == 0) isLeapYear = TRUE;
            
            if (t.date < 28)
            {
                /* The next day is still in this month */
                t.date++;
            }
            else if ((isLeapYear == FALSE) || (t.date == 29))
            {
                /* The next day must be Mar, 01 */
                t.date = 1;
                t.month++;               
            }
            else
            {
                /* The next day is Feb, 29 since this year is the leap year */
                t.date++;
            }
        }
        else if (t.date < 30)
        {
            /* These months have 30 days, 
             * and the next day is still in this month 
             */
            t.date++;
        }
        else
        {
            /* These months have 30 days, 
             * and the next day is in the next month 
             */        
            t.date = 1;
            t.month++;
        } 
        
        if (count >= SEC_PER_DAY) 
        {
            count = count - SEC_PER_DAY;
        }
        else
        {
            exit = TRUE;
        }       
    }
        
    /* Calculate the week day 0 (Sun).. 6 (Sat)*/
    tmp_year = (uint16_t)t.year + 2000;
    if(t.month < 3)
    {
        t.month = t.month + 12;
        tmp_year = tmp_year - 1;
    }
    tmp1 = (6 * (t.month + 1)) / 10;
    tmp2 = tmp_year / 4;
    tmp3 = tmp_year / 100;
    tmp4 = tmp_year / 400;
    day_week = t.date + (2 * t.month) + tmp1 + tmp_year + tmp2 - tmp3 + tmp4 +1;
    day_week = day_week % 7;
    
    t.day = (uint8_t)day_week;
    
    /* Update the Date (day, date, month, year) */
    DateTime.day = t.day;
    DateTime.date = t.date;
    DateTime.month = t.month;
    DateTime.year = t.year;
    
    BKP_WriteBackupRegister(RTC_BKP_DATE_REG, t.date);
    BKP_WriteBackupRegister(RTC_BKP_MONTH_REG, t.month);
    BKP_WriteBackupRegister(RTC_BKP_YEAR_REG, t.year);
    
    /* Reset the RTC counter */
    RTC_SetCounter(count);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    
    /* Update the time (hour, min, sec) */
    RTC_Get();
}

/*******************************************************************************
 * @fn     RTC_Set     
 * @brief  Reinitialise the date & time of RTC
 * @param  time: current date & time
 * @retval None
*******************************************************************************/
void RTC_Set(RTCStruct t)
{
    uint32_t count;
    
    DateTime.day    = t.day  ;
    DateTime.date   = t.date ;
    DateTime.month  = t.month;
    DateTime.year   = t.year ;
    DateTime.hour   = t.hour ;
    DateTime.min    = t.min  ;
    DateTime.sec    = t.sec  ;  
    
    BKP_WriteBackupRegister(RTC_BKP_DATE_REG, t.date);
    BKP_WriteBackupRegister(RTC_BKP_MONTH_REG, t.month);
    BKP_WriteBackupRegister(RTC_BKP_YEAR_REG, t.year);
    
    count = t.hour * 3600 + t.min * 60 + t.sec;
    RTC_SetCounter(count);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

/*******************************************************************************
 * @fn     RTC_Get     
 * @brief  Return the current date & time of RTC from RTC counter value to 
 *          DateTime structure
 * @param  None
 * @retval return current date & time
*******************************************************************************/
RTCStruct RTC_Get(void)
{
    uint32_t rtc_count;
    uint32_t tmp;

    /* Update time */
    rtc_count = RTC_GetCounter();
    rtc_count = rtc_count % 86400;
    
    tmp = rtc_count / 3600;
    DateTime.hour = (uint8_t)tmp;
    
    tmp = (rtc_count  % 3600) / 60;
    DateTime.min = (uint8_t)tmp;
    
    tmp = (rtc_count % 60);
    DateTime.sec = (uint8_t)tmp;
    
    /* Update Date */
    // The date in structure must be done in RTC_Init() or Interrupt handler
    
    return DateTime;
}

/*******************************************************************************
 * @fn     RTC_Get     
 * @brief  Interrupt every 1 (sec). This interrupt checks whether one day is 
 *         elapsed or not, then update the BKP registers and DateTime structure.
 * @param  None
 * @retval None
*******************************************************************************/
void RTC_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(RTC_IRQn);
    RTC_ClearITPendingBit(RTC_IT_SEC);
    /* If counter is equal to 86399: one day was elapsed */
    /* This takes care of date change and resetting of counter in case of
    power on - Run mode/ Main supply switched on condition*/
    if(RTC_GetCounter() >= (SEC_PER_DAY-1))
    {
        /* Increment the date */
        /* Note: This large function may make the program is halted 
        *  in this interrupt 
        */
        RTC_UpdateDateTime();
        
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
        /* Reset counter value */
        RTC_SetCounter(0x0);
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
    }
    RTC_Int1sFlag = TRUE;
    /* Do something here */
}

/*******************************************************************************
 * @fn     COMM_CAN_Init     
 * @brief  Initialise CAN peripheral, and message format
 * @param  None
 * @retval None
*******************************************************************************/
void COMM_CAN_Init(void)
{
    CAN_InitTypeDef CAN_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;  

    /* Configure CAN pin: RX */
    GPIO_InitStructure.GPIO_Pin = COMM_CAN_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(COMM_CAN_PORT, &GPIO_InitStructure);
    /* Configure CAN pin: TX */
    GPIO_InitStructure.GPIO_Pin = COMM_CAN_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COMM_CAN_PORT, &GPIO_InitStructure);
    GPIO_PinRemapConfig(COMM_CAN_REMAP, ENABLE);

    /* CAN register init */
    /*
    * Note: f_CAN = f_PCLK / (CAN_Prescaler * (1 + CAN_BS1 + CAN_BS2))
    */
    
    CAN_DeInit(COMM_CANx);
    CAN_InitStructure.CAN_Prescaler = PCLK / COMM_CAN_BAUDRATE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; 
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;    
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_Init(COMM_CANx, &CAN_InitStructure);
    
    /* CAN filter init */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;  
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    /* CAN RX Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(COMM_CANx, CAN_IT_FMP0, ENABLE);
}

/*******************************************************************************
 * @fn     COMM_CAN_WriteBytes     
 * @brief  Send bytes from this master to slave
 * @param  a: address of the slave
 * @param  c: pointer to bytes that want to send. 
 * @param  l: a number of bytes that want to send. This length value must be 
 *            smaller or equal to 8 bytes.
 * @retval None
*******************************************************************************/
uint8_t COMM_CAN_WriteBytes(uint8_t a, uint8_t * c, uint8_t l)
{
    CanTxMsg msg;
    uint8_t i;
    
    if (l > 8) return 0;
    
    msg.StdId = a;
    msg.ExtId = 0;
    msg.IDE = CAN_Id_Standard;
    msg.RTR = CAN_RTR_DATA;
    msg.DLC = l;
    for (i = 0; i < l; msg.Data[i++] = *c++);
    return CAN_Transmit(COMM_CANx, &msg);
}

/*******************************************************************************
 * @fn     COMM_CAN_ReadBytes     
 * @brief  Receive bytes from slave. This function may be a callback, 
 *         which is called in interrupt handler.
 * @param  a: return the address of the slave
 * @param  c: return bytes to this array
 * @param  l: return the number of reception bytes. This length value must be 
 *            smaller or equal to 8 bytes.
 * @retval None
*******************************************************************************/
void COMM_CAN_ReadBytes(uint8_t * a, uint8_t * c, uint8_t *l)
{
    CanRxMsg msg;
    uint8_t i;
    
    CAN_Receive(COMM_CANx, CAN_FIFO0, &msg);
    *a = msg.StdId;
    *l = msg.DLC;
    for (i = 0; i < msg.DLC; *c++ = msg.Data[i++]);
}

/*******************************************************************************
 * @fn     USB_LP_CAN1_RX0_IRQHandler     
 * @brief  CAN Reception Interrupt
 * @param  None
 * @retval None
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    uint8_t rx_dat[8];
    uint8_t a;
    uint8_t l;
    
    COMM_CAN_RXFlag = TRUE;
    COMM_CAN_ReadBytes(&a, rx_dat, &l);
    rx_dat[l] = '\r'; rx_dat[l+1] = '\n';
    PC_USART_DMA_WriteBytes(rx_dat, l+2);
    if (a == 9) LED_PULSE_Toggle();
    CAN_ClearITPendingBit(COMM_CANx, CAN_IT_FMP0);
}

/*******************************************************************************
 * @fn     DRV_SPI_Init     
 * @brief  Driver Initialise
 * @param  None
 * @retval None
*******************************************************************************/
void DRV_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	//	Configure SRCLK, SDI
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;//GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = DRV_SPI_SRCLK_PIN | DRV_SPI_SDI_PIN;
	GPIO_Init(DRV_SPI_PORT, &GPIO_InitStructure);
   
    //	Configure OE, RCLK
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = DRV_SPI_OE_PIN | DRV_SPI_RCLK_PIN;
	GPIO_Init(DRV_SPI_PORT, &GPIO_InitStructure);
	GPIO_SetBits(DRV_SPI_PORT, DRV_SPI_OE_PIN); // Deselect CS pin
    
//     //  SPI configuration 
// 	SPI_I2S_DeInit(DRV_SPIx);  
// 	SPI_InitStructure.SPI_Direction 	    = SPI_Direction_1Line_Tx; //	1-way
// 	SPI_InitStructure.SPI_DataSize 		    = SPI_DataSize_8b; //	8 bits
// 	SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_Low;							
// 	SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_1Edge;
// 	SPI_InitStructure.SPI_NSS 				= SPI_NSS_Soft;	//	pin Chip-select be controlled by software
// 	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; // APB2 = 72M, Prescale = 64 --> CLK = 72/64 = 1M
// 	SPI_InitStructure.SPI_FirstBit 			= SPI_FirstBit_MSB;	//	MSB bit first out
// 	SPI_InitStructure.SPI_CRCPolynomial 	= 7; //	0007 is reset value
// 	SPI_InitStructure.SPI_Mode 				= SPI_Mode_Master; //	master mode
// 	SPI_Init(DRV_SPIx, &SPI_InitStructure);
// 	//	Enable DRV_SPIx
//     SPI_Cmd(DRV_SPIx, ENABLE);
}

/*******************************************************************************
 * @fn     DRV_SPI_WriteBytes     
 * @brief  Write bytes to driver
 * @param  None
 * @retval None
*******************************************************************************/
void DRV_SPI_WriteBytes(uint8_t *c, uint8_t l)
{
    uint8_t i, j;
    uint8_t d;
    
    //DRV_SPI_Do();
     
//     for (i = 0; i < l ; i++)
//     {
//         // Loop while DR register in not empty 
//         while (SPI_I2S_GetFlagStatus(DRV_SPIx, SPI_I2S_FLAG_TXE) == RESET);
//         
//         // Send byte through the SPIx peripheral
//         SPI_I2S_SendData(DRV_SPIx, c[i]);
//     }
    
    for (i = 0; i < l ; i++)
    {
        // MSByte first
        d = c[l - 1 - i];
        for (j = 0; j < 8 ; j++)
        {
            // MSB first
            //if (d & (1<<(7-j))) GPIO_SetBits(DRV_SPI_PORT, DRV_SPI_SDI_PIN);
            // LSbit first
            if (d & (1<<j)) GPIO_SetBits(DRV_SPI_PORT, DRV_SPI_SDI_PIN);
            else GPIO_ResetBits(DRV_SPI_PORT, DRV_SPI_SDI_PIN);
            GPIO_ResetBits(DRV_SPI_PORT, DRV_SPI_SRCLK_PIN);
            GPIO_SetBits(DRV_SPI_PORT, DRV_SPI_SRCLK_PIN); // rising edge
        }
    }

    GPIO_ResetBits(DRV_SPI_PORT, DRV_SPI_RCLK_PIN);
    GPIO_SetBits(DRV_SPI_PORT, DRV_SPI_RCLK_PIN); // rising edge
    GPIO_ResetBits(DRV_SPI_PORT, DRV_SPI_RCLK_PIN);
    
    DRV_SPI_Eo();
}

/*******************************************************************************
 * @fn     DRV_SPI_Eo     
 * @brief  Enable output
 * @param  None
 * @retval None
*******************************************************************************/
void DRV_SPI_Eo(void)
{
    GPIO_ResetBits(DRV_SPI_PORT, DRV_SPI_OE_PIN); // output data
}

/*******************************************************************************
 * @fn     DRV_SPI_Do     
 * @brief  Disable output - HiZ
 * @param  None
 * @retval None
*******************************************************************************/
void DRV_SPI_Do(void)
{
    GPIO_SetBits(DRV_SPI_PORT, DRV_SPI_OE_PIN); // high Z
}
/********************************************************************************
* 					            PRIVATE FUNCTIONS
********************************************************************************/


