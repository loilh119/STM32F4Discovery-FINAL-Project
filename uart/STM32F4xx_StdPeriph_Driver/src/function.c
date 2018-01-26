#include "function.h"

// ham tinh toan
void operation(const uint8_t oper, struct queue_t* queue_num_1, struct queue_t* queue_num_2, struct queue_t* queue_result, struct queue_t* queue_decimal)
{
	int n1, n2;
	int temp1,temp2;
	double result;
	switch(oper)
	{
		case 1:
			n1 = decoder(&queue_number_1, queue_number_1.capacity);
			n2 = decoder(&queue_number_2, queue_number_2.capacity);
			temp1 = n1 * sign_number_1;
			temp2 = n2 * sign_number_2;
			sign_number_1 = 1;
			sign_number_2 = 1;
			result = temp1 + temp2;
			if (result < 0)
			{
				sign_flag = 1;
				result *= -1;
			}
			else
			{
				sign_flag = 0;
			}
			encoder(queue_result, (int)result);
			remove_zero(queue_result);
			reverse_queue(queue_result, queue_result->capacity);
			break;
		
		case 2:
			n1 = decoder(&queue_number_1, queue_number_1.capacity);
			n2 = decoder(&queue_number_2, queue_number_2.capacity);
			temp1 = n1 * sign_number_1;
			temp2 = n2 * sign_number_2;
			sign_number_1 = 1;
			sign_number_2 = 1;
			result = temp1 - temp2;
			if(result < 0 )
			{
				sign_flag = 1;
				result *= -1;
			}
			else
			{
				sign_flag = 0;
			}
			encoder(queue_result, (int)result);
			remove_zero(queue_result);
			reverse_queue(queue_result, queue_result->capacity);
			break;
			
		case 3:
			n1 = decoder(&queue_number_1, queue_number_1.capacity);
			n2 = decoder(&queue_number_2, queue_number_2.capacity);
			temp1 = n1 * sign_number_1;
			temp2 = n2 * sign_number_2;
			sign_number_1 = 1;
			sign_number_2 = 1;
			result = temp1 * temp2;
			if(result < 0 )
			{
				sign_flag = 1;
				result *= -1;
			}
			else
			{
				sign_flag = 0;
			}
			encoder(queue_result, (int)result);
			remove_zero(queue_result);
			reverse_queue(queue_result, queue_result->capacity);
			break;
			
		case 4:
			n1 = decoder(&queue_number_1, queue_number_1.capacity);
			n2 = decoder(&queue_number_2, queue_number_2.capacity);
			temp1 = n1 * sign_number_1;
			temp2 = n2 * sign_number_2;
			sign_number_1 = 1;
			sign_number_2 = 1;
			result = (double)temp1 / (double)temp2;
			if(result < 0 )
			{
				sign_flag = 1;
				result *= -1;
			}
			else
			{
				sign_flag = 0;
			}
			encoder(queue_result, (int)result);
			remove_zero(queue_result);
			reverse_queue(queue_result, queue_result->capacity);
			decimal_part(queue_decimal,result);
			break;
			
		case 5:
			n1 = decoder(&queue_number_1, queue_number_1.capacity);
			n2 = decoder(&queue_number_2, queue_number_2.capacity);
			temp1 = n1 * sign_number_1;
			temp2 = n2 * sign_number_2;
			sign_number_1 = 1;
			sign_number_2 = 1;
			result = sqrt((double)(temp1*temp1 + temp2*temp2));
			if(result < 0 )
			{
				sign_flag = 1;
				result *= -1;
			}else
			{
				sign_flag = 0;
			}
			encoder(queue_result, (int)result);
			remove_zero(queue_result);
			reverse_queue(queue_result, queue_result->capacity);
			decimal_part(queue_decimal,result);
			break;
			
		default:
			id = 30;
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			break;
	}
}

// Khoi tao queue
void Queue_Init(struct queue_t* queue){
	int i;
	queue = 0;
	for(i = 0; i < MAX_QUEUE; i++)
	{
		queue->array[i] = 0;
	}
}


//chuyen tu chuoi thanh int 
int decoder(struct queue_t* queue, const uint8_t length)
{
	int i;
	result_decode = 0;
	for (i = 0; i < length; i++)
	{
		result_decode = result_decode*10 + Queue_Pop(queue);
	}
	return result_decode;
}


//chuyen int vao chuoi
void encoder(struct queue_t* queue, int number)
{
	int i;
	for (i = 0; i < MAX_QUEUE; i++)
	{
		num1 = number % 10;
		Queue_Push(queue,num1);
		number = number / 10;
	}
}

//lay phan thap phan cua so
void decimal_part(struct queue_t* queue, double num)
{
	int i;
	double m = num - (int)num;
	for(i = 0; i < 2; i++)
	{
		m *= 10;
		Queue_Push(queue,(int)m);
		m -= (int)m;
	}
}

//loai bo tat ca so 0 cuoi chuoi
void remove_zero(struct queue_t* queue)
{
	for(i = 0; i < MAX_QUEUE; i++)
	{
		if(i == MAX_QUEUE - 1)
		{
			return;
		}else if(queue->array[MAX_QUEUE - i -1] == 0)
		{
			queue->capacity --;
		}else if(queue->array[MAX_QUEUE - i -1] != 0)
		{
			return;
		} 
	}
}


//dao chuoi
void reverse_queue(struct queue_t* queue, const uint8_t length)
{
	for(i = 0 ; i < length/2; i++)
	{
		uint8_t temp;
		temp = queue->array[i];
		queue->array[i] = queue->array[length - i - 1];
		queue->array[length - i - 1] = temp;
	}
}	