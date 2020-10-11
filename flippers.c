#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pigpio.h> // http://abyz.me.uk/rpi/pigpio/

// arbitrary connections of the stewie pinball machine's J1 connector 
// to our raspberry pi gpios
#define FLIPPER_SOL_LEFT    10
#define FLIPPER_SOL_RIGHT   11    
#define FLIPPER_SW_LEFT     12
#define FLIPPER_SW_RIGHT    13   

#define SOL_OFF      0
#define SOL_ON       255
#define SOL_ON_MS    50    
#define SOL_HOLD     128

#define FALLING_EDGE 0
#define RISING_EDGE  1
#define LEFT_TIMER   0
#define RIGHT_TIMER  1

static void switchRightCallback(int gpio, int level, uint32_t tick) {
    if ( level == FALLING_EDGE ) {
        gpioPWM( FLIPPER_SOL_RIGHT, SOL_ON/*0-255*/);
        gpioSetTimerFunc( RIGHT_TIMER, SOL_ON_MS/*ms*/, solRightCallback );
    }
    if ( level == RISING_EDGE ) {
        gpioPWM( FLIPPER_SOL_RIGHT, SOL_OFF/*0-255*/);
    }
}

static void switchLeftCallback(int gpio, int level, uint32_t tick) {
    if ( level == FALLING_EDGE ) {
        gpioPWM( FLIPPER_SOL_LEFT, SOL_ON/*0-255*/);
        gpioSetTimerFunc( LEFT_TIMER, SOL_ON_MS/*ms*/, solLeftCallback );
    }
    if ( level == RISING_EDGE ) {
        gpioPWM( FLIPPER_SOL_LEFT, SOL_OFF/*0-255*/);
    }
}

static void solLeftCallback(void) {
    gpioPWM( FLIPPER_SOL_LEFT, PWM_HOLD/*0-255*/);
    gpioSetTimerFunc( LEFT_TIMER, 0, NULL );
}

static void solRightCallback(void) {
    gpioPWM( FLIPPER_SOL_RIGHT, PWM_HOLD/*0-255*/);
    gpioSetTimerFunc( RIGHT_TIMER, 0, NULL );
}

void flippersInit(void) {
    gpioSetMode( FLIPPER_SOL_LEFT, PI_OUTPUT );
    gpioSetMode( FLIPPER_SOL_RIGHT, PI_OUTPUT );
    gpioWrite( FLIPPER_SOL_LEFT, SOL_OFF );
    gpioWrite( FLIPPER_SOL_RIGHT, SOL_OFF );

    gpioSetMode( FLIPPER_SW_LEFT, PI_INPUT );
    gpioSetMode( FLIPPER_SW_RIGHT, PI_INPUT );
    gpioSetPullUpDown(FLIPPER_SW_LEFT, PI_PUD_UP);
    gpioSetPullUpDown(FLIPPER_SW_RIGHT, PI_PUD_UP);
}

void flippersEnable(void) {
    gpioSetAlertFunc( FLIPPER_SW_RIGHT, switchRightCallback );
    gpioSetAlertFunc( FLIPPER_SW_LEFT, switchLeftCallback );
}

void flippersDisable(void) {
    gpioSetAlertFunc( FLIPPER_SW_RIGHT, NULL );
    gpioSetAlertFunc( FLIPPER_SW_LEFT, NULL );
    gpioSetTimerFunc( LEFT_TIMER, 0, NULL );
    gpioSetTimerFunc( RIGHT_TIMER, 0, NULL );
    gpioWrite( FLIPPER_SOL_LEFT, SOL_OFF );
    gpioWrite( FLIPPER_SOL_RIGHT, SOL_OFF );    
}


