#ifndef UART_H
#define UART_H


#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"
#include "string.h"


#define IBR 104
#define FBR 11
#define UART1_IRQ (1U<<6)
#define COMMA_ASCII 44

xQueueHandle xDataQueue;

void UART0_Init(void);
uint8_t UART0_inChar(void);
void UART0_outChar(uint8_t);

void UART1_Init(void);
uint8_t UART1_inChar(void);
void UART1_outChar(uint8_t);

void UART5_Init(void);
uint8_t UART5_inChar(void);
void UART5_outChar(uint8_t);

void prinText(char*);

//void UART1_Handler(void);
void vSendToPC(void *pvParameters);



#endif
