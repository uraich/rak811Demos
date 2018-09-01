
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void stop(){
	while (1)
		HAL_Delay(10000);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	RTC_DateTypeDef currentDate;
	RTC_TimeTypeDef currentTime;

	char inBuf[20],*inBufPtr;
	size_t i,noOfChars;
	char *endPtr;

	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

	char *weekDay[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
	char weekDayBuf[4];
	bool found;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("Real Time Clock Demo\r\n");
  printf("Asks the user for the current time in the format: hh:mm:ss\r\n");
  printf("Prints the time every 5 s\r\n");

  /* read current date */

  printf("Please enter date in the format: weekday(e.g.) TUE yy-mm-dd: ");

  inBufPtr = inBuf;

  for (noOfChars=0; noOfChars<18; noOfChars++) {
	  *inBufPtr = (char) getchar();
	  putchar(*inBufPtr);        /* echo the character */
	  if (*inBufPtr == '\r')
		  break;
	  inBufPtr++;
  }
  *inBufPtr++ = '\n';
  *inBufPtr = '\0';
  printf("\r\n");
  printf("No of chars read: %d\r\n",noOfChars);
  printf("Date read: %s\r\n",inBuf);

  /* get the weekday and compare to the list */

  inBufPtr = inBuf;
  printf("weekday: ");
  for (int i=0; i<3;i++) {
	  weekDayBuf[i] = *inBufPtr & 0x5f;    // convert to upper case
	  printf("%c",*inBufPtr);
	  inBufPtr++;
  }
  printf("\r\n");
/* get the weekday */
  weekDayBuf[3] = '\0';
  found = false;
  for (i=0; i<7; i++)
	  if (!strcmp(weekDayBuf,weekDay[i]))
		  found = true;
  if (found)
	  printf("The day is %d\r\n",i);
  else
	  printf("The weekday %s is not known\r\n",weekDayBuf);
  if (*inBufPtr++ != ' ')
	  printf("Invalid date format\r\n");
/* get the year */
  currentDate.Year = (uint8_t) strtol(inBufPtr,&endPtr,10);
  if ((currentDate.Year == 0) && (endPtr == inBufPtr)) {
	  printf("Could not convert the year from ascii to int\r\n");
	  stop();
  }
  else
	  printf("year: %d\r\n",currentDate.Year);
  inBufPtr = endPtr;
  if (*inBufPtr++ != '-') {
	  printf("Invalid date format\r\n");
	  stop();
  }
/* get the month */
  currentDate.Month = (uint8_t) strtol(inBufPtr,&endPtr,10);
  if ((currentDate.Month == 0) && (endPtr == inBufPtr)) {
	  printf("Could not convert the month from ascii to int\r\n");
	  stop();
  }
  else
	  printf("month: %d\r\n",currentDate.Month);
  if ((currentDate.Month == 0) || (currentDate.Month >12)) {
	  printf("Invalid month\r\n");
	  stop();
  }

  inBufPtr = endPtr;
  if (*inBufPtr++ != '-') {
	  printf("Invalid date format\r\n");
	  stop();
  }
/* get the day */
  currentDate.Date = (uint8_t) strtol(inBufPtr,&endPtr,10);
  if ((currentDate.Date == 0) && (endPtr == inBufPtr)) {
	  printf("Could not convert the day from ascii to int\r\n");
	  stop();
  }
  else
	  printf("day: %d\r\n",currentDate.Date);
  if ((currentDate.Date == 0) || (currentDate.Date >31)) {
	  printf("Invalid day\r\n");
	  stop();
  }
  /* read time */

  printf("Please enter the current time in the format: hh:mm:ss ");
  inBufPtr = inBuf;

  for (noOfChars=0; noOfChars<18; noOfChars++) {
	  *inBufPtr = (char) getchar();
	  putchar(*inBufPtr);        /* echo the character */
	  if (*inBufPtr == '\r')
		  break;
	  inBufPtr++;
  }
  *inBufPtr++ = '\n';
  *inBufPtr = '\0';
  printf("\r\n");
  printf("No of chars read: %d\r\n",noOfChars);
  printf("Time read: %s\r\n",inBuf);

  inBufPtr = inBuf;
  currentTime.Hours = (uint8_t) strtol(inBufPtr,&endPtr,10);
  if ((currentTime.Hours == 0) && (endPtr == inBufPtr)) {
	  printf("Could not convert the hour from ascii to int\r\n");
	  stop();
  }
  else
	  printf("hour: %d\r\n",currentTime.Hours);

  if (currentTime.Hours > 23) {
	  printf("Invalid hour: should be 0..23\r\n");
	  stop();
  }

  inBufPtr = endPtr;
  if (*inBufPtr++ != ':') {
	  printf("Invalid time format\r\n");
	  stop();
  }

  currentTime.Minutes = (uint8_t) strtol(inBufPtr,&endPtr,10);
  if ((currentTime.Minutes == 0) && (endPtr == inBufPtr)) {
	  printf("Could not convert the minutes from sscii to int\r\n");
	  stop();
  }
  else
	  printf("min: %d\r\n",currentTime.Minutes);

  if (currentTime.Minutes > 59) {
	  printf("Invalid minutes: should be 0..59\r\n");
	  stop();
  }

  inBufPtr = endPtr;
  if (*inBufPtr++ != ':') {
	  printf("Invalid time format\r\n");
	  stop();
  }

  currentTime.Seconds = (uint8_t) strtol(inBufPtr,&endPtr,10);
  if ((currentTime.Seconds == 0) && (endPtr == inBufPtr)) {
	  printf("Could not convert the secondes from ascii to int\r\n");
	  stop();
  }
  else
	  printf("s: %d\r\n",currentTime.Seconds);

  if (currentTime.Seconds > 59) {
	  printf("Invalid seconds: should be 0..59\r\n");
	  stop();
  }
  currentTime.SecondFraction = 0;
  currentTime.StoreOperation = RTC_STOREOPERATION_RESET;
  currentTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;

  if (HAL_RTC_SetTime(&hrtc, &currentTime, RTC_FORMAT_BIN) != HAL_OK) {
	  printf("Count not set the time\r\n");
	  stop();
  }
  printf("Time successfully set\r\n");

  if (HAL_RTC_SetDate(&hrtc, &currentDate, RTC_FORMAT_BIN) != HAL_OK) {
	  printf("Count not set the time\r\n");
	  stop();
  }
  printf("Date successfully set\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		  printf("Cannot read time from RTC\r\n");
		  stop();
	  }
	  else
		  printf("Date: %02x-%02d-%02d   ",sDate.Year,sDate.Month,sDate.Date);

	  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		  printf("Cannot read time from RTC\r\n");
		  stop();
	  }
	  else
		  printf("Time: %02d:%02d:%02d\r\n",sTime.Hours,sTime.Minutes,sTime.Seconds);


	  HAL_Delay(5000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

    /**Initialize RTC and set the Time and Date 
    */
  sTime.Hours = 13;
  sTime.Minutes = 44;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN RTC_Init 3 */

  /* USER CODE END RTC_Init 3 */

  sDate.WeekDay = RTC_WEEKDAY_SATURDAY;
  sDate.Month = RTC_MONTH_SEPTEMBER;
  sDate.Date = 1;
  sDate.Year = 18;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN RTC_Init 4 */

  /* USER CODE END RTC_Init 4 */

    /**Enable the TimeStamp 
    */
  if (HAL_RTCEx_SetTimeStamp(&hrtc, RTC_TIMESTAMPEDGE_RISING) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN RTC_Init 5 */

  /* USER CODE END RTC_Init 5 */

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED2_Pin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
