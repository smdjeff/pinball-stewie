#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#include "portable.h"


int gpioInitialise(void) { 
    printf("gpioInitialise\n"); return 0;
    sleep(1);
}

int gpioSetMode(unsigned gpio, unsigned mode) { 
    return 0; 
}

int gpioSetTimerFunc(unsigned timer, unsigned millis, gpioTimerFunc_t f) {
    return 0; 
}

static void *keyboardInput(void *arg) {
    int i = getchar();
    gpioAlertFunc_t f = arg;
    int gpio = 0;
    int level = 0;
    uint32_t tick = 0;
    f( gpio, level, tick);
    return 0;
}

int gpioSetAlertFunc(unsigned user_gpio, gpioAlertFunc_t f) {
    gpioStartThread( keyboardInput, f );
    return 0; 
}

void* gpioStartThread(gpioThreadFunc_t f, void *userdata) {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, f, userdata); 
    return 0;
}

static int gpioState[41] = {0,};

int gpioWrite(unsigned gpio, unsigned level) {
    printf("gpio[%d] wr %d\n", gpio, level);
    sleep(1);
    gpioState[gpio] = level;
    return 0; 
}

int gpioRead(unsigned gpio) { 
    int level = gpioState[gpio];
    printf("gpio[%d] rd %d\n", gpio, level);
    sleep(1);
    return level;
}

int gpioSetPullUpDown(unsigned gpio, unsigned pud) { 
    return 0; 
}

int gpioPWM(unsigned user_gpio, unsigned dutycycle) { 
    return 0; 
}

int gpioSetPWMfrequency(unsigned gpio, unsigned frequency) {
    return 0;
}

int gpioGetPWMfrequency(unsigned gpio) {
    return 0;
}

int gpioCfgClock(unsigned micros, unsigned peripheral, unsigned source) {
    return 0;
}

int gpioGlitchFilter(unsigned user_gpio, unsigned steady) {
    return 0;
}

int i2cWriteByteData(unsigned id, unsigned i2cReg, unsigned bVal) {
    char data[2];
    data[0] = i2cReg;
    data[1] = bVal;
    return i2cWriteDevice( id, data, sizeof(data) );
}

int i2cWriteDevice(unsigned handle, char *buf, unsigned count) {
    printf("i2c-write[%d] ", handle); for (int i=0;i<count;i++) { printf("%02x ",(uint8_t)buf[i]); } printf("\n");
    sleep(1);
    return 0;
}

int i2cOpen(unsigned i2cBus, unsigned i2cAddr, unsigned i2cFlags) { 
    printf("i2c-open[%d,%d,%d]\n", i2cBus, i2cAddr, i2cFlags);
    sleep(1);
    int handle = rand();
    return handle; 
}

