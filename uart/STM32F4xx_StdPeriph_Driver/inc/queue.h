#include "main.h"

	extern struct queue_t queue_send;
	extern struct queue_t queue_receive;
	extern struct queue_t queue_number_1;
	extern struct queue_t queue_number_2;
	extern struct queue_t queue_result;
  extern struct queue_t queue_decimal;
	extern struct queue_t queue_counter;
		
	void Push_queue(struct queue_t * queue, struct queue_t * queue1, const uint8_t length);
	void Push_string(struct queue_t* queue, const char * string, const uint8_t length);
	void Queue_Init(struct queue_t* queue);
	void Queue_Push(struct queue_t* queue, const uint8_t data);
	uint8_t Queue_Pop(struct queue_t* queue);
	uint8_t Queue_Peek(struct queue_t* queue);
	int Queue_Is_Empty(const struct queue_t* queue);
	int Queue_Is_Full(const struct queue_t* queue);

