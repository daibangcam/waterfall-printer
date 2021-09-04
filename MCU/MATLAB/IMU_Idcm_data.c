/*
 * File: IMU_Idcm_data.c
 *
 * Real-Time Workshop code generated for Simulink model IMU_Idcm.
 *
 * Model version                        : 1.45
 * Real-Time Workshop file version      : 7.6  (R2010b)  03-Aug-2010
 * Real-Time Workshop file generated on : Tue May 28 23:40:41 2013
 * TLC version                          : 7.6 (Jul 13 2010)
 * C/C++ source code generated on       : Tue May 28 23:40:42 2013
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "IMU_Idcm.h"
#include "IMU_Idcm_private.h"

/* Block parameters (auto storage) */
Parameters_IMU_Idcm IMU_Idcm_P = {
  /*  Expression: [1;0;0;0]
   * Referenced by: '<S1>/Unit Delay1'
   */
  { 1.0, 0.0, 0.0, 0.0 },
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Unit Delay'
                                        */

  /*  Expression: [0.0099; 0.0099; 0.0099; 0.0099]
   * Referenced by: '<Root>/delta'
   */
  { 0.0099, 0.0099, 0.0099, 0.0099 },
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<Root>/Gain'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S9>/Gain'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S7>/Gain'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S6>/Gain'
                                        */
  572.95779513082323,                  /* Expression: 1800/pi
                                        * Referenced by: '<Root>/Gain2'
                                        */
  255.0,                               /* Expression: 255
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  200.0,                               /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  100.0,                               /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
