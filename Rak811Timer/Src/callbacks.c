/*
 * callbacks.c
 *
 *  Created on: Aug 27, 2018
 *      Author: uli
 */
#include "stm32l1xx_hal.h"
extern TIM_HandleTypeDef htim4;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance==TIM3) //check if the interrupt comes from TIM3
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin); //this will toggle the LED
		 //this will switch the LED2 on
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		/* start timer 4 and ask it to create interrupts */
		HAL_TIM_Base_Start_IT(&htim4);
	}
	if (htim->Instance==TIM4) //check if the interrupt comes from TIM4
	{
		/* Switches LED2 off again */
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	}
}
