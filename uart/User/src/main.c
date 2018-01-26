#include "main.h"

	void TIM4_Configuration(void);
	NVIC_InitTypeDef nvic_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	volatile char flag;
	extern __IO uint32_t Timmer4;
	extern __IO uint32_t Timmer_Led_Off;
	
	struct queue_t queue_send;
	struct queue_t queue_receive;
	struct queue_t queue_number_1;
	struct queue_t queue_number_2;
	struct queue_t queue_result;
  struct queue_t queue_decimal;
	struct queue_t queue_counter;
	
	char* error = "Error!!!!!!! ESC to return main menu";
	char* inputOption = "Choose your option (1,2,..): ";
	char* inputName = "1.Student infomation";
	char* inputOperation = "2.Basic Operation";
	char* inputSimpleLed = "3.Simple Led";
	char* inputAvanceLed = "4.Timmer";
	char* Name = "Name: Huynh Huu Loi";
	char* MSSV = "MSSV: 14520480";
	char* ESC = "ESC: return previous menu";
	char* Plus = "1.Plus";
	char* Subtract = "2.Subtract";
	char* Multiple = "3.Multiple";
	char* Divide = "4.Divide";
	char* Module = "5.Module";
	char* newLineStr = "\r\n";
	char* number_1 = "Number 1st: ";
	char* number_2 = "Number 2nd: ";
	char* operation_result = "Result: ";
	char* Turn_On_Led_Red = "1.Turn On Led RED";
	char* Turn_On_Led_Green = "2.Turn On Led Green";
	char* Blink_Led = "3.Blink Led";
	char* Running = "Running..................";
	char* Count_Down = "1. Count Down";
	char* Stop_Watch = "2. Stop Watch";
	char* Counter_Time_Blink = "Enter the time blink led: ";
	char* Counter_Down = "Enter the time count down: ";
	char* Stop_Watch_Input = "Press 1 to start";
	
	int i ;
	uint8_t mode;
	uint8_t id = 0;
	uint8_t past_id = 0;
	uint8_t oper = 0;
	uint8_t sign_flag = 0;
	uint8_t mode_counter = 0;
	int counter = 0;
	int sign_number_1 = 1;
	int sign_number_2 = 1;
	int result_decode;
	double num1 = 0;
	double num2 = 0;
	double result = 0;
	
	void main_option(void);
	void student_info(void);
	void operation_option(void);
	void munber1_option(void);
	void number2_option(void);
	void operation_result_option(void);
	void led_option(void);
	void led_red_option(void);
	void led_green_option(void);
	void blink_led_option(void);
	void blink_led_running(void);
	void timmer_option(void);
	void input_countdown(void);
	void input_stopwatch(void);
	void error_option(void);
int main(){
	
	uart_interrupt_my_init();
	TIM4_Configuration();
	// Enable GPIOD clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		
	//Systick Configuration
	SysTick_Config(SystemCoreClock/1000);
	
	Queue_Init(&queue_counter);
	Queue_Init(&queue_number_1);
	Queue_Init(&queue_number_2);
	Queue_Init(&queue_decimal);
	Queue_Init(&queue_result);
	// Queue send
	Queue_Init(&queue_send);
	// Queue receive
	Queue_Init(&queue_receive);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	
	main_option();

	for(;;){
		while(flag == 0){};
			switch(id)
			{
				case 0:
					main_option();
					break;
				
				case 1:
					student_info();
					break;
				
				case 2:
					operation_option();
					break;
					
				case 3:
					munber1_option();
					break;
				
				case 4:
					number2_option();
					break;
				
				case 5:
					operation_result_option();
					break;
					
				case 6:
					led_option();
					break;
					
				case 7:
					led_red_option();
					break;
				
				case 8:
					led_green_option();
					break;
				
				case 9:
					blink_led_option();
					break;
				
					case 10:
					blink_led_running();
					break;
				
				case 11:
					timmer_option();
					break;
				
				case 12:
					input_countdown();
					break;
					
				case 13:
					input_stopwatch();
					break;
				
				case 15:
					flag = 0;
					Push_string(&queue_send, newLineStr, strlen(newLineStr));
					Push_string(&queue_send, ESC, strlen(ESC));
					Push_string(&queue_send, newLineStr, strlen(newLineStr));
					Push_string(&queue_send, Running, strlen(Running));
					Push_string(&queue_send, newLineStr, strlen(newLineStr));
								
					USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
					if(mode_counter == 1)
					{
						TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
						TIM_Cmd(TIM4, ENABLE);
						
						while(counter != 0)
						{
							if(Timmer4 == 1)
							{
								encoder(&queue_counter, counter);
								remove_zero(&queue_counter);
								reverse_queue(&queue_counter,queue_counter.capacity);
								Push_queue(&queue_send, &queue_counter, queue_counter.capacity);
								Push_string(&queue_send, newLineStr, strlen(newLineStr));
								USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
								Timmer4 = 0;
							}
						}
						TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
						TIM_Cmd(TIM4, DISABLE);
						
						Push_string(&queue_send, "Time Out!", 9);
					}else if(mode_counter == 2)
					{
						mode = 0;
						TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
						TIM_Cmd(TIM4, ENABLE);
						for(;;)
						{
							if(Timmer4 == 1)
							{
								encoder(&queue_counter, counter);
								remove_zero(&queue_counter);
								reverse_queue(&queue_counter,queue_counter.capacity);
								Push_queue(&queue_send, &queue_counter, queue_counter.capacity);
								Push_string(&queue_send, newLineStr, strlen(newLineStr));
								USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
								Timmer4 = 0;
							}else if(mode == 27)
							{
								counter = 0;
								break;
							}
							
						}
						TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
						TIM_Cmd(TIM4, DISABLE);
					}else
					{
						counter = 0;
						TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
						TIM_Cmd(TIM4, DISABLE);
					}
					break;
					
				case 14:
					error_option();
					break;
					
			}
	}
}

