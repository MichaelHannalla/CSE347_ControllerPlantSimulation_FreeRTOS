/**
 *
 * CSE347 - Embedded Systems Design
 * Faculty of Engineering - Ain Shams University
 * Final Project - Using MATLAB Embedded Coder - Controller Tiva
 *
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Controller.h"

int main(void)
{
    Controller_initialize();

    /* Creation of controller task. */
    xTaskCreate(Controller_step,
                (const portCHAR *)"Controller Task",
                configMINIMAL_STACK_SIZE,
                NULL, 1, NULL);

    vTaskStartScheduler();

    for(;;); /* Program should never reach this line. */

    Controller_terminate();

	return 0;
}
