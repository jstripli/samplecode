#
# Copyright 2010-2012, 2018 - Jeff R. Stripling - All Rights Reserved
#
# A simple makefile for my prime number project.
#
# Usage:
#
#  make - build the target
#  make clean - remove any created files
#  make depend - update header file dependancies
# make cjqq
 
CC = gcc
CFLAGS = -Wall
RM = rm

SRC = getprimes.c main.c
INC = getprints.h

OBJ = $(SRC:.c=.o)

printprimes: $(OBJ)
	$(CC) -o $@ $^

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean depend

clean:
	$(RM) $(OBJ) .depend printprimes
	
depend: .depend

.depend: $(SRC) $(INC)
	$(CC) $(CFLAGS) -MM $^ > $@
	
-include .depend