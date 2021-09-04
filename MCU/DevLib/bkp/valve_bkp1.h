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
        ->V[0:3]        ->V[4:7]          ...       ->V[4n:(4n+3)]  // Each valve
        ->I[0]          ->I[1]            ...       ->I[n]          // Each IC (4 valves)
        ->S[0]                                                      // System (all valves)
IDLE:  0b00000000       0b00000000        ...       0b00000000    
ON:    0b01010101       0b01010101        ...       0b01010101
OFF:   0b10101010       0b10101010        ...       0b10101010
ERROR: 0b11111111       0b11111111        ...       0b11111111

* Note:
+ prefix notation: 
    VALVE_ : this is a component in valve.c or valve.h
    VALVE_V: this is a component in valve.c or valve.h and assign to each valve
    VALVE_I: this is a component in valve.c or valve.h and assign to each IC (4 valves)
    VALVE_S: this is a component in valve.c or valve.h and assign to whole system
 ******************************************************************************/
 
 /*******************************************************************************
 *      VALVE CONTROL
 Time slot:
 |---- 0(ms)
 |control time: Valve is ON or IDLE
 |---- CTRL_DT (ms)
 |rest time: Valve is OFF
 |---- (CTRL_DT + REST_DT) (ms)
 |... next cycle
  ******************************************************************************/
 
 
 
 
 
 /*******************************************************************************
 * 							        IMPORT
 ******************************************************************************/
#include "mcu_board.h"

/********************************************************************************
* 							        TYPEDEF
********************************************************************************/
typedef enum
{
    VIDLE = (uint8_t)0x00,
    VON   = (uint8_t)0x01,
    VOFF  = (uint8_t)0x02,
}VALVE_VSTATE;

typedef enum
{
    IIDLE = (uint8_t)0x00,
    ION   = (uint8_t)0x55,
    IOFF  = (uint8_t)0xAA,
}VALVE_ISTATE;

/********************************************************************************
* 							        DEFINE
********************************************************************************/
/* Valve parameters */
#define VALVE_VTOTAL            10
#define VALVE_ITOTAL            3// WARN:this value must be greater than the VALVE_TOTAL/4
#define VALVE_CTRL_DT           100//ms
#define VALVE_REST_DT           20//ms

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
void VALVE_VSet(uint16_t vn, VALVE_VSTATE s);
void VALVE_ISet(uint16_t in, VALVE_ISTATE s);
void VALVE_SSet(VALVE_ISTATE s);
void VALVE_Write(void);



#endif /* __VALVE_H */
