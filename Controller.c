/*
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu May 14 23:03:13 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"
#include "Controller_private.h"

/* Block states (default storage) */
DW_Controller_T Controller_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Controller_T Controller_Y;

/* Real-time model */
RT_MODEL_Controller_T Controller_M_;
RT_MODEL_Controller_T *const Controller_M = &Controller_M_;

/* Model step function */
void Controller_step(void *pvParameters) /* Function argument edited manually to be compatible with FreeRTOS */
{
  real_T rtb_Subtract;
  real_T rtb_FilterCoefficient;

  /*  Recieving data from based on a sine wave input
   *  Note: We implemented the following piece of code manually.
  */

  for(;;) /* Infinite loop for task to be compatible with FreeRTOS */
  {

  /* Sinusoidal input */
  //Controller_U.Setpoint = sineRTOS();

  /* Step input */
  Controller_U.Setpoint = 1;

  Controller_U.Measurement = UART5_inChar() / FRACTIONING_FACTOR;

  /* End of manual piece of code */
  /* Sum: '<S1>/Subtract' incorporates:
   *  Inport: '<Root>/Measurement'
   *  Inport: '<Root>/Setpoint'
   */
  rtb_Subtract = Controller_U.Setpoint - Controller_U.Measurement;

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S2>/Filter'
   *  Gain: '<S2>/Derivative Gain'
   *  Sum: '<S2>/SumD'
   */
  rtb_FilterCoefficient = (D_GAIN * rtb_Subtract -
    Controller_DW.Filter_DSTATE) * 100.0;

  /* Outport: '<Root>/Control Action' incorporates:
   *  DiscreteIntegrator: '<S2>/Integrator'
   *  Gain: '<S2>/Proportional Gain'
   *  Sum: '<S2>/Sum'
   */
  Controller_Y.ControlAction = (P_GAIN * rtb_Subtract +
    Controller_DW.Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Transmit control action to plant
   * Note: The following piece of code is implemented manually
   */

  UART1_outChar((uint8_t)(Controller_Y.ControlAction * FRACTIONING_FACTOR));
  vTaskDelay(SAMPLING_TIME_TICKS);

  /* End of manual piece of code */

  /* Update for DiscreteIntegrator: '<S2>/Integrator' incorporates:
   *  Gain: '<S2>/Integral Gain'
   */
  Controller_DW.Integrator_DSTATE += I_GAIN * rtb_Subtract * SAMPLING_TIME_SEC;

  /* Update for DiscreteIntegrator: '<S2>/Filter' */
  Controller_DW.Filter_DSTATE += SAMPLING_TIME_SEC * rtb_FilterCoefficient;
  }
}

/* Model initialize function */
void Controller_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Controller_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Controller_DW, 0,
                sizeof(DW_Controller_T));

  /* external inputs */
  (void)memset((void *)&Controller_U, 0, sizeof(ExtU_Controller_T));

  /* external outputs */
  Controller_Y.ControlAction = 0.0;

  /* Manual enabling of UART peripherals. */
  UART0_Init();
  UART1_Init();
  UART5_Init();
}

/* Model terminate function */
void Controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
