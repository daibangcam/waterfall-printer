/*
 * File: IMU_Idcm.c
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

/* user code (top of source file) */
/* System '<Root>' */
#include "stm32f4xx.h"
#include "driver.h"

/* Exported block signals */
real_T fgyro[3];                       /* '<Root>/Gyro  Sensor' */
real_T facc[3];                        /* '<Root>/Acc  Sensor' */
real_T fmag[3];                        /* '<Root>/Mag  Sensor' */
real_T Out1[3];                        /* '<Root>/Gain2' */
real_T Out2;                           /* '<Root>/Pulse Generator' */

/* Block states (auto storage) */
D_Work_IMU_Idcm IMU_Idcm_DWork;

/* Real-time model */
RT_MODEL_IMU_Idcm IMU_Idcm_M_;
RT_MODEL_IMU_Idcm *IMU_Idcm_M = &IMU_Idcm_M_;
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    return (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    return atan2(u0 > 0.0 ? 1.0 : -1.0, u1 > 0.0 ? 1.0 : -1.0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      return RT_PI / 2.0;
    } else if (u0 < 0.0) {
      return -(RT_PI / 2.0);
    } else {
      return 0.0;
    }
  } else {
    return atan2(u0, u1);
  }
}

/* Model step function */
void IMU_Idcm_step(void)
{
  real_T qk[4];
  real_T phi;
  real_T theta;
  real_T qs[4];
  real_T rtb_qk[4];
  real_T tmp[16];
  real_T tmp_0[16];
  int32_T i;
  real_T mag_idx;
  real_T mag_idx_0;
  real_T mag_idx_1;
  real_T rtb_TmpSignalConversionAtSFun_0;
  real_T rtb_TmpSignalConversionAtSFun_1;
  real_T rtb_TmpSignalConversionAtSFun_2;

  {
    /* user code (Output function Header) */

    /* System '<Root>' */
    uint16_t i;

    /* user code (Output function Body) */

    /* System '<Root>' */
    read_adis();
    for (i=0; i<3; i++) {
      fgyro[i] = marg[i+1];
      facc[i] = marg[i+4];
      fmag[i] = marg[i+7];
    }

    /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport4' incorporates:
     *  Gain: '<Root>/Gain'
     *  Inport: '<Root>/Gyro  Sensor'
     */
    rtb_TmpSignalConversionAtSFun_0 = IMU_Idcm_P.Gain_Gain * fgyro[0];
    rtb_TmpSignalConversionAtSFun_1 = IMU_Idcm_P.Gain_Gain * fgyro[1];
    rtb_TmpSignalConversionAtSFun_2 = IMU_Idcm_P.Gain_Gain * fgyro[2];

    /* Embedded MATLAB: '<S1>/QUEST filter' incorporates:
     *  Constant: '<Root>/delta'
     *  Inport: '<Root>/Acc  Sensor'
     *  Inport: '<Root>/Mag  Sensor'
     *  UnitDelay: '<S1>/Unit Delay'
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    qk[0] = IMU_Idcm_DWork.UnitDelay1_DSTATE[0];
    qk[1] = IMU_Idcm_DWork.UnitDelay1_DSTATE[1];
    qk[2] = IMU_Idcm_DWork.UnitDelay1_DSTATE[2];
    qk[3] = IMU_Idcm_DWork.UnitDelay1_DSTATE[3];

    /* Embedded MATLAB Function 'QUEST Filter/QUEST filter': '<S3>:1' */
    /* '<S3>:1:4' */
    /* '<S3>:1:6' */
    /*  gyro measurement is considered as input value of the model */
    /* '<S3>:1:7' */
    /*  measurement value from accelerometer sensor */
    /* '<S3>:1:8' */
    /*  measurement value from magnetic sensor */
    /* '<S3>:1:9' */
    phi = sqrt((rt_pow_snf(fmag[0], 2.0) + rt_pow_snf(fmag[1], 2.0)) +
               rt_pow_snf(fmag[2], 2.0));
    mag_idx_1 = fmag[0] / phi;
    mag_idx = fmag[1] / phi;
    mag_idx_0 = fmag[2] / phi;

    /*  from accelerometer */
    /* '<S3>:1:15' */
    phi = rt_atan2d_snf(facc[1], facc[2]);

    /* '<S3>:1:16' */
    theta = asin((-facc[0]) / sqrt((rt_pow_snf(facc[0], 2.0) + rt_pow_snf(facc[1],
      2.0)) + rt_pow_snf(facc[2], 2.0)));

    /*  from magnetic sensor */
    /* '<S3>:1:19' */
    /* '<S3>:1:20' */
    /* '<S3>:1:21' */
    /* '<S3>:1:25' */
    mag_idx_1 = rt_atan2d_snf(-(mag_idx * cos(phi) - mag_idx_0 * sin(phi)),
      (mag_idx * sin(theta) * sin(phi) + mag_idx_1 * cos(theta)) + mag_idx_0 *
      sin(theta) * cos(phi));

    /* =========================================================================== */
    /* -- Convert euler angle into quaternion */
    /*  initial quaternion */
    /* '<S3>:1:70' */
    /* '<S3>:1:72' */
    /* '<S3>:1:74' */
    /* '<S3>:1:76' */
    /* '<S3>:1:78' */
    qs[0] = cos(phi / 2.0) * cos(theta / 2.0) * cos(mag_idx_1 / 2.0) + sin(phi /
      2.0) * sin(theta / 2.0) * sin(mag_idx_1 / 2.0);
    qs[1] = sin(phi / 2.0) * cos(theta / 2.0) * cos(mag_idx_1 / 2.0) - cos(phi /
      2.0) * sin(theta / 2.0) * sin(mag_idx_1 / 2.0);
    qs[2] = cos(phi / 2.0) * sin(theta / 2.0) * cos(mag_idx_1 / 2.0) + sin(phi /
      2.0) * cos(theta / 2.0) * sin(mag_idx_1 / 2.0);
    qs[3] = cos(phi / 2.0) * cos(theta / 2.0) * sin(mag_idx_1 / 2.0) - sin(phi /
      2.0) * sin(theta / 2.0) * cos(mag_idx_1 / 2.0);

    /* '<S3>:1:79' */
    phi = sqrt(((rt_pow_snf(qs[0], 2.0) + rt_pow_snf(qs[1], 2.0)) + rt_pow_snf
                (qs[2], 2.0)) + rt_pow_snf(qs[3], 2.0));
    qs[0] = qs[0] / phi;
    qs[1] = qs[1] / phi;
    qs[2] = qs[2] / phi;
    qs[3] = qs[3] / phi;
    if (qs[0] < 0.0) {
      /* '<S3>:1:26' */
      /* '<S3>:1:27' */
      qs[0] = -qs[0];
      qs[1] = -qs[1];
      qs[2] = -qs[2];
      qs[3] = -qs[3];
    }

    /*  initial value of qk  */
    if (IMU_Idcm_DWork.UnitDelay_DSTATE == 1.0) {
      /* '<S3>:1:31' */
      /* '<S3>:1:32' */
      qk[0] = qs[0];
      qk[1] = qs[1];
      qk[2] = qs[2];
      qk[3] = qs[3];
    }

    /*  compute error value between gyros and (accs + mags) */
    /* '<S3>:1:36' */
    /*  compute estimated value of qk using first order approximation */
    /* '<S3>:1:39' */
    /* '<S3>:1:44' */
    tmp[0] = 0.0;
    tmp[4] = -rtb_TmpSignalConversionAtSFun_0;
    tmp[8] = -rtb_TmpSignalConversionAtSFun_1;
    tmp[12] = -rtb_TmpSignalConversionAtSFun_2;
    tmp[1] = rtb_TmpSignalConversionAtSFun_0;
    tmp[5] = 0.0;
    tmp[9] = rtb_TmpSignalConversionAtSFun_2;
    tmp[13] = -rtb_TmpSignalConversionAtSFun_1;
    tmp[2] = rtb_TmpSignalConversionAtSFun_1;
    tmp[6] = -rtb_TmpSignalConversionAtSFun_2;
    tmp[10] = 0.0;
    tmp[14] = rtb_TmpSignalConversionAtSFun_0;
    tmp[3] = rtb_TmpSignalConversionAtSFun_2;
    tmp[7] = rtb_TmpSignalConversionAtSFun_1;
    tmp[11] = -rtb_TmpSignalConversionAtSFun_0;
    tmp[15] = 0.0;
    for (i = 0; i < 4; i++) {
      tmp_0[i << 2] = tmp[i << 2] * 0.005;
      tmp_0[1 + (i << 2)] = tmp[(i << 2) + 1] * 0.005;
      tmp_0[2 + (i << 2)] = tmp[(i << 2) + 2] * 0.005;
      tmp_0[3 + (i << 2)] = tmp[(i << 2) + 3] * 0.005;
    }

    for (i = 0; i < 4; i++) {
      rtb_qk[i] = ((((tmp_0[i + 4] * qk[1] + tmp_0[i] * qk[0]) + tmp_0[i + 8] *
                     qk[2]) + tmp_0[i + 12] * qk[3]) + qk[i]) + (qs[i] - qk[i]) *
        IMU_Idcm_P.delta_Value[i];
    }

    /*  normalization */
    /* '<S3>:1:47' */
    phi = sqrt(((rt_pow_snf(rtb_qk[0], 2.0) + rt_pow_snf(rtb_qk[1], 2.0)) +
                rt_pow_snf(rtb_qk[2], 2.0)) + rt_pow_snf(rtb_qk[3], 2.0));
    rtb_qk[0] = rtb_qk[0] / phi;
    rtb_qk[1] = rtb_qk[1] / phi;
    rtb_qk[2] = rtb_qk[2] / phi;
    rtb_qk[3] = rtb_qk[3] / phi;
    if (rtb_qk[0] < 0.0) {
      /* '<S3>:1:49' */
      /* '<S3>:1:50' */
      rtb_qk[0] = -rtb_qk[0];
      rtb_qk[1] = -rtb_qk[1];
      rtb_qk[2] = -rtb_qk[2];
      rtb_qk[3] = -rtb_qk[3];
    }

    /*  compute external acceleration */
    /* exacc = R'*acc - [0; 0; 1000]; */
    /* '<S3>:1:62' */
    /* '<S3>:1:63' */

    /* Sqrt: '<S10>/sqrt' incorporates:
     *  Product: '<S11>/Product'
     *  Product: '<S11>/Product1'
     *  Product: '<S11>/Product2'
     *  Product: '<S11>/Product3'
     *  Sum: '<S11>/Sum'
     */
    phi = sqrt(((rtb_qk[0] * rtb_qk[0] + rtb_qk[1] * rtb_qk[1]) + rtb_qk[2] *
                rtb_qk[2]) + rtb_qk[3] * rtb_qk[3]);

    /* Product: '<S4>/Product' */
    theta = rtb_qk[0] / phi;

    /* Product: '<S4>/Product1' */
    mag_idx_1 = rtb_qk[1] / phi;

    /* Product: '<S4>/Product2' */
    mag_idx = rtb_qk[2] / phi;

    /* Product: '<S4>/Product3' */
    phi = rtb_qk[3] / phi;

    /* Gain: '<Root>/Gain2' incorporates:
     *  Gain: '<S6>/Gain'
     *  Gain: '<S7>/Gain'
     *  Gain: '<S9>/Gain'
     *  Product: '<S5>/Product'
     *  Product: '<S5>/Product1'
     *  Product: '<S5>/Product2'
     *  Product: '<S5>/Product3'
     *  Product: '<S6>/Product2'
     *  Product: '<S6>/Product3'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product2'
     *  Product: '<S8>/Product'
     *  Product: '<S8>/Product1'
     *  Product: '<S8>/Product2'
     *  Product: '<S8>/Product3'
     *  Product: '<S9>/Product1'
     *  Product: '<S9>/Product2'
     *  Sum: '<S5>/Sum'
     *  Sum: '<S6>/Sum'
     *  Sum: '<S7>/Sum'
     *  Sum: '<S8>/Sum'
     *  Sum: '<S9>/Sum'
     *  Trigonometry: '<S2>/Trigonometric Function1'
     *  Trigonometry: '<S2>/Trigonometric Function2'
     *  Trigonometry: '<S2>/Trigonometric Function3'
     */
    Out1[0] = rt_atan2d_snf((theta * mag_idx_1 + mag_idx * phi) *
      IMU_Idcm_P.Gain_Gain_n, ((theta * theta - mag_idx_1 * mag_idx_1) - mag_idx
      * mag_idx) + phi * phi) * IMU_Idcm_P.Gain2_Gain;
    mag_idx_0 = (theta * mag_idx - mag_idx_1 * phi) * IMU_Idcm_P.Gain_Gain_g;
    Out1[1] = asin(mag_idx_0 >= 1.0 ? 1.0 : mag_idx_0 <= -1.0 ? -1.0 : mag_idx_0)
      * IMU_Idcm_P.Gain2_Gain;
    Out1[2] = rt_atan2d_snf((phi * theta + mag_idx_1 * mag_idx) *
      IMU_Idcm_P.Gain_Gain_i, ((theta * theta + mag_idx_1 * mag_idx_1) - mag_idx
      * mag_idx) - phi * phi) * IMU_Idcm_P.Gain2_Gain;

    /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
    Out2 = ((real_T)IMU_Idcm_DWork.clockTickCounter <
            IMU_Idcm_P.PulseGenerator_Duty) && (IMU_Idcm_DWork.clockTickCounter >=
      0) ? IMU_Idcm_P.PulseGenerator_Amp : 0.0;
    if ((real_T)IMU_Idcm_DWork.clockTickCounter >=
        IMU_Idcm_P.PulseGenerator_Period - 1.0) {
      IMU_Idcm_DWork.clockTickCounter = 0;
    } else {
      IMU_Idcm_DWork.clockTickCounter = IMU_Idcm_DWork.clockTickCounter + 1;
    }

    /* user code (Output function Trailer) */

    /* System '<Root>' */
    for (i=0; i<3; i++)
      euler[i] = Out1[i];
    if (Out2 != 0.0)
      GPIO_SetBits(GPIOB, GPIO_Pin_1);
    else
      GPIO_ResetBits(GPIOB, GPIO_Pin_1);
  }

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  IMU_Idcm_DWork.UnitDelay1_DSTATE[0] = rtb_qk[0];
  IMU_Idcm_DWork.UnitDelay1_DSTATE[1] = rtb_qk[1];
  IMU_Idcm_DWork.UnitDelay1_DSTATE[2] = rtb_qk[2];
  IMU_Idcm_DWork.UnitDelay1_DSTATE[3] = rtb_qk[3];

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  IMU_Idcm_DWork.UnitDelay_DSTATE = 0.0;
}

