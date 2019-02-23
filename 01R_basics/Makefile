# Please write your make-skript here
#HEADER = $(SOURCE:%.c=%.h) #what happened if there is no hello.h for hello.c
			    #for compiling we don't need header files
SOURCE_SILLUTILS = test.c shellutils.c
OBJ_SILLUTILS = $(SOURCE_SILLUTILS:%.c=%.o)
HEADER = $(SOURCE:%.c=%.h)
CC = clang
CFLAGS = -std=c11 -pedantic -Wall -Wextra
.PHONY: all clean
#we build only the target helloworld, it has no dependencies
all: helloworld shellutilstest
helloworld: hello.o
	@echo Linke Program: $@
	$(CC) -o $@ $+
shellutilstest: $(OBJ_SILLUTILS)
	@echo Linke Program: $@
	$(CC) -o $@ $+
#here is the implicit rule,
#if we don't have these command, makefile can still work
%.o: %.c %.h
	@echo Kompiliere Datei: $< #what is $< here 
	$(CC) $(CFLAGS) -c -g -O0 $<
clean:
	rm -f *.o 
	rm -f shellutilstest
	rm -f helloworld #remove all documents with end .o and all targets
