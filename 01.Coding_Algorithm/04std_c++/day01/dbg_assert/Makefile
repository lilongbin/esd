#================================================================
#   Copyright (C) 2017 * Ltd. All rights reserved.
#   
#   File name   : Makefile
#   Author      : longbin
#   Created date: 2017-10-23 00:49:31
#   Description : 
#
#================================================================

OBJS=app 
# SRC=debug.c
# CC=gcc
# CFLAGS=
SRC=debug.cpp
CC=g++
CFLAGS=-std=c++11

NM=nm
SYMBOL=symbol.txt
CALLSTACK=callstack.txt
MAPS=mem-map.txt

DEBUGON = 
ifeq ($(DEBUGON),)
    DEBUG = @echo >/dev/null
else
    DEBUG = @echo
endif

all: OBJS SYMBOL CALLSTACK MAPS
OBJS:
	$(CC) $(CFLAGS) -o $(OBJS) $(SRC)
	$(DEBUG) "DEBUG: $(OBJS)"
	$(warning "debug test")

SYMBOL:
	$(DEBUG) "DEBUG: symbol"
	$(NM) -n $(OBJS) > $(SYMBOL)

CALLSTACK:
	$(DEBUG) "DEBUG: callstack"
	./$(OBJS) > $(CALLSTACK)

MAPS:
	$(DEBUG) "DEBUG: callstack"

.PHONY: clean
clean:
	-rm -v ${OBJS} $(CALLSTACK) $(MAPS) symbol*.txt

