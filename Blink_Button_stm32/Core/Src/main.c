#include "main.h"
#include "stdbool.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void button_press(void);

bool flag_block, flag_block1, flag_set1;

int main(void){
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	flag_block = 0;
	flag_block1 = 0;
	flag_set1 = 0;

	while (1){
		button_press();
	}
}

static void button_press(void){
//	if(HAL_GPIO_ReadPin(GPIOC, BUTT_Pin)){			//якщо кнопка натиснута,тод≥ вмикаЇмо св≥тло≥ндикац≥ю
//		GPIOC -> BSRR = (uint32_t)Led_Pin << 16;
//	} else {										//јбо не св≥титьс€
//		GPIOC -> BSRR = (uint32_t)Led_Pin;
//	}

	if((GPIOC -> IDR & BUTT_Pin) && !flag_block1){
		flag_block = 1;
		flag_set1 = !flag_set1;
		if(flag_set1){
			GPIOC -> BSRR = Led_Pin;
		} else if(!flag_set1){
			GPIOC -> BRR = Led_Pin;
		}
	} else if((GPIOC -> IDR & BUTT_Pin) && flag_block1){
		flag_block = 0;
	}
}

void SystemClock_Config(void){
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK){
		Error_Handler();
	}
}

static void MX_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Led_Pin */
	GPIO_InitStruct.Pin = Led_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Led_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTT_Pin */
	GPIO_InitStruct.Pin = BUTT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BUTT_GPIO_Port, &GPIO_InitStruct);

}

void Error_Handler(void){
	__disable_irq();
	while (1){
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line){
}
#endif