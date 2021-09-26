#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "../portable.h"
    
int usleep(useconds_t usec) {
    sleep_us(usec);
}

int gpioInitialise(void) { 
    return 0; 
}

int gpioSetMode(unsigned gpio, unsigned mode) { 
    return 0; 
}

int gpioSetTimerFunc(unsigned timer, unsigned millis, gpioTimerFunc_t f) {
    return 0; 
}

int gpioSetAlertFunc(unsigned user_gpio, gpioAlertFunc_t f) {
    return 0; 
}

void* gpioStartThread(gpioThreadFunc_t f, void *userdata) {
    return 0;
}

int gpioWrite(unsigned gpio, unsigned level) {
    return 0; 
}

int gpioRead(unsigned gpio) { 
    return 0;
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

int i2cWriteByteData(unsigned handle, unsigned i2cReg, unsigned bVal) {
    return 0; 
}

int i2cOpen(unsigned i2cBus, unsigned i2cAddr, unsigned i2cFlags) { 
    return 0; 
}

