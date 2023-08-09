#include "lifo.h"
#include <stdio.h>
#include <stdlib.h>

LIFO_status LIFO_Add_item (LIFO_Buf_t* lifo_buff , int item)
{
	if(!lifo_buff || !(lifo_buff->head) || !(lifo_buff->base)) return LIFO_Null;
	if(lifo_buff->count==lifo_buff->length) return LIFO_full;
	else 
	{
		*(lifo_buff->head)=item;
		lifo_buff->head++;
		lifo_buff->count++;
	}
	return LIFO_no_error;
}

LIFO_status LIFO_get_item (LIFO_Buf_t* lifo_buff , int* item)
{
	if(!lifo_buff || !lifo_buff->head || !lifo_buff->base) return LIFO_Null;
	if(lifo_buff->count==0) return LIFO_empty;
	lifo_buff->head--;
	
	lifo_buff->count--;
	*item=*(lifo_buff->head);
	return LIFO_no_error;
}

LIFO_status LIFO_init (LIFO_Buf_t* lifo_buff , int* buf,int size)
{
	if(buf == NULL) return LIFO_Null;
	lifo_buff->base=buf;
	lifo_buff->head=buf;
	lifo_buff->length=size;
	lifo_buff->count =0;
	return LIFO_no_error;
}
