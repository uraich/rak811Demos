/*
 * callbacks.c
 *
 *  Created on: Aug 26, 2018
 *      Author: uli
 */

#include "stm32l1xx_hal.h"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == gpsTimingPulse_Pin)
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