/* Model initialize function */
void IMU_Idcm_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(IMU_Idcm_M, (NULL));

  /* block I/O */

  /* exported global signals */
  Out1[0] = 0.0;
  Out1[1] = 0.0;
  Out1[2] = 0.0;
  Out2 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&IMU_Idcm_DWork, 0,
                sizeof(D_Work_IMU_Idcm));

  /* external inputs */
  (void) memset(fgyro, 0,
                3U*sizeof(real_T));
  (void) memset(facc, 0,
                3U*sizeof(real_T));
  (void) memset(fmag, 0,
                3U*sizeof(real_T));

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  IMU_Idcm_DWork.clockTickCounter = 0;

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay1' */
  IMU_Idcm_DWork.UnitDelay1_DSTATE[0] = IMU_Idcm_P.UnitDelay1_X0[0];
  IMU_Idcm_DWork.UnitDelay1_DSTATE[1] = IMU_Idcm_P.UnitDelay1_X0[1];
  IMU_Idcm_DWork.UnitDelay1_DSTATE[2] = IMU_Idcm_P.UnitDelay1_X0[2];
  IMU_Idcm_DWork.UnitDelay1_DSTATE[3] = IMU_Idcm_P.UnitDelay1_X0[3];

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
  IMU_Idcm_DWork.UnitDelay_DSTATE = IMU_Idcm_P.UnitDelay_X0;
}

/* Model terminate function */
void IMU_Idcm_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
