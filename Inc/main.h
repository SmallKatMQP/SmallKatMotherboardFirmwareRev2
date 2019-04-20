#ifndef __MAIN_H__
#define __MAIN_H__


#define CS4_Pin GPIO_PIN_4
#define CS4_GPIO_Port GPIOE
#define CS2_Pin GPIO_PIN_3
#define CS2_GPIO_Port GPIOC
#define CS1_Pin GPIO_PIN_4
#define CS1_GPIO_Port GPIOA
#define IMU2_CS_Pin GPIO_PIN_7
#define IMU2_CS_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_12
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_13
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_14
#define LED3_GPIO_Port GPIOD
#define CS3_Pin GPIO_PIN_15
#define CS3_GPIO_Port GPIOA
#define CS_TAIL_Pin GPIO_PIN_0
#define CS_TAIL_GPIO_Port GPIOD
#define CS_HEAD_Pin GPIO_PIN_7
#define CS_HEAD_GPIO_Port GPIOD
#define CS6_Pin GPIO_PIN_6
#define CS6_GPIO_Port GPIOB
#define IMU1_CS_Port GPIOA
#define IMU1_CS_Pin GPIO_PIN_1


#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif
