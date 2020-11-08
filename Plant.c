/*
 * File: Plant.c
 *
 * Code generated for Simulink model 'Plant'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sun May 17 22:30:38 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Plant.h"
#include "Plant_private.h"

/* Block states (default storage) */
DW_Plant_T Plant_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Plant_T Plant_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Plant_T Plant_Y;

/* Real-time model */
RT_MODEL_Plant_T Plant_M_;
RT_MODEL_Plant_T *const Plant_M = &Plant_M_;

/* Model step function */
void Plant_step(void *pvParameters) /* Change of function arguments to be compatible with FreeRTOS */
{
   for(;;)
   {
       /* Infinite loop to make this thread a FreeRTOS Task */
       /* Outport: '<Root>/SystemOutput' incorporates:
        * DiscreteTransferFcn: '<S1>/Discrete Transfer Fcn'
        */

       Plant_Y.SystemOutput = Plant_DW.DiscreteTransferFcn_states;

       /* Sending the current system output to PC for logging.
        * We implemented the following piece of code manually.
        */

       UART0_outChar((uint8_t)(Plant_Y.SystemOutput * FRACTIONING_FACTOR));
       UART5_outChar((uint8_t)(Plant_Y.SystemOutput * FRACTIONING_FACTOR));
       vTaskDelay(SAMPLING_TIME_TICKS);

       /* Update for DiscreteTransferFcn: '<S1>/Discrete Transfer Fcn' incorporates:
        *  Inport: '<Root>/ControlAction'
        */
       Plant_DW.DiscreteTransferFcn_states = Plant_U.ControlAction - 0.5 * Plant_DW.DiscreteTransferFcn_states;

       /* Recieving the current control action from the controller Tiva. */
       Plant_U.ControlAction = UART1_inChar() / FRACTIONING_FACTOR;
    }
}

/* Model initialize function */
void Plant_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Plant_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Plant_DW, 0,
                sizeof(DW_Plant_T));

  /* external inputs */
  Plant_U.ControlAction = 0.0;

  /* external outputs */
  Plant_Y.SystemOutput = 0.0;

  UART0_Init();
  UART1_Init();
  UART5_Init();
}

/* Model terminate function */
void Plant_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
