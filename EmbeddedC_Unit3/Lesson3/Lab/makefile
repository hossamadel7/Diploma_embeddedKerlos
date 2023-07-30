#@copyright: Hossssssss
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
Project_name=Lesson3_lab

all:$(Project_name).hex
	@echo "Build 100%"

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
#startup.o: startup.s
#	$(CC)as.exe  $(CFLAGS) $< -o $@
$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linkerscript.ld $(LIBS) $(OBJ) $(AsOBJ) -o $(Project_name).elf -Map=mapfile.map
$(Project_name).hex: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@


clean_all:
	rm *.o *.elf *.bin *.hex
	@echo "Everthin clean"

