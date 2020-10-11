stewie: main.c stewie-lamps.c
	gcc -Wall -pthread -o stewie stewie-lamps.c main.c -lpigpio -lrt -I.
