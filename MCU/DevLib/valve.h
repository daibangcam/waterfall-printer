/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: valve.h
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 04-Aug-13
 *                    - 20-Oct-13: Change to control 1 pin - 1 valve
 *	Description	    : Middle layer 
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/

#ifndef __VALVE_H
#define __VALVE_H
 
/*******************************************************************************
*            VALVE CONFIGURATION
         --------         --------                   --------
        |   0    | ----- |   1    |------ ... ------|   n    |
         --------         --------                   --------
         ||||||||         ||||||||                   ||||||||
        ->D0[7:0]       ->D1[7:0]                   ->Dn[7:0]
        ->V[0:7]        ->V[8:15]          ...      ->V[8n:(8n+7)]  // Each valve
        ->I[0]          ->I[1]            ...       ->I[n]          // Each IC (8 valves)
        ->S[0]                                                      // System (all valves) 
ON:    0b11111111       0b11111111        ...       0b11111111
OFF:   0b00000000       0b00000000        ...       0b00000000

* Note:
+ prefix notation: 
    VALVE_ : this is a component in valve.c or valve.h
    VALVE_V: this is a component in valve.c or valve.h and assign to each valve
    VALVE_I: this is a component in valve.c or valve.h and assign to each IC (8 valves)
    VALVE_S: this is a component in valve.c or valve.h and assign to whole system
 ******************************************************************************/
 
 /*******************************************************************************
 *      VALVE CONTROL TIMING
 Time slot:
 |---- 0(ms)
 |control time: Valve is ON or OFF
 |---- CTRL_DT (ms)
 |... next cycle
 |...
 |---- REST_DT
 |rest time
  ******************************************************************************/
 
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "mcu_board.h"

/********************************************************************************
* 							        TYPEDEF
********************************************************************************/
#define VON     (uint8_t)0x01
#define VOFF    (uint8_t)0x00
#define ION     (uint8_t)0xFF
#define IOFF    (uint8_t)0x00


/********************************************************************************
* 							        DEFINE
********************************************************************************/
/* Valve parameters */
//#define VALVE_VTOTAL            (uint16_t)264
//#define VALVE_ITOTAL            (uint16_t)88// WARN:this value must be equal or greater than the VALVE_TOTAL/8

#define VALVE_VTOTAL            (uint16_t)192
#define VALVE_ITOTAL            (uint16_t)64// WARN:this value must be equal or greater than the VALVE_TOTAL/8

#define VALVE_CTRL_DT           10//ms

/********************************************************************************
* 					        GLOBAL VARIABLES
********************************************************************************/
extern uint8_t VALVE_IData[VALVE_ITOTAL];


/********************************************************************************
* 					        PRIVATE VARIABLES
********************************************************************************/

/********************************************************************************
* 					        PUBLIC FUNCTIONS
********************************************************************************/

void VALVE_Init(void);
void VALVE_Test(void);
void VALVE_VSet(uint16_t vn, uint8_t s);
void VALVE_ISet(uint16_t in, uint8_t s);
void VALVE_SSet(uint8_t *s);
void VALVE_SWrite(void);


#endif /* __VALVE_H */
