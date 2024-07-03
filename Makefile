# Makefile to build and flash avrtft.
#
# Simplified version from: https://github.com/hexagon5un/AVR-Programming

MCU = atmega328p
F_CPU = 16000000
BAUD = 38400
PROGRAMMER_TYPE = avrispmkII
PROGRAMMER_ARGS = 

# These settings should be enough to get all currently supported
# drivers to work (they are very similar):
# - ST7735R
# - ST7789
# - ILI9341
# and also, for larger TTL displays:
# - RA8875

# Set to 1 for RA8875, 0 for other drivers
DRIVER = 1

# Display dimensions
DISPLAY_WIDTH = 800
DISPLAY_HEIGHT = 480
# 1 = BGR, 0 = RGB
BGR = 1
# Invert color
INVERT = 0
# Flip image
HFLIP = 0
VFLIP = 0

MAIN = avrtft.c
SRC = bitmaps.c bmp.c cmd.c colorspace.c display.c emojis.c font.c \
      hack.c i2c.c paint.c ra8875.c sdcard.c spi.c tft.c touch.c usart.c

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL -DBAUD=$(BAUD)
CFLAGS += -DDRIVER=$(DRIVER)
CFLAGS += -DDISPLAY_WIDTH=$(DISPLAY_WIDTH) -DDISPLAY_HEIGHT=$(DISPLAY_HEIGHT)
CFLAGS += -DINVERT=$(INVERT) -DBGR=$(BGR) -DHFLIP=$(HFLIP) -DVFLIP=$(VFLIP)
CFLAGS += -O2 -I.
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
CFLAGS += -Wall -Wstrict-prototypes
CFLAGS += -g -ggdb
CFLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections -mrelax
CFLAGS += -std=gnu99
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105523
# CFLAGS += --param=min-pagesize=0

TARGET = $(strip $(basename $(MAIN)))
SRC += $(TARGET).c

OBJ = $(SRC:.c=.o) 
OBJ = $(SRC:.S=.o)
	
$(TARGET).elf: bitmaps.h bmp.h cmd.h colorspace.h display.h emojis.h font.h \
	       hack.h i2c.h paint.h ra8875.h sdcard.h spi.h tft.h touch.h \
	       pins.h types.h usart.h utils.h Makefile

all: $(TARGET).hex

%.hex: %.elf
	$(OBJCOPY) -R .eeprom -O ihex $< $@

%.elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) --output $@ 

disasm: $(TARGET).lst

eeprom: $(TARGET).eeprom

%.lst: %.elf
	$(OBJDUMP) -S $< > $@
 
size:  $(TARGET).elf
	$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

flash: $(TARGET).hex 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<
