#ifndef SAMPLING_C
#define SAMPLING_C

#include "Sampling.h"
#include "UART.h"


/* Implementation of a function that returns a sine wave based on FreeRTOS tick timing.
 * Arguments: void
 * Returns: Sine wave value
 * The current tick count is received inside the function body.
 */
float sineRTOS(void)
{
    static volatile long entryCount = 0;
    static volatile float currentTime = 0;
    currentTime = entryCount * SAMPLING_TIME_SEC;
    float outputValue = SINE_AMPLITUDE * sin(SINE_FREQ * currentTime);
    entryCount++;
    UART0_outChar(outputValue * 20);
    return outputValue;
}


#endif
