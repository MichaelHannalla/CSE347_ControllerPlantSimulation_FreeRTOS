/**
 *
 * CSE347 - Embedded Systems Design
 * Faculty of Engineering - Ain Shams University
 * Final Project - Using MATLAB Embedded Coder - Plant Tiva C
 *
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Plant.h"

int main(void)
{
    Plant_initialize();

    /* Creation of controller task. */
    xTaskCreate(Plant_step,
                (const portCHAR *)"Plant Task",
                configMINIMAL_STACK_SIZE,
                NULL, 1, NULL);

    vTaskStartScheduler();

    for(;;); /* Program should never reach this line. */

    Plant_terminate();


	return 0;
}
