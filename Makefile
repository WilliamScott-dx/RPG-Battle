# File:   Makefile
# Author: William Scott
# Date:   13 Sep 2015
# Descr:  Makefile for RPGBattle

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -std=c99 -Wextra -g -I../../drivers -I../../fonts -I../../drivers/avr -I../../utils
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
main.o: main.c rpgbattle.h gfx_utils.h text.h ../../drivers/avr/ir_uart.h ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../drivers/button.h ../../drivers/display.h ../../drivers/navswitch.h  ../../utils/pacer.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) -std=c99 $< -o $@

attack.o: attack.c attack.h text.h hero.h
	$(CC) -c $(CFLAGS) $< -o $@

rpgbattle.o: rpgbattle.c rpgbattle.h hero.h text.h rpgbattle_utils.h gfx_utils.h ../../drivers/avr/delay.h ../../drivers/avr/ir_uart.h ../../drivers/avr/system.h ../../drivers/button.h ../../drivers/display.h ../../drivers/navswitch.h ../../drivers/button.h  ../../utils/pacer.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

rpgbattle_utils.o: rpgbattle_utils.c rpgbattle_utils.h
	$(CC) -c $(CFLAGS) $< -o $@

gfx_utils.o: gfx_utils.c gfx_utils.h text.h ../../fonts/font3x5_1.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

hero.o: hero.c hero.h attack.h text.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
game.out: rpgbattle.o main.o hero.o attack.o led.o gfx_utils.o rpgbattle_utils.o ir_uart.o pio.o prescale.o system.o button.o timer.o timer0.o usart1.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start

