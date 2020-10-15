#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

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

int gpioSetAlertFunc(unsigned user_gpio, gpioAlertFunc_t f) { 
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

int i2cWriteByteData(unsigned handle, unsigned i2cReg, unsigned bVal) {
    return 0; 
}

int i2cOpen(unsigned i2cBus, unsigned i2cAddr, unsigned i2cFlags) { 
    return 0; 
}

