#ifndef UART_C
#define UART_C

#include "UART.h"

void UART0_Init(void)
{
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R0) == SYSCTL_RCGCGPIO_R0));
	
	GPIO_PORTA_DEN_R |= 0x03;                          //Make PA0 and PA1 as digital
	GPIO_PORTA_AFSEL_R |=0X03;                         //Use pin A0 and A1 as RxD and TxD
	GPIO_PORTA_PCTL_R |=0x11;                          //which alternative function
	
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;           //Enable UART clock
	while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R0) == SYSCTL_RCGCUART_R0));
	
	UART0_CTL_R &= ~(1U);                              //Disable UART
	UART0_IBRD_R = IBR;                                //integer portion of the Baud rate
	UART0_FBRD_R = FBR;                                //fractional portion of the Baud rate
	UART0_CC_R &= ~(1U);                               //system clock as UART clock
	UART0_LCRH_R |= 0x60;                              //Length of the word 8 bits
	UART0_CTL_R |= 0x300;                              //Set TxE and RxE bits
	UART0_CTL_R |= (1U);                               //Enable UART
 
}

uint8_t UART0_inChar(void)
{
  char recievedChar;
  while((UART0_FR_R & 0x10) != 0);          // Wait until the Rx buffer isn't empty
  recievedChar = UART0_DR_R;                // Read the UART data register
  return recievedChar;
}

void UART0_outChar(uint8_t transmittedChar)
{
  while((UART0_FR_R & 0x20) != 0);          // Wait until Tx buffer not full
  UART0_DR_R = transmittedChar;
}

void printText(char* textToPrint)
{
  int i = 0;
  for (i= 0 ; i< strlen(textToPrint) ; i++)
  {
    UART0_outChar(textToPrint[i]);
  }
}

void vSendToPC(void *pvParameters)
{
    static uint8_t dataToPC;
    for(;;)
    {
        xQueueReceive(xDataQueue, &dataToPC, portMAX_DELAY);
        while((UART0_FR_R & 0x20) != 0);          // Wait until Tx buffer not full
        UART0_DR_R = dataToPC;
        UART0_DR_R = COMMA_ASCII;
    }

}

void UART1_Init(void)
{
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;           //Enable UART clock
    while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R1) == SYSCTL_RCGCUART_R1));

    UART1_CTL_R &= ~(1U);                              //Disable UART

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R1) == SYSCTL_RCGCGPIO_R1));
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTB_CR_R|= 0xFF;
	GPIO_PORTB_DEN_R |= 0x03;                          //Make PB0 and PB1 as digital
	GPIO_PORTB_AFSEL_R |=0X03;                         //Use pin B0 and B1 as RxD and TxD
	GPIO_PORTB_PCTL_R |=0x11;                          //which alternative function
	NVIC_EN0_R |= UART1_IRQ;
	
	UART1_IBRD_R = IBR;                                //integer portion of the Baud rate
	UART1_FBRD_R = FBR;                                //fractional portion of the Baud rate
	UART1_CC_R = 0x0;                                  //system clock as UART clock
	UART1_LCRH_R |= 0x60;                              //Length of the word 8 bits
	//UART1_ICR_R |= 0x010;                            //clear RX interrupt flag
	//UART1_IM_R |= 0x10;                              //enable RX interrupt
	UART1_CTL_R |= (0x300);                            //Set TxE and RxE bits
	UART1_CTL_R |= (1U);                               //Enable UART

}

uint8_t UART1_inChar(void)
{
  char recievedChar;
  while((UART1_FR_R & 0x10) != 0);          // Wait until the Rx buffer isn't empty
  recievedChar = UART1_DR_R;                // Read the UART data register
  return recievedChar;
}

void UART1_outChar(uint8_t transmittedChar)
{
  while((UART1_FR_R & 0x20) != 0);          // Wait until Tx buffer not full
  UART1_DR_R = transmittedChar;
}

/*
void UART1_Handler(void)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    while((UART1_FR_R & 0x10) != 0);                   // Wait until the Rx buffer isn't empty
    uint8_t ulReceivedData = UART1_DR_R + 1;
    xQueueSendToBackFromISR( xDataQueue, &ulReceivedData, &xHigherPriorityTaskWoken );
    UART1_ICR_R |= 0x010;
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
*/


void UART5_Init(void)
{
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;

  // Wait for stabilization
  while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R5) == SYSCTL_RCGCUART_R5));

  // INITIALIZING PORTE WITH NEEDED FUNCTIONALITIES

  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // Inializing PORTA with Clock Gating Control

  // Wait for stabilization
  while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R4) == SYSCTL_RCGCGPIO_R4));

  GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;         // Unlocking CR Register with Magic Code
  GPIO_PORTE_CR_R = 0x0000000FFU;            // If Not Already Unlocked

  //Initializing For UART
  GPIO_PORTE_DEN_R |= 0x30U;                 // Digital Enabling
  GPIO_PORTE_AFSEL_R |= 0x30U;               // GPIO Alternative Function Select
  GPIO_PORTE_PCTL_R  |= (GPIO_PCTL_PE4_U5RX|GPIO_PCTL_PE5_U5TX);           // Configuring pins E4 and E5 for UART                     // Call Func

  UART5_CTL_R &= ~(0x1U);                  // Clearing UART5EN Bit to Disable UART5

  UART5_IBRD_R = 104;                      // For 9600 Baud Rate
  UART5_FBRD_R = 11;                       // For 9600 Baud Rate
  UART5_LCRH_R = 0x60U;
  UART5_CC_R = UART_CC_CS_SYSCLK;          // Clock Source is System Clock

  UART5_CTL_R |= 0x301U;                   // Setting UART5EN Bit to Enable UART5
}

uint8_t UART5_inChar(void)
{
  char recievedChar;
  while((UART5_FR_R & 0x10) != 0);          // Wait until the Rx buffer isn't empty
  recievedChar = UART5_DR_R;                // Read the UART data register
  return recievedChar;
}

void UART5_outChar(uint8_t transmittedChar)
{
  while((UART5_FR_R & 0x20) != 0);          // Wait until Tx buffer not full
  UART5_DR_R = transmittedChar;
}

#endif
