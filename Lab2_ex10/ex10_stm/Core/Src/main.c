/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int timer4_flag = 0;
int timer4_counter = 0;
int timer3_flag = 0;
int timer3_counter = 0;
int timer2_flag = 0;
int timer2_counter = 0;
int timer1_flag = 0;
int timer1_counter = 0;
int timer0_flag = 0;
int timer0_counter = 0;
int TIMER_CYCLE = 10;

void setTimer4(int duration)
{
	timer4_counter = duration/TIMER_CYCLE;
	timer4_flag = 0;
}
void setTimer3(int duration)
{
	timer3_counter = duration/TIMER_CYCLE;
	timer3_flag = 0;
}
void setTimer2(int duration)
{
	timer2_counter = duration/TIMER_CYCLE;
	timer2_flag = 0;
}
void setTimer1(int duration)
{
	timer1_counter = duration/TIMER_CYCLE;
	timer1_flag = 0;
}

void setTimer0(int duration)
{
	timer0_counter = duration/TIMER_CYCLE;
	timer0_flag = 0;
}

void timerRun()
{
	if(timer4_counter > 0){
		timer4_counter--;
		if(timer4_counter <= 0){
			timer4_flag = 1;
		}
	}
	if(timer3_counter > 0){
		timer3_counter--;
		if(timer3_counter <= 0){
			timer3_flag = 1;
		}
	}

	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter <= 0){
			timer2_flag = 1;
		}
	}
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}

	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter <= 0){
			timer0_flag = 1;
		}
	}
}
int hour, minute, second;
const int MAX_LED = 4;
int index_led = 0;
int led_buffer [4] = {6, 7, 8, 9};
int counter_LEDRED = 100;
int counter_LED7SEG = 25;

int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer [8] = {0x18,0x24,0x42,0x42,0x7e,0x42,0x42,0x42};//moi phan tu dai dien cho 1 row=>>doi ra he ma nhi phan va ket hop lai se duoc chu 'A'
void displayLedMatrix(int row, int col){
	int shift = 1;// mask used to get bit by bit of buffer

	if(row == 0){// enable row 0
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));//compare bit neu bi nho nhat = 0 =>> (col & shift) = 0 =>> 1- 0 = 1 = GPIO_PIN_SET
		col = col >> 1;//shift to left = divide by 2
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 1){// enable row 1
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 2){// enable row 2
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 3){// enable row 3
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 4){// enable row 4
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 5){// enable row 5
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 6){// enable row 6
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

	if(row == 7){// enable row 7
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);

		// get bit by bit of buffer, then assign to ENM-PIN to control col-PIN
		HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1 - (col & shift));
		col = col >> 1;
		HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin,  1 - (col & shift));
	}

}

void updateLedMatrix(int index){
	switch(index){
	case 0:// display row 0 of led matrix
		displayLedMatrix(0, matrix_buffer[0]);
		break;
	case 1:// display row 1 of led matrix
		displayLedMatrix(1, matrix_buffer[1]);
		break;
	case 2:// display row 2 of led matrix
		displayLedMatrix(2, matrix_buffer[2]);
		break;
	case 3:// display row 3 of led matrix
		displayLedMatrix(3, matrix_buffer[3]);
		break;
	case 4:// display row 4 of led matrix
		displayLedMatrix(4, matrix_buffer[4]);
		break;
	case 5:// display row 5 of led matrix
		displayLedMatrix(5, matrix_buffer[5]);
		break;
	case 6:// display row 6 of led matrix
		displayLedMatrix(6, matrix_buffer[6]);
		break;
	case 7:// display row 7 of led matrix
		displayLedMatrix(7, matrix_buffer[7]);
		break;
	default:
		break;
	}
}
void updateClockBuffer ()
{
	led_buffer[0] = hour / 10;
	led_buffer [1] = hour % 10;
	led_buffer [2] = minute / 10;
	led_buffer [3] = minute % 10;
}

