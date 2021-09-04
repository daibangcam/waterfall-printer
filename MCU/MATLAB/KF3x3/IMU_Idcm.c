/*
 * File: IMU_Idcm.c
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

/* user code (top of source file) */
/* System '<Root>' */
#include "stm32f10x.h"
// #include "driver.h"

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
  real_T mobs[3];
  real_T C[9];
  real_T Qd[9];
  real_T R[9];
  real_T K[9];
  int8_T I[9];
  int32_T p;
  int32_T p_0;
  int32_T p_1;
  real_T absx;
  real_T absx_0;
  real_T absx_1;
  int32_T itmp;
  real_T s_phi;
  real_T c_phi;
  real_T s_theta;
  real_T c_theta;
  real_T s_psi;
  real_T c_psi;
  real_T rtb_Gain[3];
  real_T rtb_Gain1[3];
  real_T rtb_TmpSignalConversionAtSFun_f[9];
  real_T rtb_outxh__p[3];
  real_T rtb_xk[3];
  real_T rtb_outP__h[9];
  real_T tmp[9];
  real_T tmp_0[9];
  real_T mobs_0[3];
  real_T c_theta_0[3];
  static int8_T tmp_1[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  {
    /* user code (Output function Header) */

    /* System '<Root>' */
    uint16_t i;

    /* user code (Output function Body) */

    /* System '<Root>' */
//  read_adis();
//     for (i=0; i<3; i++) {
//       fgyro[i] = marg[i+1];
//       facc[i] = marg[i+4];
//       fmag[i] = marg[i+7];
//     }
      
    for (i=0; i<3; i++) {
      fgyro[i] = 1;
      facc[i] = 1;
      fmag[i] = 1;
    }

    /* SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport7' incorporates:
     *  Inport: '<Root>/Mag  Sensor'
     */

    /* Gain: '<Root>/Gain' incorporates:
     *  Inport: '<Root>/Gyro  Sensor'
     */
    absx = IMU_Idcm_P.Gain_Gain * fgyro[0];

    /* Gain: '<Root>/Gain1' incorporates:
     *  Inport: '<Root>/Acc  Sensor'
     */
    rtb_Gain1[0] = IMU_Idcm_P.Gain1_Gain * facc[0];
    rtb_TmpSignalConversionAtSFun_f[0] = absx;
    rtb_Gain[0] = absx;

    /* Gain: '<Root>/Gain' incorporates:
     *  Inport: '<Root>/Gyro  Sensor'
     */
    absx = IMU_Idcm_P.Gain_Gain * fgyro[1];

    /* Gain: '<Root>/Gain1' incorporates:
     *  Inport: '<Root>/Acc  Sensor'
     */
    rtb_Gain1[1] = IMU_Idcm_P.Gain1_Gain * facc[1];
    rtb_TmpSignalConversionAtSFun_f[1] = absx;
    rtb_Gain[1] = absx;

    /* Gain: '<Root>/Gain' incorporates:
     *  Inport: '<Root>/Gyro  Sensor'
     */
    absx = IMU_Idcm_P.Gain_Gain * fgyro[2];

    /* Gain: '<Root>/Gain1' incorporates:
     *  Inport: '<Root>/Acc  Sensor'
     */
    rtb_Gain1[2] = IMU_Idcm_P.Gain1_Gain * facc[2];
    rtb_TmpSignalConversionAtSFun_f[2] = absx;
    rtb_Gain[2] = absx;
    rtb_TmpSignalConversionAtSFun_f[3] = rtb_Gain1[0];
    rtb_TmpSignalConversionAtSFun_f[4] = rtb_Gain1[1];
    rtb_TmpSignalConversionAtSFun_f[5] = rtb_Gain1[2];
    rtb_TmpSignalConversionAtSFun_f[6] = fmag[0];
    rtb_TmpSignalConversionAtSFun_f[7] = fmag[1];
    rtb_TmpSignalConversionAtSFun_f[8] = fmag[2];

    /* Embedded MATLAB: '<S2>/Kalman Filter 1' incorporates:
     *  Constant: '<S1>/Q1'
     *  Constant: '<S1>/Racc'
     *  Constant: '<S1>/acc_Rbar'
     *  UnitDelay: '<S2>/Unit Delay'
     *  UnitDelay: '<S2>/Unit Delay1'
     */
    /* Embedded MATLAB Function 'DCM Kalman Filter/Kalman Filter 1/Kalman Filter 1': '<S4>:1' */
    /*  EKF  Extended Kalman Filter */
    /*  */
    /*    [xk, Pk, outxh_, outP_] = ekf(inxh_, inP_, Rv, Rn, obs) */
    /*  */
    /*    This filter assumes the following standard state-space model: */
    /*  */
    /*      x(k) = ffun[x(k-1),v(k-1),U1(k-1)] */
    /*      y(k) = hfun[x(k),n(k),U2(k)] */
    /*  */
    /*    where x is the system state, v the process noise, n the observation noise */
    /*    and y the noisy observation of the system. */
    /*  */
    /*    INPUT */
    /*          inxh_                predicted state at time k       */
    /*          inP_                 predicted state covariance at time */
    /*          Sv                   process noise Sv = chol(Q)' */
    /*          Sn                   measurement noise Sn = sqrtm(R)  */
    /*          obs                  noisy observations at time k */
    /*  */
    /*    OUTPUT */
    /*          xk                   estimates of state starting at time k  */
    /*          Pk                   state covariance */
    /*          outxh_               predicted state for time k+1       */
    /*          outP_                predicted state covariance for time k+1 */
    /*  */
    /* ========================================================================== */
    /* '<S4>:1:28' */
    mobs[0] = rtb_TmpSignalConversionAtSFun_f[3] * 0.981;
    mobs[1] = rtb_TmpSignalConversionAtSFun_f[4] * 0.981;
    mobs[2] = rtb_TmpSignalConversionAtSFun_f[5] * 0.981;

    /*  measurement value from accelerometer */
    /* '<S4>:1:29' */
    /*  gyro measurement is considered as input value of the model */
    /* '<S4>:1:31' */
    /*  initialise variables and parameters     */
    /* Qd  = Rv* eye(3); */
    /* '<S4>:1:39' */
    C[0] = 0.0;
    C[3] = -IMU_Idcm_DWork.UnitDelay_DSTATE_h[2];
    C[6] = IMU_Idcm_DWork.UnitDelay_DSTATE_h[1];
    C[1] = IMU_Idcm_DWork.UnitDelay_DSTATE_h[2];
    C[4] = 0.0;
    C[7] = -IMU_Idcm_DWork.UnitDelay_DSTATE_h[0];
    C[2] = -IMU_Idcm_DWork.UnitDelay_DSTATE_h[1];
    C[5] = IMU_Idcm_DWork.UnitDelay_DSTATE_h[0];
    C[8] = 0.0;

    /* '<S4>:1:43' */
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + IMU_Idcm_P.Q1_Value[p] * C[p_0];
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + IMU_Idcm_P.Q1_Value[p + 3] * C[p_0
          + 3];
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + IMU_Idcm_P.Q1_Value[p + 6] * C[p_0
          + 6];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp_0[p + 3 * p_0] = 0.0;
        tmp_0[p + 3 * p_0] = tmp_0[3 * p_0 + p] + C[3 * p_0] * tmp[p];
        tmp_0[p + 3 * p_0] = C[3 * p_0 + 1] * tmp[p + 3] + tmp_0[3 * p_0 + p];
        tmp_0[p + 3 * p_0] = C[3 * p_0 + 2] * tmp[p + 6] + tmp_0[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      Qd[3 * p] = tmp_0[3 * p] * 0.0001;
      Qd[1 + 3 * p] = tmp_0[3 * p + 1] * 0.0001;
      Qd[2 + 3 * p] = tmp_0[3 * p + 2] * 0.0001;
    }

    /* '<S4>:1:44' */
    memcpy((void *)&R[0], (void *)(&IMU_Idcm_P.Racc_Value[0]), 9U * sizeof
           (real_T));

    /* '<S4>:1:47' */
    /* '<S4>:1:49' */
    if (fabs(sqrt((rt_pow_snf(mobs[0], 2.0) + rt_pow_snf(mobs[1], 2.0)) +
                  rt_pow_snf(mobs[2], 2.0)) - 9.81) / 9.81 != 0.0) {
      /* '<S4>:1:51' */
      /* '<S4>:1:52' */
      for (p = 0; p < 9; p++) {
        R[p] = IMU_Idcm_P.Racc_Value[p] / IMU_Idcm_P.acc_Rbar_Value;
        Qd[p] = Qd[p] * IMU_Idcm_P.acc_Rbar_Value;
      }
    }

    /*  compute Kalman gain */
    /* '<S4>:1:64' */
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] +
          IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0] * (real_T)tmp_1[p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0 + 1] *
          (real_T)tmp_1[p + 3] + tmp[3 * p_0 + p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0 + 2] *
          (real_T)tmp_1[p + 6] + tmp[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        C[p + 3 * p_0] = (((real_T)tmp_1[3 * p_0 + 1] * tmp[p + 3] + (real_T)
                           tmp_1[3 * p_0] * tmp[p]) + (real_T)tmp_1[3 * p_0 + 2]
                          * tmp[p + 6]) + R[3 * p_0 + p];
      }
    }

    memcpy((void *)&K[0], (void *)&C[0], 9U * sizeof(real_T));
    p = 0;
    p_0 = 3;
    p_1 = 6;
    absx = fabs(C[0]);
    absx_0 = fabs(C[1]);
    absx_1 = fabs(C[2]);
    if ((absx_0 > absx) && (absx_0 > absx_1)) {
      p = 3;
      p_0 = 0;
      K[0] = C[1];
      K[1] = C[0];
      absx = K[3];
      K[3] = K[4];
      K[4] = absx;
      absx = K[6];
      K[6] = K[7];
      K[7] = absx;
    } else {
      if (absx_1 > absx) {
        p = 6;
        p_1 = 0;
        K[0] = C[2];
        K[2] = C[0];
        absx = K[3];
        K[3] = K[5];
        K[5] = absx;
        absx = K[6];
        K[6] = K[8];
        K[8] = absx;
      }
    }

    K[1] = K[1] / K[0];
    K[2] = K[2] / K[0];
    K[4] = K[4] - K[1] * K[3];
    K[5] = K[5] - K[2] * K[3];
    K[7] = K[7] - K[1] * K[6];
    K[8] = K[8] - K[2] * K[6];
    if (fabs(K[5]) > fabs(K[4])) {
      itmp = p_0;
      p_0 = p_1;
      p_1 = itmp;
      absx = K[1];
      K[1] = K[2];
      K[2] = absx;
      absx = K[4];
      K[4] = K[5];
      K[5] = absx;
      absx = K[7];
      K[7] = K[8];
      K[8] = absx;
    }

    K[5] = K[5] / K[4];
    K[8] = K[8] - K[5] * K[7];
    absx = (K[5] * K[1] - K[2]) / K[8];
    absx_0 = (-(K[7] * absx + K[1])) / K[4];
    C[p] = ((1.0 - K[3] * absx_0) - K[6] * absx) / K[0];
    C[p + 1] = absx_0;
    C[p + 2] = absx;
    absx = (-K[5]) / K[8];
    absx_0 = (1.0 - K[7] * absx) / K[4];
    C[p_0] = (-(K[3] * absx_0 + K[6] * absx)) / K[0];
    C[p_0 + 1] = absx_0;
    C[p_0 + 2] = absx;
    absx = 1.0 / K[8];
    absx_0 = (-K[7]) * absx / K[4];
    C[p_1] = (-(K[3] * absx_0 + K[6] * absx)) / K[0];
    C[p_1 + 1] = absx_0;
    C[p_1 + 2] = absx;
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + (real_T)tmp_1[3 * p_0] *
          IMU_Idcm_DWork.UnitDelay1_DSTATE_p[p];
        tmp[p + 3 * p_0] = (real_T)tmp_1[3 * p_0 + 1] *
          IMU_Idcm_DWork.UnitDelay1_DSTATE_p[p + 3] + tmp[3 * p_0 + p];
        tmp[p + 3 * p_0] = (real_T)tmp_1[3 * p_0 + 2] *
          IMU_Idcm_DWork.UnitDelay1_DSTATE_p[p + 6] + tmp[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        K[p + 3 * p_0] = 0.0;
        K[p + 3 * p_0] = K[3 * p_0 + p] + C[3 * p_0] * tmp[p];
        K[p + 3 * p_0] = C[3 * p_0 + 1] * tmp[p + 3] + K[3 * p_0 + p];
        K[p + 3 * p_0] = C[3 * p_0 + 2] * tmp[p + 6] + K[3 * p_0 + p];
      }
    }

    /*  update estimate with measurement Zk */
    /* '<S4>:1:67' */
    for (p = 0; p < 3; p++) {
      mobs_0[p] = mobs[p] - (((real_T)tmp_1[p + 3] *
        IMU_Idcm_DWork.UnitDelay_DSTATE_h[1] + (real_T)tmp_1[p] *
        IMU_Idcm_DWork.UnitDelay_DSTATE_h[0]) + (real_T)tmp_1[p + 6] *
        IMU_Idcm_DWork.UnitDelay_DSTATE_h[2]);
    }

    for (p = 0; p < 3; p++) {
      rtb_xk[p] = ((K[p + 3] * mobs_0[1] + K[p] * mobs_0[0]) + K[p + 6] *
                   mobs_0[2]) + IMU_Idcm_DWork.UnitDelay_DSTATE_h[p];
    }

    /* '<S4>:1:68' */
    absx = sqrt((rt_pow_snf(rtb_xk[0], 2.0) + rt_pow_snf(rtb_xk[1], 2.0)) +
                rt_pow_snf(rtb_xk[2], 2.0));

    /* '<S4>:1:69' */
    rtb_xk[0] = rtb_xk[0] / absx;
    rtb_xk[1] = rtb_xk[1] / absx;
    rtb_xk[2] = rtb_xk[2] / absx;

    /*  compute error covariance for updated estimate */
    /* '<S4>:1:72' */
    /*  project ahead */
    /* '<S4>:1:76' */
    /* '<S4>:1:79' */
    for (p = 0; p < 9; p++) {
      I[p] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    tmp[0] = 0.0;
    tmp[3] = rtb_TmpSignalConversionAtSFun_f[2];
    tmp[6] = -rtb_TmpSignalConversionAtSFun_f[1];
    tmp[1] = -rtb_TmpSignalConversionAtSFun_f[2];
    tmp[4] = 0.0;
    tmp[7] = rtb_TmpSignalConversionAtSFun_f[0];
    tmp[2] = rtb_TmpSignalConversionAtSFun_f[1];
    tmp[5] = -rtb_TmpSignalConversionAtSFun_f[0];
    tmp[8] = 0.0;
    for (p = 0; p < 3; p++) {
      C[3 * p] = tmp[3 * p] * 0.01 + (real_T)I[3 * p];
      C[1 + 3 * p] = tmp[3 * p + 1] * 0.01 + (real_T)I[3 * p + 1];
      C[2 + 3 * p] = tmp[3 * p + 2] * 0.01 + (real_T)I[3 * p + 2];
    }

    /* '<S4>:1:80' */
    /* '<S4>:1:81' */
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] +
          IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0] * (real_T)tmp_1[p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0 + 1] *
          (real_T)tmp_1[p + 3] + tmp[3 * p_0 + p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0 + 2] *
          (real_T)tmp_1[p + 6] + tmp[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp_0[p + 3 * p_0] = (((real_T)tmp_1[3 * p_0 + 1] * tmp[p + 3] + (real_T)
          tmp_1[3 * p_0] * tmp[p]) + (real_T)tmp_1[3 * p_0 + 2] * tmp[p + 6]) +
          R[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        R[p + 3 * p_0] = 0.0;
        R[p + 3 * p_0] = R[3 * p_0 + p] + tmp_0[3 * p_0] * K[p];
        R[p + 3 * p_0] = tmp_0[3 * p_0 + 1] * K[p + 3] + R[3 * p_0 + p];
        R[p + 3 * p_0] = tmp_0[3 * p_0 + 2] * K[p + 6] + R[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE_p[3 * p_0 + p] -
          ((R[p + 3] * K[p_0 + 3] + R[p] * K[p_0]) + R[p + 6] * K[p_0 + 6]);
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        R[p + 3 * p_0] = 0.0;
        R[p + 3 * p_0] = R[3 * p_0 + p] + tmp[3 * p_0] * C[p];
        R[p + 3 * p_0] = tmp[3 * p_0 + 1] * C[p + 3] + R[3 * p_0 + p];
        R[p + 3 * p_0] = tmp[3 * p_0 + 2] * C[p + 6] + R[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        rtb_outP__h[p + 3 * p_0] = ((R[p + 3] * C[p_0 + 3] + R[p] * C[p_0]) +
          R[p + 6] * C[p_0 + 6]) + Qd[3 * p_0 + p];
      }
    }

    /* SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport8' */
    for (p = 0; p < 3; p++) {
      rtb_TmpSignalConversionAtSFun_f[p] = rtb_Gain[p];
      rtb_outxh__p[p] = C[p + 6] * rtb_xk[2] + (C[p + 3] * rtb_xk[1] + C[p] *
        rtb_xk[0]);
    }

    rtb_TmpSignalConversionAtSFun_f[3] = rtb_Gain1[0];
    rtb_TmpSignalConversionAtSFun_f[4] = rtb_Gain1[1];
    rtb_TmpSignalConversionAtSFun_f[5] = rtb_Gain1[2];

    /* Embedded MATLAB: '<S3>/Kalman Filter 2' incorporates:
     *  Constant: '<S1>/Q2'
     *  Constant: '<S1>/Rmag'
     *  Constant: '<S1>/mag_Rbar'
     *  Constant: '<S1>/mag_sigma'
     *  Inport: '<Root>/Mag  Sensor'
     *  UnitDelay: '<S3>/Unit Delay'
     *  UnitDelay: '<S3>/Unit Delay1'
     */
    /* Embedded MATLAB Function 'DCM Kalman Filter/Kalman Filter 2/Kalman Filter 2': '<S5>:1' */
    /*  EKF  Extended Kalman Filter */
    /*  */
    /*    [xk, Pk, outxh_, outP_] = ekf(inxh_, inP_, Rv, Rn, obs) */
    /*  */
    /*    This filter assumes the following standard state-space model: */
    /*  */
    /*      x(k) = ffun[x(k-1),v(k-1),U1(k-1)] */
    /*      y(k) = hfun[x(k),n(k),U2(k)] */
    /*  */
    /*    where x is the system state, v the process noise, n the observation noise */
    /*    and y the noisy observation of the system. */
    /*  */
    /*    INPUT */
    /*          inxh_                predicted state at time k       */
    /*          inP_                 predicted state covariance at time */
    /*          Sv                   process noise Sv = chol(Q)' */
    /*          Sn                   measurement noise Sn = sqrtm(R)  */
    /*          obs                  noisy observations at time k */
    /*  */
    /*    OUTPUT */
    /*          xk                   estimates of state starting at time k  */
    /*          Pk                   state covariance */
    /*          outxh_               predicted state for time k+1       */
    /*          outP_                predicted state covariance for time k+1 */
    /*  */
    /* ========================================================================== */
    /* '<S5>:1:28' */
    /*  measurement value from accelerometer and magnetic sensor */
    /* '<S5>:1:29' */
    /*  gyro measurement is considered as input value of the model */
    /* '<S5>:1:31' */
    rtb_TmpSignalConversionAtSFun_f[6] = fmag[0];
    rtb_Gain[0] = 0.0;
    rtb_TmpSignalConversionAtSFun_f[7] = fmag[1];
    rtb_Gain[1] = 0.0;
    rtb_TmpSignalConversionAtSFun_f[8] = fmag[2];
    rtb_Gain[2] = 0.0;

    /* '<S5>:1:32' */
    /* Qd  = Rv* eye(3); */
    /* '<S5>:1:36' */
    /* '<S5>:1:37' */
    for (p = 0; p < 9; p++) {
      Qd[p] = IMU_Idcm_P.Q2_Value[p];
      R[p] = IMU_Idcm_P.Rmag_Value[p];
    }

    /* '<S5>:1:40' */
    if (fabs(sqrt((rt_pow_snf(rtb_TmpSignalConversionAtSFun_f[6], 2.0) +
                   rt_pow_snf(rtb_TmpSignalConversionAtSFun_f[7], 2.0)) +
                  rt_pow_snf(rtb_TmpSignalConversionAtSFun_f[8], 2.0)) - 700.0) >
        IMU_Idcm_P.mag_sigma_Value) {
      /* '<S5>:1:42' */
      /* '<S5>:1:43' */
      /* '<S5>:1:44' */
      for (p = 0; p < 9; p++) {
        Qd[p] = IMU_Idcm_P.Q2_Value[p] * IMU_Idcm_P.mag_Rbar_Value;
        R[p] = IMU_Idcm_P.Rmag_Value[p] / IMU_Idcm_P.mag_Rbar_Value;
      }
    }

    /* measurement */
    /* '<S5>:1:49' */
    absx = rt_atan2d_snf(rtb_xk[1], rtb_xk[2]);

    /* '<S5>:1:50' */
    s_phi = sin(absx);

    /* '<S5>:1:51' */
    c_phi = cos(absx);

    /* '<S5>:1:53' */
    s_theta = -rtb_xk[0];

    /*  sin(theta) */
    /* '<S5>:1:54' */
    c_theta = sqrt(1.0 - rt_pow_snf(s_theta, 2.0));

    /*  cos(theta) */
    /* '<S5>:1:56' */
    absx = (rtb_TmpSignalConversionAtSFun_f[7] * s_theta * s_phi +
            rtb_TmpSignalConversionAtSFun_f[6] * c_theta) +
      rtb_TmpSignalConversionAtSFun_f[8] * s_theta * c_phi;

    /* '<S5>:1:57' */
    absx_0 = rtb_TmpSignalConversionAtSFun_f[7] * c_phi -
      rtb_TmpSignalConversionAtSFun_f[8] * s_phi;

    /* '<S5>:1:58' */
    s_psi = (-absx_0) / sqrt(rt_pow_snf(absx, 2.0) + rt_pow_snf(absx_0, 2.0));

    /* '<S5>:1:59' */
    c_psi = absx / sqrt(rt_pow_snf(absx, 2.0) + rt_pow_snf(absx_0, 2.0));

    /* '<S5>:1:61' */
    /* '<S5>:1:62' */
    /* '<S5>:1:63' */
    /* '<S5>:1:64' */
    /*  initialise variables and parameters     */
    /*  compute Kalman gain */
    /* '<S5>:1:75' */
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + IMU_Idcm_DWork.UnitDelay1_DSTATE[3
          * p_0] * (real_T)tmp_1[p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE[3 * p_0 + 1] *
          (real_T)tmp_1[p + 3] + tmp[3 * p_0 + p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE[3 * p_0 + 2] *
          (real_T)tmp_1[p + 6] + tmp[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        C[p + 3 * p_0] = (((real_T)tmp_1[3 * p_0 + 1] * tmp[p + 3] + (real_T)
                           tmp_1[3 * p_0] * tmp[p]) + (real_T)tmp_1[3 * p_0 + 2]
                          * tmp[p + 6]) + R[3 * p_0 + p];
      }
    }

    memcpy((void *)&K[0], (void *)&C[0], 9U * sizeof(real_T));
    p = 0;
    p_0 = 3;
    p_1 = 6;
    absx = fabs(C[0]);
    absx_0 = fabs(C[1]);
    absx_1 = fabs(C[2]);
    if ((absx_0 > absx) && (absx_0 > absx_1)) {
      p = 3;
      p_0 = 0;
      K[0] = C[1];
      K[1] = C[0];
      absx = K[3];
      K[3] = K[4];
      K[4] = absx;
      absx = K[6];
      K[6] = K[7];
      K[7] = absx;
    } else {
      if (absx_1 > absx) {
        p = 6;
        p_1 = 0;
        K[0] = C[2];
        K[2] = C[0];
        absx = K[3];
        K[3] = K[5];
        K[5] = absx;
        absx = K[6];
        K[6] = K[8];
        K[8] = absx;
      }
    }

    K[1] = K[1] / K[0];
    K[2] = K[2] / K[0];
    K[4] = K[4] - K[1] * K[3];
    K[5] = K[5] - K[2] * K[3];
    K[7] = K[7] - K[1] * K[6];
    K[8] = K[8] - K[2] * K[6];
    if (fabs(K[5]) > fabs(K[4])) {
      itmp = p_0;
      p_0 = p_1;
      p_1 = itmp;
      absx = K[1];
      K[1] = K[2];
      K[2] = absx;
      absx = K[4];
      K[4] = K[5];
      K[5] = absx;
      absx = K[7];
      K[7] = K[8];
      K[8] = absx;
    }

    K[5] = K[5] / K[4];
    K[8] = K[8] - K[5] * K[7];
    absx = (K[5] * K[1] - K[2]) / K[8];
    absx_0 = (-(K[7] * absx + K[1])) / K[4];
    C[p] = ((1.0 - K[3] * absx_0) - K[6] * absx) / K[0];
    C[p + 1] = absx_0;
    C[p + 2] = absx;
    absx = (-K[5]) / K[8];
    absx_0 = (1.0 - K[7] * absx) / K[4];
    C[p_0] = (-(K[3] * absx_0 + K[6] * absx)) / K[0];
    C[p_0 + 1] = absx_0;
    C[p_0 + 2] = absx;
    absx = 1.0 / K[8];
    absx_0 = (-K[7]) * absx / K[4];
    C[p_1] = (-(K[3] * absx_0 + K[6] * absx)) / K[0];
    C[p_1 + 1] = absx_0;
    C[p_1 + 2] = absx;
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + (real_T)tmp_1[3 * p_0] *
          IMU_Idcm_DWork.UnitDelay1_DSTATE[p];
        tmp[p + 3 * p_0] = (real_T)tmp_1[3 * p_0 + 1] *
          IMU_Idcm_DWork.UnitDelay1_DSTATE[p + 3] + tmp[3 * p_0 + p];
        tmp[p + 3 * p_0] = (real_T)tmp_1[3 * p_0 + 2] *
          IMU_Idcm_DWork.UnitDelay1_DSTATE[p + 6] + tmp[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        K[p + 3 * p_0] = 0.0;
        K[p + 3 * p_0] = K[3 * p_0 + p] + C[3 * p_0] * tmp[p];
        K[p + 3 * p_0] = C[3 * p_0 + 1] * tmp[p + 3] + K[3 * p_0 + p];
        K[p + 3 * p_0] = C[3 * p_0 + 2] * tmp[p + 6] + K[3 * p_0 + p];
      }
    }

    /*  update estimate with measurement Zk */
    /* '<S5>:1:77' */
    mobs_0[0] = c_theta * s_psi;
    mobs_0[1] = s_phi * s_theta * s_psi + c_phi * c_psi;
    mobs_0[2] = c_phi * s_theta * s_psi - s_phi * c_psi;
    for (p = 0; p < 3; p++) {
      c_theta_0[p] = mobs_0[p] - (((real_T)tmp_1[p + 3] *
        IMU_Idcm_DWork.UnitDelay_DSTATE[1] + (real_T)tmp_1[p] *
        IMU_Idcm_DWork.UnitDelay_DSTATE[0]) + (real_T)tmp_1[p + 6] *
        IMU_Idcm_DWork.UnitDelay_DSTATE[2]);
    }

    for (p = 0; p < 3; p++) {
      rtb_Gain1[p] = ((K[p + 3] * c_theta_0[1] + K[p] * c_theta_0[0]) + K[p + 6]
                      * c_theta_0[2]) + IMU_Idcm_DWork.UnitDelay_DSTATE[p];
    }

    /* '<S5>:1:78' */
    absx = sqrt((rt_pow_snf(rtb_Gain1[0], 2.0) + rt_pow_snf(rtb_Gain1[1], 2.0))
                + rt_pow_snf(rtb_Gain1[2], 2.0));

    /* '<S5>:1:79' */
    rtb_Gain1[0] = rtb_Gain1[0] / absx;
    rtb_Gain1[1] = rtb_Gain1[1] / absx;
    rtb_Gain1[2] = rtb_Gain1[2] / absx;

    /*  compute error covariance for updated estimate */
    /* '<S5>:1:82' */
    /*  project ahead */
    /* '<S5>:1:85' */
    /* '<S5>:1:88' */
    for (p = 0; p < 9; p++) {
      I[p] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    tmp[0] = 0.0;
    tmp[3] = rtb_TmpSignalConversionAtSFun_f[2];
    tmp[6] = -rtb_TmpSignalConversionAtSFun_f[1];
    tmp[1] = -rtb_TmpSignalConversionAtSFun_f[2];
    tmp[4] = 0.0;
    tmp[7] = rtb_TmpSignalConversionAtSFun_f[0];
    tmp[2] = rtb_TmpSignalConversionAtSFun_f[1];
    tmp[5] = -rtb_TmpSignalConversionAtSFun_f[0];
    tmp[8] = 0.0;
    for (p = 0; p < 3; p++) {
      C[3 * p] = tmp[3 * p] * 0.01 + (real_T)I[3 * p];
      C[1 + 3 * p] = tmp[3 * p + 1] * 0.01 + (real_T)I[3 * p + 1];
      C[2 + 3 * p] = tmp[3 * p + 2] * 0.01 + (real_T)I[3 * p + 2];
    }

    /* '<S5>:1:89' */
    /* '<S5>:1:90' */
    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = 0.0;
        tmp[p + 3 * p_0] = tmp[3 * p_0 + p] + IMU_Idcm_DWork.UnitDelay1_DSTATE[3
          * p_0] * (real_T)tmp_1[p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE[3 * p_0 + 1] *
          (real_T)tmp_1[p + 3] + tmp[3 * p_0 + p];
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE[3 * p_0 + 2] *
          (real_T)tmp_1[p + 6] + tmp[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp_0[p + 3 * p_0] = (((real_T)tmp_1[3 * p_0 + 1] * tmp[p + 3] + (real_T)
          tmp_1[3 * p_0] * tmp[p]) + (real_T)tmp_1[3 * p_0 + 2] * tmp[p + 6]) +
          R[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        R[p + 3 * p_0] = 0.0;
        R[p + 3 * p_0] = R[3 * p_0 + p] + tmp_0[3 * p_0] * K[p];
        R[p + 3 * p_0] = tmp_0[3 * p_0 + 1] * K[p + 3] + R[3 * p_0 + p];
        R[p + 3 * p_0] = tmp_0[3 * p_0 + 2] * K[p + 6] + R[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        tmp[p + 3 * p_0] = IMU_Idcm_DWork.UnitDelay1_DSTATE[3 * p_0 + p] - ((R[p
          + 3] * K[p_0 + 3] + R[p] * K[p_0]) + R[p + 6] * K[p_0 + 6]);
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        R[p + 3 * p_0] = 0.0;
        R[p + 3 * p_0] = R[3 * p_0 + p] + tmp[3 * p_0] * C[p];
        R[p + 3 * p_0] = tmp[3 * p_0 + 1] * C[p + 3] + R[3 * p_0 + p];
        R[p + 3 * p_0] = tmp[3 * p_0 + 2] * C[p + 6] + R[3 * p_0 + p];
      }
    }

    for (p = 0; p < 3; p++) {
      for (p_0 = 0; p_0 < 3; p_0++) {
        rtb_TmpSignalConversionAtSFun_f[p + 3 * p_0] = ((R[p + 3] * C[p_0 + 3] +
          R[p] * C[p_0]) + R[p + 6] * C[p_0 + 6]) + Qd[3 * p_0 + p];
      }
    }

    /* '<S5>:1:92' */
    absx = rtb_Gain1[1] * rtb_xk[2] - rtb_Gain1[2] * rtb_xk[1];

    /* '<S5>:1:93' */
    /* '<S5>:1:94' */
    /* '<S5>:1:96' */
    absx /= sqrt((rt_pow_snf(rtb_Gain1[2] * rtb_xk[0] - rtb_Gain1[0] * rtb_xk[2],
      2.0) + rt_pow_snf(absx, 2.0)) + rt_pow_snf(rtb_Gain1[0] * rtb_xk[1] -
      rtb_Gain1[1] * rtb_xk[0], 2.0));

    /* '<S5>:1:98' */
    rtb_Gain[0] = rt_atan2d_snf(rtb_xk[1], rtb_xk[2]);

    /*  phi */
    /* '<S5>:1:99' */
    rtb_Gain[1] = asin(-rtb_xk[0]);

    /*  theta */
    /* '<S5>:1:100' */
    rtb_Gain[2] = rt_atan2d_snf(rtb_Gain1[0], absx);
    for (p = 0; p < 3; p++) {
      /* Gain: '<Root>/Gain2' */
      Out1[p] = IMU_Idcm_P.Gain2_Gain * rtb_Gain[p];
      mobs[p] = C[p + 6] * rtb_Gain1[2] + (C[p + 3] * rtb_Gain1[1] + C[p] *
        rtb_Gain1[0]);
    }

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

//     /* System '<Root>' */
//     for (i=0; i<3; i++)
//       euler[i] = Out1[i];
//     if (Out2 != 0.0)
//       GPIO_SetBits(GPIOB, GPIO_Pin_1);
//     else
//       GPIO_ResetBits(GPIOB, GPIO_Pin_1);
  }

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  IMU_Idcm_DWork.UnitDelay_DSTATE[0] = mobs[0];
  IMU_Idcm_DWork.UnitDelay_DSTATE[1] = mobs[1];
  IMU_Idcm_DWork.UnitDelay_DSTATE[2] = mobs[2];

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  IMU_Idcm_DWork.UnitDelay_DSTATE_h[0] = rtb_outxh__p[0];
  IMU_Idcm_DWork.UnitDelay_DSTATE_h[1] = rtb_outxh__p[1];
  IMU_Idcm_DWork.UnitDelay_DSTATE_h[2] = rtb_outxh__p[2];
  for (p = 0; p < 9; p++) {
    /* Update for UnitDelay: '<S3>/Unit Delay1' */
    IMU_Idcm_DWork.UnitDelay1_DSTATE[p] = rtb_TmpSignalConversionAtSFun_f[p];

    /* Update for UnitDelay: '<S2>/Unit Delay1' */
    IMU_Idcm_DWork.UnitDelay1_DSTATE_p[p] = rtb_outP__h[p];
  }
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

  {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
    IMU_Idcm_DWork.UnitDelay_DSTATE[0] = IMU_Idcm_P.UnitDelay_X0[0];
    IMU_Idcm_DWork.UnitDelay_DSTATE[1] = IMU_Idcm_P.UnitDelay_X0[1];
    IMU_Idcm_DWork.UnitDelay_DSTATE[2] = IMU_Idcm_P.UnitDelay_X0[2];

    /* InitializeConditions for UnitDelay: '<S2>/Unit Delay' */
    IMU_Idcm_DWork.UnitDelay_DSTATE_h[0] = IMU_Idcm_P.UnitDelay_X0_i[0];
    IMU_Idcm_DWork.UnitDelay_DSTATE_h[1] = IMU_Idcm_P.UnitDelay_X0_i[1];
    IMU_Idcm_DWork.UnitDelay_DSTATE_h[2] = IMU_Idcm_P.UnitDelay_X0_i[2];
    for (i = 0; i < 9; i++) {
      /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
      IMU_Idcm_DWork.UnitDelay1_DSTATE[i] = IMU_Idcm_P.UnitDelay1_X0[i];

      /* InitializeConditions for UnitDelay: '<S2>/Unit Delay1' */
      IMU_Idcm_DWork.UnitDelay1_DSTATE_p[i] = IMU_Idcm_P.UnitDelay1_X0_n[i];
    }
  }
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
