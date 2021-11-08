UNAME := $(shell uname -n)
ifeq ($(UNAME),raspberrypi)
LDFLAGS += -pthread -lpigpio -lrt -lzmq
CFLAGS += -DRASPBERRY -O3
else
ADD_OBJS = linux/portable.o
LDFLAGS += -pthread -lzmq
CFLAGS+=-ggdb -Wall -Wfatal-errors -Wno-unused-variable -Wno-unused-function 
SANITIZERS=-fsanitize=address -fno-omit-frame-pointer -Wno-format-security
#SANITIZERS+=-fsanitize=leak 
#SANITIZERS+=-fsanitize=memory 
SANITIZERS+=-fsanitize=undefined 
CFLAGS+=$(SANITIZERS)
LDFLAGS+=$(SANITIZERS)
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



