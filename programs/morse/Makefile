CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

###############################
# make all build files
###############################
all: MorseEncoder test

###############################
# main executables
###############################
MorseEncoder: MorseEncoder.o morse_encoders.o

test: test.o morse_encoders.o

###############################
# object files
###############################
MorseEncoder.o: morse_base.h

morse_encoders.o: morse_base.h morse_encoders.h

test.o: morse_base.h morse_encoders.h

###############################
clean:
	rm -f $(wildcard *.o)
	rm -f $(wildcard *.run)
	rm -f MorseEncoder
	rm -rf temp
