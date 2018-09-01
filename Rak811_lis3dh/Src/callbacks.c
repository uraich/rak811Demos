/*
 * callbacks.c
 *
 *  Created on: Aug 18, 2018
 *      Author: uli
 */
#include "stm32l1xx_hal.h"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  printf("EXTI15_10_IRQHandler: Switch transition seen on pin 0x%04x\r\n",GPIO_Pin);
//  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); //this will toggle the LED
}