void main_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, inputOption, strlen(inputOption));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, inputName, strlen(inputName));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, inputOperation, strlen(inputOperation));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, inputSimpleLed, strlen(inputSimpleLed));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, inputAvanceLed, strlen(inputAvanceLed));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void student_info()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Name, strlen(Name));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, MSSV, strlen(MSSV));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void operation_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Plus, strlen(Plus));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Subtract, strlen(Subtract));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Multiple, strlen(Multiple));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Divide, strlen(Divide));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Module, strlen(Module));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
					
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void munber1_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, number_1, strlen(number_1));
					
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void number2_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, number_2, strlen(number_2));
					
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void operation_result_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, operation_result, strlen(operation_result));
	operation(oper, &queue_number_1, &queue_number_2, &queue_result, &queue_decimal);
		if(sign_flag == 1)
		{
			if(oper == 1 || oper == 2)
		{
			Push_string(&queue_send, "-", 1);
			Push_queue(&queue_send, &queue_result, queue_result.capacity);
			Push_string(&queue_send, newLineStr, strlen(newLineStr));
		}else
		{
			Push_string(&queue_send, "-", 1);
			Push_queue(&queue_send, &queue_result, queue_result.capacity);
			Push_string(&queue_send, ".", 1);
			Push_queue(&queue_send, &queue_decimal, queue_decimal.capacity);
			Push_string(&queue_send, newLineStr, strlen(newLineStr));
		}
	}else
	{
		if(oper == 1 || oper == 2)
		{
			Push_queue(&queue_send, &queue_result, queue_result.capacity);
			Push_string(&queue_send, newLineStr, strlen(newLineStr));
		}else
		{
			Push_queue(&queue_send, &queue_result, queue_result.capacity);
			Push_string(&queue_send, ".", 1);
			Push_queue(&queue_send, &queue_decimal, queue_decimal.capacity);
			Push_string(&queue_send, newLineStr, strlen(newLineStr));
		}
	}
					
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void led_option()
{
	flag = 0;
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Turn_On_Led_Red, strlen(Turn_On_Led_Red));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Turn_On_Led_Green, strlen(Turn_On_Led_Green));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Blink_Led, strlen(Blink_Led));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void led_red_option()
{
	flag = 0;
	STM_EVAL_LEDOn(LED4);
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Running, strlen(Running));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
		
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void led_green_option()
{
	flag = 0;
	STM_EVAL_LEDOn(LED3);
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Running, strlen(Running));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void blink_led_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Counter_Time_Blink, strlen(Counter_Time_Blink));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void blink_led_running()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Running, strlen(Running));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
	counter = decoder(&queue_counter,queue_counter.capacity);
	if(counter >= 0)
	{
		TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM4,ENABLE);
		while(counter >= 0)
		{
			if(Timmer4 == 1)
			{
				STM_EVAL_LEDOn(LED3);
				STM_EVAL_LEDOn(LED4);
				Timmer4 = 0;
			}
			if(Timmer_Led_Off == 1)
			{
				STM_EVAL_LEDOff(LED3);
				STM_EVAL_LEDOff(LED4);
				Timmer_Led_Off = 0;
			}
		}	
		STM_EVAL_LEDOff(LED3);
		STM_EVAL_LEDOff(LED4);
		TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
		TIM_Cmd(TIM4, DISABLE);	
	}
}

void timmer_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Count_Down, strlen(Count_Down));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Stop_Watch, strlen(Stop_Watch));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void input_countdown()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Counter_Down, strlen(Counter_Down));
	
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void input_stopwatch()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, ESC, strlen(ESC));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, Stop_Watch_Input, strlen(Stop_Watch_Input));
				
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}


void error_option()
{
	flag = 0;
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send,error,strlen(error));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
	Push_string(&queue_send, newLineStr, strlen(newLineStr));
					
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void uart_interrupt_my_init()
{
	GPIO_InitTypeDef gpio_init;
	USART_InitTypeDef usart_init;
	NVIC_InitTypeDef nvic_init;

	GPIO_StructInit(&gpio_init);
	USART_StructInit(&usart_init);
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &gpio_init);

	usart_init.USART_BaudRate = 9600;
	usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart_init.USART_Parity = USART_Parity_No;
	usart_init.USART_StopBits = USART_StopBits_1;
	usart_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &usart_init);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	nvic_init.NVIC_IRQChannel = USART3_IRQn;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&nvic_init);

	USART_Cmd(USART3, ENABLE);
}

void TIM4_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;     // frequency = 1000000
  TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  nvic_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_InitStructure.NVIC_IRQChannelSubPriority = 1;
  nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_InitStructure);
	
}
