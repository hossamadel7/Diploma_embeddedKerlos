/*
 * IncFile1.h
 *
 * Created: 9/7/2023 5:17:08 PM
 *  Author: KH
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define baseIO 0x20
#define MCUCR *(volatile unsigned char *) (baseIO + 0x35)
#define MCUCSR *(volatile unsigned char *) (baseIO + 0x34)
#define GICR *(volatile unsigned char *) (baseIO + 0x3B)
#define PORTD *(volatile unsigned char *) (baseIO + 0x12)
#define DDRD *(volatile unsigned char *) (baseIO + 0x11)

#define SET_bit(ADDRESS, BIT) ADDRESS |= (1<<BIT)
#define RESET_bit(ADDRESS, BIT) ADDRESS &= ~(1<<BIT)



#endif /* INCFILE1_H_ */