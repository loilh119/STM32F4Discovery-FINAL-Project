#include <queue.h>

	// Day data vao vi tri cuoi cung cua queue
	void Queue_Push(struct queue_t* queue, uint8_t data){
		queue->array[queue->capacity] = data;
		queue->capacity += 1;
	}
	
	// Tra ve phan ru dau tien, roi xoa khoi queue
	uint8_t Queue_Pop(struct queue_t* queue){
		uint8_t result;
		int i;
		result = queue->array[0];
		for ( i = 0; i < queue->capacity ; i++){
			queue->array[i] = queue->array[i+1];
		}
		queue->capacity -= 1;
		return result;
	}
	
	// Xem gia tri dau tien cua queue
	uint8_t Queue_Peek(struct queue_t* queue){
		return queue->array[0];
	}
	
	// Kiem tra xem queue co rong hay khong
	int Queue_Is_Empty(const struct queue_t* queue){
		if(queue->capacity == 0)
			return 1;
		return  0;
	}
	
	// Kiem tra xem queue co day hay khong
	int Queue_Is_Full(const struct queue_t* queue){
		if(queue->capacity == MAX_QUEUE)
			return 1;
		return  0;
	}

	//dua du lieu tu chuoi nay sang chuoi khac
	void Push_queue(struct queue_t * queue, struct queue_t * queue1, const uint8_t length)
	{
		int i;
		for(i = 0; i < length; i++)
		{
			Queue_Push(queue, Queue_Pop(queue1) + 0x30);		
		}
	}

	//day du lieu tu char* vao chuoi
	void Push_string(struct queue_t * queue, const char * string, const uint8_t length)
	{
		int i;
		for(i = 0; i < length; i++)
		{
			Queue_Push(queue, string[i]);
		}
	}
	
	