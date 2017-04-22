CC=gcc
AR=ar

INCS=-I.
LIBOBJS=write_pcap.o
FLAG= -g -W


%.o:%.c
	$(CC) $(FLAG) -c $(INCS) $<

all:libwrite_pcap

libwrite_pcap:$(LIBOBJS)
	$(AR) -r $@.a $(LIBOBJS)
	cp $@.a ../../libs
	cp write_pcap.h ../../include
	
clean:
	rm -rf *.o *.a
	rm -rf ../../libs/libwrite_pcap.a
	rm -rf ../../include/write_pcap.h
.PHONY: all clean
