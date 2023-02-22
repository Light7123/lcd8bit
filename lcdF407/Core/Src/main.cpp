/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "glcd.h"
#include "lcd_menu.h"
#include "button.h"
#include "string"
#include "string.h"
#include "strings.h"
#include "qrcode.h"
#include <stdarg.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int up_button=0;
int down_button=0;
int ok_button=0;
int reset_button=0;
int buttontimer=0;
int qr_flag=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_7&&HAL_GetTick()-buttontimer>300) // если прерывание поступило от ножки PA9
	{
		up_button=1;
		buttontimer=HAL_GetTick();
	}
	else
		if(GPIO_Pin == GPIO_PIN_6&&HAL_GetTick()-buttontimer>300) // если прерывание поступило от ножки PA9
		{
			down_button=1;
			buttontimer=HAL_GetTick();
		}
		else
			if(GPIO_Pin == GPIO_PIN_9&&HAL_GetTick()-buttontimer>300) // если прерывание поступило от ножки PA9
			{
				ok_button=1;
				buttontimer=HAL_GetTick();

			}
			else
				if(GPIO_Pin == GPIO_PIN_8&&HAL_GetTick()-buttontimer>300) // если прерывание поступило от ножки PA9
				{
					reset_button=1;
					qr_flag=0;
					buttontimer=HAL_GetTick();

				}

}

void AdafruitPrint(const char *args, ...)
{
	char StrBuff[256];
	va_list ap;
	va_start(ap, args);
	char len = vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
	va_end(ap);
	HAL_UART_Transmit(&huart5,(uint8_t*)StrBuff,len,100);
}


void QR()
{

	QRCode qrcode;

	char myIpQrData[120] ="https://electronics.stackexchange.com/questions/436803/how-to-design-an-stm32-board-with-uart-over-a-usb-connection";
	//prepareIpQrData(myIpQrData);

	const uint8_t ecc = 0;  //lowest level of error correction
	const uint8_t version = 11;

	uint8_t qrcodeData[qrcode_getBufferSize(version)];
	qrcode_initText(&qrcode,
			qrcodeData,
			version, ecc,
			myIpQrData);




	int qr[64][64] = {0};
	for (uint8_t y = 0; y < qrcode.size; y++) {
		for (uint8_t x = 0; x < qrcode.size; x++) {
			bool mod = qrcode_getModule(&qrcode, x, y);
			if(mod)
				qr[y][x] = 1;
			//sprintf(ch,"%u",qr[y][x] );
			//AdafruitPrint(ch);
		}
	//	AdafruitPrint("\n");
	}

	int sector8 = 0;
	//goto(y,0)
    		for(int y0 = 0;y0 <64; y0) {
    			for (uint8_t x = 0; x < 64; x++) {
    				for (uint8_t y = y0; y < y0 + 8; y++) {
    					if (qr[y][x] == 1)
    						sector8 |= 1 << y % 8;
    				}
    				glcd_gotoxy(x, y0/8);
    				glcd_putchar(sector8, 0);
    				sector8 = 0;
    			}
    			y0+=8;


    		}

}


void menu(int mode)
{
	switch (mode) {
		case 1:
			glcd_gotoxy(0, 0);
			for(int y=0;y<8;y++)
			{
				int x=0;
			for(int i=y*128;i<128*(y+1);i++)
			{
				glcd_gotoxy(x, y);
				glcd_putImage(wait[i], x);

				x++;
			}
			glcd_gotoxy(0, y+1);
			}

			break;
		case 2:
					glcd_gotoxy(0, 0);
					for(int y=0;y<8;y++)
					{
						int x=0;
					for(int i=y*128;i<128*(y+1);i++)
					{
						glcd_gotoxy(x, y);
						glcd_putImage(naliv[i], x);

						x++;
					}
					glcd_gotoxy(0, y+1);
					}

					break;

		case 3:
					glcd_gotoxy(0, 0);
					for(int y=0;y<8;y++)
					{
						int x=0;
					for(int i=y*128;i<128*(y+1);i++)
					{
						glcd_gotoxy(x, y);
						glcd_putImage(otmena[i], x);

						x++;
					}
					glcd_gotoxy(0, y+1);
					}

					break;

		case 4:
					if(qr_flag==0)
					{
					glcd_gotoxy(0, 0);
					for(int y=0;y<8;y++)
					{
						int x=0;
					for(int i=y*128;i<128*(y+1);i++)
					{
						glcd_gotoxy(x, y);
						glcd_putImage(oplata[i], x);

						x++;
					}
					glcd_gotoxy(0, y+1);
					}
					QR();
					qr_flag=1;
					}

					break;
		case 5:
					glcd_gotoxy(0, 0);
					for(int y=0;y<8;y++)
					{
						int x=0;
					for(int i=y*128;i<128*(y+1);i++)
					{
						glcd_gotoxy(x, y);
						glcd_putImage(vozvrat[i], x);

						x++;
					}
					glcd_gotoxy(0, y+1);
					}

					break;


	}


}

void nal_menu()
{
	switch (selectedMenuItem->payload.menu_ptr) {
		case menu1_ptr:
			menu(1);
			break;
		case menu2_ptr:
			menu(2);
					break;
		case menu3_ptr:
			menu(3);
					break;
		case menu4_ptr:
			menu(4);
					break;
		case menu5_ptr:
			menu(5);
					break;
	}
}


void QR_Reader()
{
	uint8_t QR_info[256];
	HAL_UARTEx_ReceiveToIdle_IT(&huart4, QR_info, 256);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_UART5_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	//HAL_UART_Transmit_IT(&huart5,(uint8_t*)"1\n", 2);
	glcd_on();
	glcd_clear_all();
	menu_init();
	startMenu();





	//QRcode qrcode;
	//HAL_UART_Transmit_IT(&huart5, (uint8_t*)"hello", 5);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		read_button();
		if(selectedMenuItem->payload.callback != nullptr)
			selectedMenuItem->payload.callback();
		//HAL_Delay(100);

		//  HAL_UART_Transmit(&huart5, (uint8_t*)"hello", 5, 500);




		// AdafruitPrint("\n");

		//HAL_UART_Transmit_IT(&huart5,(uint8_t*)"\n",1);
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
