RASPBERRYPI = $(shell ./onapi)

ifeq ($(RASPBERRYPI),Pi)
all: main.c stewie-lamps.c mcp23017.c flippers.c
	gcc -Wall -pthread -DRASPBERRYPI-o stewie main.c stewie-lamps.c mcp23017.c flippers.c -lpigpio -lrt -I.
else
all: main.c stewie-lamps.c mcp23017.c flippers.c
	gcc -Wall -pthread -o stewie main.c stewie-lamps.c mcp23017.c flippers.c portable_stdio.c -I.
endif

