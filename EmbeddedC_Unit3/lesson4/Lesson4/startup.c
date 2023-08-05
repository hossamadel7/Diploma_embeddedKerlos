//Eng.Hossam Adel

#include <stdint.h>
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;

extern int main();

static unsigned long Stack_top[256] ;

void Rest_handler (void);
void Default_handler(void)
{
	Rest_handler();
}

void NMI_handler(void) __attribute__ ((weak, alias ("Default_handler")));;
void H_fault_handler(void) __attribute__ ((weak, alias ("Default_handler")));;
void MM_fault_handler(void) __attribute__ ((weak, alias ("Default_handler")));;
void Bus_fault(void) __attribute__ ((weak, alias ("Default_handler")));;
void Usage_fault_handler(void) __attribute__ ((weak, alias ("Default_handler")));;

void (* const g_ptr_FnVectors[]) () __attribute__((section(".vectors"))) =
{
  (void (*)()) ((unsigned long)Stack_top+sizeof(Stack_top)),
  &Rest_handler,
  &NMI_handler,
  &H_fault_handler,
  &MM_fault_handler,
  &Bus_fault,
  &Usage_fault_handler
};

/*
uint32_t vectors[] __attribute__((section(".vectors")))  ={
  (uint32_t) (&Stack_top[0]+sizeof(Stack_top)),
  (uint32_t) &Rest_handler,
  (uint32_t) &NMI_handler,
  (uint32_t) &H_fault_handler,
  (uint32_t) &MM_fault_handler,
  (uint32_t) &Bus_fault,
  (uint32_t) &Usage_fault_handler,
};*/

void Rest_handler(void)
{

unsigned int DATA_SIZE= (unsigned char *)&_E_DATA - (unsigned char *)&_S_DATA;
unsigned char *P_SRC=(unsigned char *)&_E_text;
unsigned char *P_dst=(unsigned char *)&_S_DATA;

for(int i=0;i<DATA_SIZE;i++)
  {

    *((unsigned char*)P_dst++)=*((unsigned char*)P_SRC++);

  } 


unsigned int bss_size=(unsigned char *)&_E_bss - (unsigned  char *)&_S_bss ;
P_dst=(unsigned char *)&_S_bss;

for(int i=0;i<bss_size;i++)
  {

    *((unsigned char*)P_dst++)=(unsigned char)0;

  } 

	main();
}
