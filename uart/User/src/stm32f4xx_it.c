/**
  ******************************************************************************
  * @file    Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define STR_MAX_LENGTH	100
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
}
__IO uint32_t Timmer4 = 0;
__IO uint32_t Timmer_Led_Off = 0;
extern int counter;
extern uint8_t mode_counter;
void TIM4_IRQHandler(void)
{
  static uint32_t time = 0;
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
		time++;
    if(time>1000)
    {
			if(mode_counter == 1)
			{
				counter --;
			}
			else if(mode_counter == 2)
			{
				counter ++;
			}
      Timmer4 = 1;
      time = 0;
    }
		if(time == 500)
		{
			Timmer_Led_Off = 1;
		}
   TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
  }
}
extern struct queue_t queue_send;
extern uint8_t mode;
extern uint8_t id;
extern volatile char flag;
extern uint8_t oper;
extern struct queue_t queue_number_1;
extern struct queue_t queue_number_2;
extern int sign_number_1;
extern int sign_number_2;
extern struct queue_t queue_counter;
void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_TXE) == SET)
	{
		if(Queue_Is_Empty(&queue_send) == 0)	
		{
			uint8_t send = Queue_Pop(&queue_send);
      USART_SendData(USART3, (uint16_t)send);
    }else
		{
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		}
	}
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
      uint8_t receive = (uint8_t)USART_ReceiveData(USART3);
			mode = receive;
			//past_id = id;
			switch(id)
			{
				case 0:
					switch(mode)
					{
						case 49:
							id = 1;
							break;
						case 50:
							id = 2;
							break;
						case 51:
							id = 6;
							break;
						case 52:
							id = 11;
							break;
						case 27:
							id = 0;
							break;
						default:
							id = 14;
							break;
					}
					break;
				case 1:
					if(mode == 27)
					{
						id = 0;
					}else
					{
						//error
						id = 14;
					}
					break;
				case 2:
					switch(mode)
					{	
						case 49:
							oper = 1;
							id = 3;
							break;
						
						case 50:
							oper = 2;
							id = 3;
							break;
						
						case 51:
							oper = 3;
							id = 3;
							break;
						
						case 52:
							oper = 4;
							id = 3;
							break;
						
						case 53:
							oper = 5;
							id = 3;
							break;
						
						case 54:
							id = 0;
							break;
						
						case 27:
							id = 0;
							break;
						
						default:
							//error
							id = 14;
							break;
						}
						break;
					
					case 3:
						if(mode >= 48 && mode <= 57)
						{
							Queue_Push(&queue_number_1 , mode - 0x30);
							id = 3;
							flag = 0;
							return;
						}
						else if(mode == 27)
						{
							id = 2;
						}
						else if(mode == 13)
						{
							id = 4;
						}else if(mode == 45 && Queue_Is_Empty(&queue_number_1) == 1)
						{
							sign_number_1 = -1;
							id = 3;
							flag = 0;
							return;
						}else
						{
							id = 3;
							flag = 0;
							return;
						}
						break;
				case 4:
						if(mode >= 48 && mode <= 57)
						{
							Queue_Push(&queue_number_2 , mode - 0x30);
							id = 4;
							flag = 0;
							return;
						}
						else if(mode == 27)
						{
							id = 2;
						}
						else if(mode == 13)
						{
							id = 5;
						}else if(mode == 45 && Queue_Is_Empty(&queue_number_2) == 1)
						{
							sign_number_2 = -1;
							id = 4;
							flag = 0;
							return;
						}else
						{
							//error
							flag = 0;
							id = 4;
							return;
						}
						break;
						
				case 5:
					id = 2;
					break;
				
				case 6:
					switch(mode)
					{
						case 49:
							id = 7;
							break;
						case 50:
							id = 8;
							break;
						case 51:
							mode_counter = 1;
							id = 9;
							break;
						case 27:
							id = 0;
							break;
						default:
							id = 14;
							break;
					}
					break;
				
				case 7:
					if(mode == 27)
					{
						id = 6;
					}else
					{
						id = 14;
					}
					break;
					
				case 8:
					if(mode == 27)
					{
						id = 6;
					}else
					{
						id = 14;
					}
					break;
						
				case 9:
					if(mode >= 48 && mode <= 57)
					{
						Queue_Push(&queue_counter , mode - 0x30);
						id = 9;
		 			  flag = 0;
						return;
					}else if(mode == 13)
					{
						id = 10;
					}else if(mode == 27)
					{
						id = 6;
					}else
					{
						id = 14;
					}						
					break;
					
				case 10:
					id = 9;
					break;
				
				case 11:
					switch(mode)
					{
						case 49:
							id = 12;
							mode_counter = 1;
							break;
						case 50:
							id = 13;
							mode_counter = 2;
							break;
						case 27:
							id = 0;
							break;
						default:
							id = 14;
							break;
					}
					break;
				
				case 12:
					if(mode >= 48 && mode <= 57)
					{
						Queue_Push(&queue_counter , mode - 0x30);
						id = 12;
		 			  flag = 0;
						return;
					}else if(mode == 13)
					{
						counter = decoder(&queue_counter,queue_counter.capacity);
						id = 15;
					}else if(mode == 27)
					{
						id = 11;
					}else
					{
						id = 14;
					}						
					break;
				
				case 13:
					switch(mode)
					{
						case 49:
							id = 15;
							break;
						case 27:
							id = 11;
							mode_counter = 3;
							break;
						default:
							id = 14;
							break;
					}
					break;
					
				case 15:	
					if(mode_counter == 1)
					{
						id = 12;
					}else
					{
						id = 11;
					}
					break;
						
				case 14:
					id = 0;
					break;
				
				default:
					id = 14;
					break;
			}
      flag = 1;
			USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
	}
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/*void USART3_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
