#**********************************
#      Makefile for atmega 238p
#**********************************

AVR_TYPE =			atmega328p
AVR_FREQ =			16000000UL
PROGRAMMER_TYPE =	arduino
PROGRAMMER_DEV =	/dev/ttyACM0
BAUD =				115200

SRC =				ring_buf.c uart.c get_temp.c main.c
OBJ =				$(SRS:.c=.o)

CC =				avr-gcc
CFLAGS =			-Wall -Os -DF_CPU=$(AVR_FREQ) -mmcu=$(AVR_TYPE)

AVRDUDE = 			avrdude -v -p$(AVR_TYPE) -c$(PROGRAMMER_TYPE) -P$(PROGRAMMER_DEV) -b$(BAUD)
TRANSLATE_OBJ =		avr-objcopy -j .text -j .data -O ihex
LST_SECTION_SIZE =	avr-size --format=avr --mcu=$(AVR_TYPE)

ELF =				main.elf
MACHINE_CODE =		main.hex

all: $(MACHINE_CODE)

$(MACHINE_CODE): $(OBJ)
	@$(CC) $(CFLAGS) $(SRC) -o $(ELF) $^
	@$(TRANSLATE_OBJ) $(ELF) $@
	@$(LST_SECTION_SIZE) $@

install: $(MACHINE_CODE) 
	@$(AVRDUDE) -D -V -U flash:w:$^:i

clean:
	@rm -f $(MACHINE_CODE) $(ELF) $(OBJ)

re: clean all install

.PHONY: install clean re 