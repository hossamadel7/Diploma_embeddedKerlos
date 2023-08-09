#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"
#define width 5


int buffer1[width];

void main()
{

    int temp = 0;

    LIFO_Buf_t UART_BUFF, I2C_BUFF;

    LIFO_init(&UART_BUFF, buffer1, width);

    int *Buffer2 = (int*)malloc(5 * sizeof(int));

    LIFO_init(&I2C_BUFF, Buffer2, 5);
    int i;
    for ( i = 0; i < 5; i++)
    {
        if (LIFO_Add_item(&UART_BUFF,i) == LIFO_no_error)
            printf("UART_LIFO add : %d \n", i);
    }

    for (i = 0; i < 5; i++)
    {
        if (LIFO_get_item(&UART_BUFF, &temp) == LIFO_no_error)
            printf("UART_LIFO get : %d \n", temp);
    }

}