/*******************************************************************************
 *
 * Project: BKWAR
 * 
 ******************************************************************************/

/*******************************************************************************
 *
 *	Module			: war.h
 *  Tool		  	: KeilC ARM 4.22a
 *	Chip		  	: STM32F103C8
 * 	History			: Begin at 20-Oct-13
 *	Description	    : Application layer, 
 *                    This header defines all demonstration for system
 *				
 *	Author			: Dang Anh Tung			
 *				
 ******************************************************************************/

#ifndef __WAR_H
#define __WAR_H
 
 
/*******************************************************************************
* 							        IMPORT
******************************************************************************/
#include "valve.h"
#include "type.h"

/********************************************************************************
* 							        TYPEDEF
********************************************************************************/
typedef void (*pFunc)(uint32_t dt);   /* con tro den ham: void func(uint32_t dt) */


/********************************************************************************
* 							        DEFINE
********************************************************************************/
//#define WAR_ROW     50
//#define WAR_COL     11
//#define FUNC_NUM    10
//#define WAR_NUM_IMG_MAX     (uint8_t)6
//#define WAR_DISP_LIST_NUM   (uint8_t)11

#define WAR_ROW     50
#define WAR_COL     8
#define FUNC_NUM    10
#define WAR_NUM_IMG_MAX     (uint8_t)6
#define WAR_DISP_LIST_NUM   (uint8_t)13

/********************************************************************************
* 					        GLOBAL VARIABLES
********************************************************************************/
extern pFunc WAR_DispList[WAR_DISP_LIST_NUM];
/********************************************************************************
* 					        PRIVATE VARIABLES
********************************************************************************/



/********************************************************************************
* 					        PUBLIC FUNCTIONS
********************************************************************************/
void WAR_Write(uint8_t row, uint8_t col, uint8_t * c, uint32_t dt);
void WAR_DispImage(IMG_LIST imgList, uint8_t num_img, DISPStruct conf);

void WAR_Test(void);


void WAR_Disp_Digit0(uint32_t dt);
void WAR_Disp_Digit1(uint32_t dt);
void WAR_Disp_Digit2(uint32_t dt);
void WAR_Disp_Digit3(uint32_t dt);
void WAR_Disp_Digit4(uint32_t dt);
void WAR_Disp_Digit5(uint32_t dt);
void WAR_Disp_Digit6(uint32_t dt);
void WAR_Disp_Digit7(uint32_t dt);
void WAR_Disp_Digit8(uint32_t dt);
void WAR_Disp_Digit9(uint32_t dt);
void WAR_Disp_Digit10(uint32_t dt);
void WAR_Disp_Digit11(uint32_t dt);
void WAR_Disp_Digit12(uint32_t dt);

void WAR_Disp_Pattern0(uint32_t dt);
void WAR_Disp_Pattern1(uint32_t dt);
void WAR_Disp_Pattern2(uint32_t dt);
void WAR_Disp_Pattern3(uint32_t dt);
void WAR_Disp_Pattern4(uint32_t dt);
void WAR_Disp_Pattern5(uint32_t dt);
void WAR_Disp_Pattern6(uint32_t dt);
//void WAR_Disp_Pattern7(uint32_t dt);
//void WAR_Disp_Pattern8(uint32_t dt);
//void WAR_Disp_Pattern9(uint32_t dt);

void WAR_Disp_Num0(uint32_t dt);
//void WAR_Disp_Num1(uint32_t dt);
//void WAR_Disp_Num2(uint32_t dt);
//void WAR_Disp_Num3(uint32_t dt);
//void WAR_Disp_Num4(uint32_t dt);
//void WAR_Disp_Num5(uint32_t dt);
//void WAR_Disp_Num6(uint32_t dt);
//void WAR_Disp_Num7(uint32_t dt);
//void WAR_Disp_Num8(uint32_t dt);
//void WAR_Disp_Num9(uint32_t dt);
//void WAR_Disp_Num10(uint32_t dt);
//void WAR_Disp_Num11(uint32_t dt);
//void WAR_Disp_Num12(uint32_t dt);

//void WAR_Disp_Curve0(uint32_t dt);
//void WAR_Disp_Curve1(uint32_t dt);
//void WAR_Disp_Curve2(uint32_t dt);
//void WAR_Disp_Curve3(uint32_t dt);
//void WAR_Disp_Curve4(uint32_t dt);
//void WAR_Disp_Curve5(uint32_t dt);
//void WAR_Disp_Curve6(uint32_t dt);
//void WAR_Disp_Curve7(uint32_t dt);
//void WAR_Disp_Curve8(uint32_t dt);
//void WAR_Disp_Curve9(uint32_t dt);

//void WAR_Disp_Heart(uint32_t dt);
//void WAR_Disp_Caro(uint32_t dt);
//void WAR_Disp_BKW(uint32_t dt);
//void WAR_Disp_Sgat(uint32_t dt);
//void WAR_Disp_Yahoo(uint32_t dt);
//void WAR_Disp_Iloveu(uint32_t dt);
//void WAR_Disp_Time(uint32_t dt);
//void WAR_Disp_2014(uint32_t dt);
//void WAR_Disp_Horse(uint32_t dt);
//void WAR_Disp_Cubid(uint32_t dt);
//void WAR_Disp_Tulip(uint32_t dt);
//void WAR_Disp_Money(uint32_t dt);
//void WAR_Disp_Pigeon(uint32_t dt);
//void WAR_Disp_Dayleo1(uint32_t dt);
//void WAR_Disp_Bamboo(uint32_t dt);
//void WAR_Disp_Dayleo2(uint32_t dt);
//void WAR_Disp_DayleoLong(uint32_t dt);

#endif /* __WAR_H */
