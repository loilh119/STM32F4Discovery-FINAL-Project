#include "main.h"
	
	extern int i ;
	extern uint8_t mode;
	extern uint8_t id;
	extern uint8_t past_id;
	extern uint8_t oper;
	extern uint8_t sign_flag;
	extern uint8_t mode_counter;
	extern int counter;
	extern int sign_number_1;
	extern int sign_number_2;
	extern int result_decode;
	extern double num1;
	extern double num2;
	extern double result;
	
	void counter_down(void);
	void uart_interrupt_my_init(void);
	void blink_led(void);
	void operation(const uint8_t oper, struct queue_t* queue_num_1, struct queue_t* queue_num_2, struct queue_t* queue_result, struct queue_t* queue_decimal);
	void decimal_part(struct queue_t* queue, double num);
	void reverse_queue(struct queue_t* queue, const uint8_t length);
	void remove_zero(struct queue_t* queue);
	void encoder(struct queue_t* queue, int number);
	int decoder(struct queue_t* queue, const uint8_t length);
	
