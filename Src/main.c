#include "main.h"
#include "stm32h7xx_hal.h"
#include "usb_device.h"
#include "usbd_custom_hid_if.h"
#include "usbd_customhid.h"

#define DELAY 22000


SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;
SPI_HandleTypeDef hspi6;

UART_HandleTypeDef huart1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_SPI4_Init(void);
static void MX_SPI6_Init(void);

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t usb_rx_buffer[64];
uint16_t SPI1_RxBuffer[5],SPI2_RxBuffer[5],SPI3_RxBuffer[5],SPI4_RxBuffer[5],SPI5_RxBuffer[5],SPI6_RxBuffer[5];
int motor = 0;
uint16_t motorSetPoints[32] = {0};
int32_t TailSetpoint[16] = {0};
int Angle;
uint16_t SendData[5] = {1,0x91,0,0,0}, RetData[5] = {0}, LegData[20];
void USB_RX_Interrupt(){
	int k = 0;
	USBD_CUSTOM_HID_HandleTypeDef *myusb=(USBD_CUSTOM_HID_HandleTypeDef *)hUsbDeviceFS.pClassData;
	uint16_t i = 0;
	k = 0;

	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

	for(i=0;i<64;i++)
	{
		usb_rx_buffer[i]=myusb->Report_buf[i]; //making local version of usb RX USB Data
	}

	if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1962){ //check id equals 1962, Motor pos id
		for(int x = 4; x<64; x+=2){
			motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
			k++;
		}
		if(motorSetPoints[0] != 0 || motorSetPoints[1] != 0)
		{
			SendData[1] = 0x91;
			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				SendData[2] = motorSetPoints[x];
				HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
				HAL_SPI_TransmitReceive(&hspi2, SendData, RetData, 5, 0x100);
				HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);

				SendData[2] = motorSetPoints[x+4];
				HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
				HAL_SPI_TransmitReceive(&hspi1, SendData, RetData,  5, 0x100);
				HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);

				SendData[2] = motorSetPoints[x+8];
				HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
				HAL_SPI_TransmitReceive(&hspi4, SendData, RetData, 5, 0x100);
				HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);

				SendData[2] = motorSetPoints[x+12];
				HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
				HAL_SPI_TransmitReceive(&hspi2, SendData, RetData, 5, 0x100);
				HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);

				if(x<2){
					SendData[2] = motorSetPoints[x+16];
					HAL_GPIO_WritePin(CS_HEAD_GPIO_Port, CS_HEAD_Pin, GPIO_PIN_RESET);
					HAL_SPI_TransmitReceive(&hspi6, SendData, RetData, 5, 0x100);
					HAL_GPIO_WritePin(CS_HEAD_GPIO_Port, CS_HEAD_Pin, GPIO_PIN_SET);
					if(x == 0){
						uint16_t TailData[2] = {0};
						TailData[0] = motorSetPoints[18]-9000;
						TailData[1] = motorSetPoints[19]-9000;
						HAL_GPIO_WritePin(CS_TAIL_GPIO_Port, CS_HEAD_Pin, GPIO_PIN_RESET);
						HAL_SPI_Transmit(&hspi6, TailData, 2, 0x100);
						HAL_GPIO_WritePin(CS_TAIL_GPIO_Port, CS_HEAD_Pin, GPIO_PIN_SET);
					}

				}


				uint64_t j = 0;
				while(j<DELAY){
					j++;
				}
			}
		}
	}


	else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1804){ //check id equals 1643, KP
		//request data from IMU 1

		//		uint16_t RequestIMUData[9] = {0,0,0,0,0,0,0,0,0};
		//		uint16_t getIMUData[9] = {0};
		//
		//		HAL_GPIO_WritePin(IMU1_CS_Port, IMU1_CS_Pin, GPIO_PIN_RESET);
		//		HAL_SPI_TransmitReceive(&hspi1, RequestIMUData, getIMUData, 9, 0x100); //request 9 16bbit ints from IMU board
		//		HAL_GPIO_WritePin(IMU1_CS_Port, IMU1_CS_Pin, GPIO_PIN_SET);
		//
		//
		//		//Copy Recieved Data to USB Buffer
		//		for(int k = 0;k<9;k++){
		//			//usb_rx_buffer[2*k+4] = getIMUData[k]>>8;
		//			//usb_rx_buffer[2*k+4] = (uint8_t)getIMUData[k];
		//		}


	}
	else if(((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1643)||((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1644)||
			((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1645)||((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1646)||
			((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1647)){

		if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1643){ //check id equals 1643, KP
			SendData[1] = 0xA0;
			SendData[3] = 1;
			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}
		else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1644){ //check id equals 1644, KI
			SendData[1] = 0xA1;
			SendData[3] = 1;

			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}
		else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1645){ //check id equals 1643, KD
			SendData[1] = 0xA2;
			SendData[3] = 1;

			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}

		else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1645){ //check id equals 1644, KD
			SendData[1] = 0xA3;
			SendData[3] = 1;

			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}

		else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1645){ //check id equals 1645, KD
			SendData[1] = 0xA4;
			SendData[3] = 1;
			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}
		else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1646){ //check id equals 1646, Grav
			SendData[1] = 0xA5;
			SendData[3] = 1;

			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}
		else if((usb_rx_buffer[1]<<8|usb_rx_buffer[0]) == 1647){ //check id equals 1647, Cor
			SendData[1] = 0xA6;
			SendData[3] = 1;
			k = 0;
			for(int x =4 ; x<64; x+=2){
				motorSetPoints[k] = usb_rx_buffer[x]<<8|usb_rx_buffer[x+1]; //bitshift motor data
				k++;
			}

			for(int x = 0;x<4;x++){
				SendData[0] = x+2;

				if( motorSetPoints[x]!=0){
					SendData[2] = motorSetPoints[x];
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x100);
					HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
				}
				if( motorSetPoints[x+4]!=0){
					SendData[2] = motorSetPoints[x+4];
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+8]!=0){
					SendData[2] = motorSetPoints[x+8];
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi4, SendData, 5, 0x10);
					HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_SET);
				}

				if( motorSetPoints[x+12]!=0){
					SendData[2] = motorSetPoints[x+12];
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi2, SendData, 5, 0x10);
					HAL_GPIO_WritePin(IMU2_CS_GPIO_Port, IMU2_CS_Pin, GPIO_PIN_SET);
				}
			}
		}

	}
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,usb_rx_buffer,64); //reply usb data over usbFS

	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

}
int main(void)
{
	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_SPI3_Init();
	MX_SPI4_Init();
	MX_SPI6_Init();
	MX_USB_DEVICE_Init();

	while (1)
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);//heartbeat led
		HAL_Delay(100);

	}

}

