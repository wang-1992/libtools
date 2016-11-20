CC=gcc
AR=ar

INCS=-I. -I../../include -I .
LIBOBJS=ringbuff.o
FLAG= -g -W


%.o:%.c
	$(CC) $(FLAG) -c $(INCS) $<

all:libringbuff

libringbuff:$(LIBOBJS)
	$(AR) -r $@.a $(LIBOBJS)
	cp $@.a ../../libs
	cp ringbuff.h ../../include
	cp $@.a ../demo
	cp ringbuff.h ../demo
	
clean:
	rm -rf *.o *.a
	rm -rf ../../libs/libringbuff.a
	rm -rf ../../include/ringbuff.h
	rm -rf ../demo/libringbuff.a
	rm -rf ../demo/ringbuff.h
.PHONY: all clean
