/*
 * File: IMU_Idcm_data.c
 *
 * Real-Time Workshop code generated for Simulink model IMU_Idcm.
 *
 * Model version                        : 1.67
 * Real-Time Workshop file version      : 7.6  (R2010b)  03-Aug-2010
 * Real-Time Workshop file generated on : Tue May 28 23:28:33 2013
 * TLC version                          : 7.6 (Jul 13 2010)
 * C/C++ source code generated on       : Tue May 28 23:28:35 2013
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
  /*  Expression: [0;0;0]
   * Referenced by: '<S3>/Unit Delay'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: 1e-2*eye(3)
   * Referenced by: '<S3>/Unit Delay1'
   */
  { 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01 },

  /*  Expression: Q2
   * Referenced by: '<S1>/Q2'
   */
  { 8.0E-12, 0.0, 0.0, 0.0, 8.0E-12, 0.0, 0.0, 0.0, 8.0E-12 },

  /*  Expression: Rmag
   * Referenced by: '<S1>/Rmag'
   */
  { 2.0E-6, 0.0, 0.0, 0.0, 2.0E-6, 0.0, 0.0, 0.0, 2.0E-6 },
  0.2,                                 /* Expression: mag_Rbar
                                        * Referenced by: '<S1>/mag_Rbar'
                                        */
  1000.0,                              /* Expression: mag_sigma
                                        * Referenced by: '<S1>/mag_sigma'
                                        */

  /*  Expression: [0;0;0]
   * Referenced by: '<S2>/Unit Delay'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: 1e-2*eye(3)
   * Referenced by: '<S2>/Unit Delay1'
   */
  { 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01 },

  /*  Expression: Q1
   * Referenced by: '<S1>/Q1'
   */
  { 8.0E-11, 0.0, 0.0, 0.0, 8.0E-11, 0.0, 0.0, 0.0, 8.0E-11 },

  /*  Expression: Racc
   * Referenced by: '<S1>/Racc'
   */
  { 4.0E-5, 0.0, 0.0, 0.0, 4.0E-5, 0.0, 0.0, 0.0, 4.0E-5 },
  0.1,                                 /* Expression: acc_Rbar
                                        * Referenced by: '<S1>/acc_Rbar'
                                        */
  5.0,                                 /* Expression: acc_sigma
                                        * Referenced by: '<S1>/acc_sigma'
                                        */
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<Root>/Gain'
                                        */
  0.00981,                             /* Expression: 0.00981
                                        * Referenced by: '<Root>/Gain1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Unit Delay3'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/Unit Delay2'
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
