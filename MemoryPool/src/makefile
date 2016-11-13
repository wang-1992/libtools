CC=gcc
AR=ar

INCS=-I. -I../../include -I .
LIBOBJS=mem_pool.o
FLAG= -g -W


%.o:%.c
	$(CC) $(FLAG) -c $(INCS) $<

all:libmempool

libmempool:$(LIBOBJS)
	$(AR) -r $@.a $(LIBOBJS)
	cp $@.a ../../libs
	cp mem_pool.h ../../include
	
clean:
	rm -rf *.o *.a
	rm -rf ../../libs/libmempool.a
	rm -rf ../../include/mem_pool.h
.PHONY: all clean
