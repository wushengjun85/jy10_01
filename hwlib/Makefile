EXEC	= ./devlib.so
OBJS    = devlib.o

CROSS	= arm-linux-gnueabihf-
CC	= $(CROSS)gcc 
STRIP	= $(CROSS)strip
CFLAGS	= -fpic -shared -Wall -g -O2

all:  clean $(EXEC)

$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread
	$(STRIP) $@

clean:
	-rm -f $(EXEC) *.o
