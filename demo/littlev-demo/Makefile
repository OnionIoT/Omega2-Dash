#
# Makefile
#
CC ?= gcc
LVGL_DIR ?= ${shell pwd}
CFLAGS ?= -Wall -Wshadow -Wundef -Wmaybe-uninitialized -O3 -g0 -I$(LVGL_DIR)/
# LDFLAGS ?= -lSDL2 -lm
LDFLAGS ?= -lm
BUILDDIR := build
BINDIR := bin
BIN = $(BINDIR)/demo


#Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/lv_examples/lv_examples.mk

#include 
INC := -I . -I lvgl -I lv_drivers -I lv_examples 

#CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
# AOBJS = $(patsubst %,%,$(ASRCS:.S=$(OBJEXT)))

#reference
# SOURCES := $(shell find . -type f -iname "*.$(SRCEXT)" )
# OBJECTS := $(patsubst %,%,$(SOURCES:.$(SRCEXT)=.o))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES

all: default
%.o: %.c
	# reference from previous littlev project
	#$(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "CC $<"
    
default: $(AOBJS) $(COBJS) $(MAINOBJ)
	@mkdir -p $(BINDIR)
	$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)
