/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: valve.c
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 04-Aug-13
 *	Description	    : Middle layer
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "valve.h"

/********************************************************************************
* 							        DEFINE
********************************************************************************/


/********************************************************************************
* 					            GLOBAL VARIABLES
********************************************************************************/
uint8_t VALVE_IData[VALVE_ITOTAL];


/********************************************************************************
* 					           PRIVATE VARIABLES
********************************************************************************/


/********************************************************************************
* 					           PUCLIC FUNCTIONS
********************************************************************************/

/*******************************************************************************
 * @fn     VALVE_Init     
 * @brief  Initialise valves to Idle state
 * @param  None
 * @retval None
*******************************************************************************/
void VALVE_Init(void)
{
    VALVE_SSet(IOFF);
}

/*******************************************************************************
 * @fn     VALVE_Test     
 * @brief  Testing whether all valves are running well or not
 * @param  None
 * @retval None
*******************************************************************************/
void VALVE_Test(void)
{
    
}

/*******************************************************************************
 * @fn     VALVE_VSet     
 * @brief  Setting a state to each valve
 * @param  v: valve position (from 0 to VALVE_TOTAL)
 * @param  s: valve state. It can be one of the enumerations {VIDLE, VON, VOFF}
 * @retval None
*******************************************************************************/
void VALVE_VSet(uint16_t vn, VALVE_VSTATE s)
{
    uint16_t in, bn;
    in = vn / 4;
    bn = vn % 4;
    VALVE_IData[in] &= (~(0x03 << bn));
    VALVE_IData[in] |= (s << bn);
}

/*******************************************************************************
 * @fn     VALVE_SetAll     
 * @brief  Setting all valves are in the same state
 * @param  s: the value are setted to data. 
 *              It can be one of the enumerations {IIDLE, ION, IOFF}
 * @retval None
*******************************************************************************/
void VALVE_ISet(uint16_t in, VALVE_ISTATE s)
{
    VALVE_IData[in] = s;
}

/*******************************************************************************
 * @fn     VALVE_SSet     
 * @brief  Setting all valves are in the same state
 * @param  s: the value are setted to data. 
 *              It can be one of the enumerations {IIDLE, ION, IOFF}
 * @retval None
*******************************************************************************/
void VALVE_SSet(VALVE_ISTATE s)
{
    uint8_t i;
    
    for (i = 0; i < VALVE_ITOTAL; VALVE_IData[i] = s, i--);    
}
/*******************************************************************************
 * @fn     VALVE_Write     
 * @brief  Valve is running
 * @param  None
 * @retval None
*******************************************************************************/
void VALVE_Write(void)
{
    DRV_SPI_WriteBytes(VALVE_IData, VALVE_ITOTAL);
    TIM_REF_DelayTms(VALVE_CTRL_DT);
    //TIM_REF_DelayTms(1);
    VALVE_SSet(IOFF);
    DRV_SPI_WriteBytes(VALVE_IData, VALVE_ITOTAL);
    TIM_REF_DelayTms(VALVE_REST_DT);
    //TIM_REF_DelayTms(1);
}

/********************************************************************************
* 					            PRIVATE FUNCTIONS
********************************************************************************/