void display7SEG(int num ) {

	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 , GPIO_PIN_SET ) ;
	switch (num) {
        case 0:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 , GPIO_PIN_RESET ) ;
            break;
        case 1:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_1|GPIO_PIN_2 , GPIO_PIN_RESET ) ;
            break;
        case 2:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;
        case 3:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;
        case 4:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;
        case 5:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;
        case 6:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;
        case 7:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET ) ;
            break;
        case 8:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;
        case 9:
        	HAL_GPIO_WritePin ( GPIOB , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6 , GPIO_PIN_RESET ) ;
            break;

    }
}

void update7SEG (int state)
{
	 switch ( state ) {
		         case 0:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
					display7SEG(led_buffer[0]);
					state = 1;
	                break;
		         case 1:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
					display7SEG(led_buffer[1]);
					state = 2;
					break;
		         case 2:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
					display7SEG(led_buffer[2]);
					state = 3;
					break;
		         case 3:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
					display7SEG(led_buffer[3]);
					state = 0;
					break;
		         default:
		        	 break;
		     }
}

void updateMatrix_buffer(){

	    matrix_buffer[0] = (matrix_buffer[0] << 1|matrix_buffer[1] >> 7);
		matrix_buffer[1] = (matrix_buffer[1] << 1|matrix_buffer[1] >> 7);
		matrix_buffer[2] = (matrix_buffer[2] << 1|matrix_buffer[2] >> 7);
		matrix_buffer[3] = (matrix_buffer[3] << 1|matrix_buffer[3] >> 7);
		matrix_buffer[4] = (matrix_buffer[4] << 1|matrix_buffer[4] >> 7);
		matrix_buffer[5] = (matrix_buffer[5] << 1|matrix_buffer[5] >> 7);
		matrix_buffer[6] = (matrix_buffer[6] << 1|matrix_buffer[6] >> 7);
		matrix_buffer[7] = (matrix_buffer[7] << 1|matrix_buffer[7] >> 7);
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 ) ;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(10);
  setTimer1(10);
  setTimer2(10);
  setTimer3(10);
  setTimer4(800);
  hour = 15, minute = 8, second = 50;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if ( timer0_flag ) {//control red led
	      HAL_GPIO_TogglePin ( GPIOA , GPIO_PIN_4 ) ;
	      HAL_GPIO_TogglePin ( GPIOA , GPIO_PIN_5 ) ;
	      setTimer0 ( 1000 ) ;
	  }
	  if(timer1_flag){//control time
		  second ++;
		  if (second >= 60)
		  {
			  second = 0;
		  	  minute++;
		  }
		  if(minute >= 60)
		  {
			  minute = 0;
		  	  hour++;
		  }
		  if(hour >= 24)
		  {
			  hour = 0;
		  }
		      updateClockBuffer();
		      setTimer1(1000);
	  }
	  if(timer2_flag){//control 4 7SEG LED
	 	counter_LED7SEG = 25;
	 	update7SEG(index_led++);
	 	if(index_led == MAX_LED) index_led = 0;
	 	setTimer2(250);
	  }

	  if(timer3_flag )// control led matrix
	  {
			updateLedMatrix(index_led_matrix++);
			if(index_led_matrix == MAX_LED_MATRIX) index_led_matrix = 0;
			setTimer3(100);
	  }

	  if(timer4_flag )// control animation led matrix
	  {
		    updateMatrix_buffer();
			setTimer4(800);
	  }

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Seg_0_Pin|Seg_1_Pin|Seg_2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|Seg_3_Pin|Seg_4_Pin|Seg_5_Pin
                          |Seg_6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Seg_0_Pin Seg_1_Pin Seg_2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin Seg_3_Pin Seg_4_Pin Seg_5_Pin
                           Seg_6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = Seg_0_Pin|Seg_1_Pin|Seg_2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|Seg_3_Pin|Seg_4_Pin|Seg_5_Pin
                          |Seg_6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	timerRun();
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
