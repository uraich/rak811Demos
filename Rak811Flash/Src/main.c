
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
#include "stm32l151xba.h"
#include "stm32l1xx_hal_flash_ex.h"
#include <stdlib.h>
#include <string.h>

#define BUFLEN           0x100
#define FLASH_USER_ADDR  0x08000000 + 0x20000 - BUFLEN //highest 256 bytes of flash
//#define FLASH_USER_ADDR 0x0801E000
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void read_flash_data(uint32_t addr, void *buffer, uint16_t len)
{
	memcpy(buffer, (void *)addr, len);
}

void erase_page(uint32_t addr) {
	FLASH_EraseInitTypeDef EraseInitStruct;
	HAL_StatusTypeDef retCode;
	uint32_t PAGEError = 0;

	HAL_FLASH_Unlock();
	printf("Erasing flash at address: 0x%lx\r\n",addr);
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = addr;
    EraseInitStruct.NbPages     = 1;
    if ((retCode = HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError))!= HAL_OK) {
    	printf("Flash erase error: 0x%02x\r\n",retCode);
    	printf("PAGEError: %ld\r\n",PAGEError);
    	retCode = HAL_FLASH_GetError();
    	printf("Flash error code is 0x%x\r\n",retCode);
    	return;
    }
	HAL_FLASH_Lock();
    printf("Page successfully erased\r\n");
}

void write_flash_data(uint32_t addr, void *buffer, uint16_t len)
{
	uint32_t *wr_data = buffer;
	int i = 0;

	printf("write_flash_data: address: 0x%lx, length: 0x%04x\r\n",addr,len);
	HAL_FLASH_Unlock();

	for (i = 0; i < len/4; i++) {
	    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *wr_data) != HAL_OK) {
	    	printf("Flash programming error at address: 0x%lx\r\n",addr);
	    	return;
	    }
        wr_data++;
        addr += 4;
	}
	//DelayMs(1000);
	HAL_FLASH_Lock();
}

void printBuf(uint8_t *buffer, uint16_t bufLen) {
	printf("0x000: ");
	for (int i=0; i<bufLen; i++) {
		if ((i != 0) && !(i % 16)) {
			printf("\r\n");
			if ((i+1) < bufLen)
				printf("0x%03x: ",i);
		}
		printf("0x%02x ",buffer[i]);
	}
	printf("\r\n\n");
}

void printOptionBytes(FLASH_OBProgramInitTypeDef *optionBytes) {
	printf("Option bytes:\r\n");
	printf("OptionType:       0x%lx\r\n",optionBytes->OptionType);
	printf("WRPState  :       0x%lx\r\n",optionBytes->WRPState);
	printf("WRPSector0To31 :  0x%lx\r\n",optionBytes->WRPSector0To31);
	printf("RDPLevel:         0x%02x\r\n",optionBytes->RDPLevel);
	printf("BORLevel:         0x%02x\r\n",optionBytes->BORLevel);
	printf("USERConfig:       0x%02x\r\n",optionBytes->USERConfig);
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
	uint8_t outBuf[BUFLEN];
	uint8_t inBuf[BUFLEN];
	uint32_t tmp,flash_status;
	FLASH_OBProgramInitTypeDef optionBytes;

	flash_status = FLASH->SR;

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("Writing and Reading Flash\r\n");
  printf ("The program writes Hello World! to flash and reads it back\r\n");
  printf("Flash is at address 0x%lx\r\n",(long)FLASH_USER_ADDR);

  HAL_FLASHEx_OBGetConfig(&optionBytes);
  printOptionBytes(&optionBytes);

  printf("The option bytes\r\n");
  tmp = OB->RDP;
  printf("RDP:   0x%08lx\r\n",tmp);
  tmp = OB->USER;
  printf("USER:  0x%08lx\r\n",tmp);
  tmp = OB->WRP01;
  printf("WRP01: 0x%08lx\r\n",tmp);
  tmp = OB->WRP23;
  printf("WRP23: 0x%08lx\r\n",tmp);

  printf("Flash status after reset: 0x%08lx\r\n",flash_status);

//  printf("Flash status after HAL_Init(): 0x%08lx\r\n",tmp1);

  FLASH->SR = (uint32_t) 0x800;
  HAL_Delay(10);
  tmp = FLASH->SR;
  printf("Flash status after write: 0x%08lx\r\n",tmp);
  tmp = FLASH->OBR;
   printf("Flash OBR 0x%08lx\r\n",tmp);
//#define READY 1

  /*
   * clear out the page buffer, write "Hello World!" into it and print it
   */
  memset(outBuf,0,BUFLEN);
  strcpy((char *)outBuf,"Hello World!\r\n");
  printf("out buffer: \r\n");
  printBuf(outBuf,(uint16_t) BUFLEN);
  /*
   * read the current data from the flash page and print it
   */
  read_flash_data(FLASH_USER_ADDR, inBuf, (uint16_t) BUFLEN );
  printf("Beginning of flash buffer: %s\r\n",inBuf);
  printBuf(inBuf,(uint16_t) BUFLEN);
  /*
   * erase the page and print the values after erase
   */
  erase_page(FLASH_USER_ADDR);
  printf("Buffer after erase: \r\n");
  read_flash_data(FLASH_USER_ADDR, inBuf, (uint16_t) BUFLEN );
  printBuf(inBuf,(uint16_t) BUFLEN);
  /*
   * write the flash with the previously prepared output buffer
   */
  write_flash_data(FLASH_USER_ADDR, outBuf, (uint16_t) BUFLEN );
  /*
   * read back the flash page and print its contents to check if writing was successful
   */
  read_flash_data(FLASH_USER_ADDR, inBuf, (uint16_t) BUFLEN );
  printf("Flash after write: \r\n");
  printBuf(inBuf,(uint16_t) BUFLEN);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

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

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
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

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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
