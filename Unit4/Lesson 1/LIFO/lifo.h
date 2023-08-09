#ifndef LIFO_H_
#define LIFO_H_


typedef struct
{
	int length ;
	int count ;
	int* base;
	int* head;

}LIFO_Buf_t;



typedef enum
{
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_Null
}LIFO_status;
//APIs

LIFO_status LIFO_Add_item (LIFO_Buf_t* lifo_buff , int item);
LIFO_status LIFO_get_item (LIFO_Buf_t* lifo_buff , int* item);
LIFO_status LIFO_init (LIFO_Buf_t* lifo_buff ,int* item,int size);

#endif