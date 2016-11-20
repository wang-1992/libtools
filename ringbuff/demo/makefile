CC ?= gcc

INC = -I.
CFLAGS ?= -g -Wall
LIBS = -L. -lringbuff -lpthread

SRC = $(wildcard *.c)
DST = $(patsubst %.c, %.o, $(SRC))

OBJ = test

.c.o:
	$(CC) -c $(INC) $(CFLAGS) $<

$(OBJ):$(DST)
	$(CC) $(DST) -o $(OBJ) $(LIBS)

clean:
	rm -f *.o $(OBJ)