void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY)
	{

	}

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 2;
	RCC_OscInitStruct.PLL.PLLN = 48;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 16;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}


	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
			|RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SPI4
			|RCC_PERIPHCLK_SPI3|RCC_PERIPHCLK_SPI1
			|RCC_PERIPHCLK_SPI2|RCC_PERIPHCLK_SPI6
			|RCC_PERIPHCLK_USB;
	PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
	PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
	PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
	PeriphClkInitStruct.Spi6ClockSelection = RCC_SPI6CLKSOURCE_D3PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	HAL_SYSTICK_Config(SystemCoreClock/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 7;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

static void MX_SPI2_Init(void)
{

	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi2.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi2.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

static void MX_SPI3_Init(void)
{

	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 7;
	hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi3.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi3.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi3) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

static void MX_SPI4_Init(void)
{

	hspi4.Instance = SPI4;
	hspi4.Init.Mode = SPI_MODE_MASTER;
	hspi4.Init.Direction = SPI_DIRECTION_2LINES;
	hspi4.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi4.Init.NSS = SPI_NSS_SOFT;
	hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi4.Init.CRCPolynomial = 7;
	hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi4.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi4.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi4) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* SPI6 init function */
static void MX_SPI6_Init(void)
{

	hspi6.Instance = SPI6;
	hspi6.Init.Mode = SPI_MODE_MASTER;
	hspi6.Init.Direction = SPI_DIRECTION_2LINES;
	hspi6.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi6.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi6.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi6.Init.NSS = SPI_NSS_SOFT;
	hspi6.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi6.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi6.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi6.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi6.Init.CRCPolynomial = 7;
	hspi6.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi6.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi6.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi6.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi6.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi6.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi6.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi6.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi6.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi6.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi6) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

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
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.Prescaler = UART_PRESCALER_DIV1;
	huart1.Init.FIFOMode = UART_FIFOMODE_DISABLE;
	huart1.Init.TXFIFOThreshold = UART_TXFIFO_THRESHOLD_1_8;
	huart1.Init.RXFIFOThreshold = UART_RXFIFO_THRESHOLD_1_8;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

static void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	HAL_GPIO_WritePin(GPIOE, CS4_Pin|IMU2_CS_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin|IMU1_CS_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOD, LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(CS3_GPIO_Port, CS3_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOD, CS_TAIL_Pin|CS_HEAD_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(CS6_GPIO_Port, CS6_Pin, GPIO_PIN_SET);

	GPIO_InitStruct.Pin = CS4_Pin|IMU2_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = CS2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(CS2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = CS1_Pin|IMU1_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(CS1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|CS_TAIL_Pin
			|CS_HEAD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = CS3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(CS3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = CS6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(CS6_GPIO_Port, &GPIO_InitStruct);

}

void _Error_Handler(char *file, int line)
{
	while(1)
	{
	}
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

}
#endif
