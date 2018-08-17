avrType=atmega328p
avrFreq=16000000UL
programmerType=arduino
programmerDev=/dev/ttyACM0
baud=115200

cflags= -Wall -Os -DF_CPU=$(avrFreq) -mmcu=$(avrType)
objects=$(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: flash clean

all: main.hex

%.o: %.c
	avr-gcc $(cflags) -c $< -o $@

main.elf: $(objects)
	avr-gcc $(cflags) -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

flash: main.hex
	avrdude -p$(avrType) -c$(programmerType) -P$(programmerDev) -b$(baud) -v -D -U flash:w:$<

clean:
	rm -f main.hex main.elf $(objects)
