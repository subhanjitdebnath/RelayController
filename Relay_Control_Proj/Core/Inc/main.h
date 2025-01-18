/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
void SignalTest();
void GPIOUpdate();
void Operation();
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN3_Pin GPIO_PIN_11
#define BTN3_GPIO_Port GPIOC
#define BTN2_Pin GPIO_PIN_12
#define BTN2_GPIO_Port GPIOC
#define BTN1_Pin GPIO_PIN_13
#define BTN1_GPIO_Port GPIOC
#define RELAY1_Pin GPIO_PIN_0
#define RELAY1_GPIO_Port GPIOC
#define RELAY2_Pin GPIO_PIN_1
#define RELAY2_GPIO_Port GPIOC
#define OPT1_Pin GPIO_PIN_2
#define OPT1_GPIO_Port GPIOB
#define OPT2_Pin GPIO_PIN_10
#define OPT2_GPIO_Port GPIOB
#define OPT3_Pin GPIO_PIN_11
#define OPT3_GPIO_Port GPIOB
#define OPT4_Pin GPIO_PIN_12
#define OPT4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
void SetALlLed();
void ResetALlLed();
void UpdateDisplay();
void GetButtonStatus();
void UpdateLedStatus();
void Dn_Sensor_execution();
void Up_Sensor_execution();
void BlinkLedFunc();

void CheckForMiddleVal();
void SequenceMode();
void SingleMode();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
