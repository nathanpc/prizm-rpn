# Makefile
# Casio Prizm project Makefile.
#
# Author: Nathan Campos <nathan@innovewokshop.com>

PROJECT = rpn
NAME = RPN

# Executables.
CC = sh3eb-elf-gcc
MKG3A = mkg3a
RM = rm -r
MKDIR = mkdir -p
CP = cp -f
UDISKSCTL = udisksctl

# Paths.
SRCDIR = src
BUILDDIR = build
LIBFXCGPATH = /opt/prizm-sdk/libfxcg
BASEDEVICEPATH = /dev/sda
DEVICEPATH = $(BASEDEVICEPATH)1
MEDIAPATH = /media/$(shell whoami)/disk

# Files.
SOURCES = $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o))
ELFBIN = $(BUILDDIR)/$(PROJECT).bin
TARGET = $(ELFBIN:.bin=.g3a)

# Flags.
CFLAGS = -std=c99 -mb -ffreestanding -flto -Os -mhitachi -Wall -Wextra -I$(LIBFXCGPATH)/include 
LDFLAGS = -Os -L$(LIBFXCGPATH)/lib -ffreestanding -flto -nostartfiles -T$(LIBFXCGPATH)/toolchain/prizm.x -Wl,-static -Wl,-gc-sections
LIBS = -lfxcg -lc -lgcc
MKG3AFLAGS = -i uns:icon_unselected.bmp -i sel:icon_selected.bmp -n basic:$(NAME) -n $(NAME)


.PHONY: install clean temp_dirs

all: clean temp_dirs $(TARGET)

$(ELFBIN): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@

$(TARGET): $(ELFBIN)
	$(MKG3A) $(MKG3AFLAGS) $< $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: temp_dirs $(TARGET)
	$(UDISKSCTL) mount -b $(DEVICEPATH)
	$(CP) $(TARGET) $(MEDIAPATH)
	$(UDISKSCTL) unmount -b $(DEVICEPATH)
	$(UDISKSCTL) power-off -b $(BASEDEVICEPATH)

clean:
	-$(RM) $(BUILDDIR)

temp_dirs:
	$(MKDIR) $(BUILDDIR)

