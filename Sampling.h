#ifndef SAMPLING_H
#define SAMPLING_H

#define SAMPLING_TIME_MS  10                                           /* 10 milliseconds */
#define SAMPLING_TIME_SEC 0.01                                          /* 0.01 seconds */
#define SAMPLING_TIME_TICKS (uint8_t)(((float)SAMPLING_TIME_MS / 1000) * configTICK_RATE_HZ)

#define P_GAIN 0.017889256245685
#define I_GAIN 0.17889256245685
#define D_GAIN 0

#define SINE_FREQ       1
#define SINE_AMPLITUDE  1
#define FRACTIONING_FACTOR 1 /* This variable to avoid the limitation of
                                 transmission of floating point numbers in UART */

#include "math.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

extern float sineRTOS(void);


#endif
