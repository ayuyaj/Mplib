/** 
 *******************************************************************************
 * @file    UART_Print.c
 * @brief   the application functions of UART_Print demo for the TOSHIBA
 *          'TMPM369' Device Series 
 * @version V0.100
 * @date    2011/09/14
 * 
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 * 
 * TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 * 
 * (C)Copyright TOSHIBA CORPORATION 2011 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "tmpm369_uart.h"
#include "tmpm369_gpio.h"
#include <stdio.h>
/**
  * @brief  The UART_Print  function
  * @param  None
  * @retval int
  */

void SIO_Configuration(TSB_SC_TypeDef * SCx);
void SIO_ChInit(void);
void delay(void);
void UART0_Print(char *s);

void UART_Print(void)
{

    char TxBuffer[] = "TMPM369\n\r";
    int k = 33333;
    /* Initialize system */
    SIO_Configuration(UART0);
    SIO_ChInit();
    sprintf(TxBuffer,"%d",k);

    while (1) 
			{     
        UART0_Print(TxBuffer);     /* SIO0 send data */
				delay();
			}

       

 
}

/**
  * @brief  Delay some time
  * @param  None
  * @retval None
  */
void delay(void)
{
    uint32_t i = 0U;
    for(i = 0U; i<0xFFFF0U; i++){
      /* Do nothing */
    }
}

void UART0_Print(char *s)
{
	
	while(*s != '\0')
	{
		
		UART_SetTxData(UART0, *s);
		s ++;
		delay();
		

  }

}

/**
  * @brief  SIO Configuration.
  * @param  SCx
  * @retval None
  */
void SIO_Configuration(TSB_SC_TypeDef * SCx)
{
    if (SCx == UART0) {
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_2, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_2, DISABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_2);
    } else {
        /*  Do Nothing */
    }
}

/**
  * @brief  SIO Configuration Initialize the uart port (SIO1).
  * @param  None
  * @retval None
  */
void SIO_ChInit(void)
{
    UART_InitTypeDef myUART;

    /* configure SIO0 for reception */
    UART_Enable(UART0);
    myUART.BaudRate = 115200U;  /* baud rate = 115200 */
    myUART.DataBits = UART_DATA_BITS_8; /* no handshake, 8-bit data, clock by baud rate generator */
    myUART.StopBits = UART_STOP_BITS_1; /* 1-bit stop, LSB,  W-buff enable */
    myUART.Parity = UART_NO_PARITY;
    myUART.Mode = UART_ENABLE_TX;
    myUART.FlowCtrl = UART_NONE_FLOW_CTRL;
    UART_Init(UART0, &myUART);
}
