	
CC= arm-none-eabi-gcc
obj= arm-none-eabi-objdump.exe
MACH = cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -o0
ld = arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -T stm32f407.ld -nostartfiles -nodefaultlibs -o executable.elf main.o startup.o
all: main.o startup.o executable binary map

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

startup.o: startup.c
	$(CC) $(CFLAGS) startup.c -o startup.o

executable:
	$(ld)

binary:
	arm-none-eabi-objcopy -O binary executable.elf executable.bin

map:
	arm-none-eabi-gcc -nostdlib -T stm32f407.ld -Wl,"-Map=final.map" -o executable.elf main.o startup.o

clean:
	rm *.o *.elf *.bin *.map
#To see the memory layout of .o file
obj:
	$(obj) -h main.o
	$(obj) -D main.o
