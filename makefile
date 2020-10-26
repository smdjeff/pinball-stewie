UNAME := $(shell uname -n)
ifeq ($(UNAME),raspberrypi)
LDFLAGS += -pthread -lpigpio -lrt
CFLAGS += -DRASPBERRY
else
ADD_OBJS = linux/portable.o
LDFLAGS += -pthread
endif

src = $(wildcard *.c)
obj = $(src:.c=.o) $(ADD_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I. -o $@ -c $<

stewie: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) stewie



