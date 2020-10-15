#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"

#include "flippers.h"

    
#define SOLENOID_OFF      0
#define SOLENOID_ON       255
#define SOLENOID_ON_MS    50    
#define SOLENOID_HOLD     128

#define FALLING_EDGE      0
#define RISING_EDGE       1
#define LEFT_TIMER        0
#define RIGHT_TIMER       1

static void solLeftCallback(void) {
    gpioPWM( SOLENOID_FLIPPER_LEFT, SOLENOID_HOLD/*0-255*/);
    gpioSetTimerFunc( LEFT_TIMER, 0, NULL );
}

static void solRightCallback(void) {
    gpioPWM( SOLENOID_FLIPPER_RIGHT, SOLENOID_HOLD/*0-255*/);
    gpioSetTimerFunc( RIGHT_TIMER, 0, NULL );
}

static void switchRightCallback(int gpio, int level, uint32_t tick) {
    if ( level == FALLING_EDGE ) {
        gpioPWM( SOLENOID_FLIPPER_RIGHT, SOLENOID_ON/*0-255*/);
        gpioSetTimerFunc( RIGHT_TIMER, SOLENOID_ON_MS/*ms*/, solRightCallback );
    }
    if ( level == RISING_EDGE ) {
        gpioPWM( SOLENOID_FLIPPER_RIGHT, SOLENOID_OFF/*0-255*/);
    }
}

static void switchLeftCallback(int gpio, int level, uint32_t tick) {
    if ( level == FALLING_EDGE ) {
        gpioPWM( SOLENOID_FLIPPER_LEFT, SOLENOID_ON/*0-255*/);
        gpioSetTimerFunc( LEFT_TIMER, SOLENOID_ON_MS/*ms*/, solLeftCallback );
    }
    if ( level == RISING_EDGE ) {
        gpioPWM( SOLENOID_FLIPPER_LEFT, SOLENOID_OFF/*0-255*/);
    }
}

void flippersInit(void) {
    printf("flippersInit()\n");
    gpioSetMode( SOLENOID_FLIPPER_LEFT, PI_OUTPUT );
    gpioSetMode( SOLENOID_FLIPPER_RIGHT, PI_OUTPUT );
    gpioWrite( SOLENOID_FLIPPER_LEFT, SOLENOID_OFF );
    gpioWrite( SOLENOID_FLIPPER_RIGHT, SOLENOID_OFF );

    gpioSetMode( SWITCH_FLIPPER_LEFT, PI_INPUT );
    gpioSetMode( SWITCH_FLIPPER_RIGHT, PI_INPUT );
    gpioSetPullUpDown( SWITCH_FLIPPER_LEFT, PI_PUD_UP );
    gpioSetPullUpDown( SWITCH_FLIPPER_RIGHT, PI_PUD_UP );
}

void flippersEnable(void) {
    printf("flippersEnable()\n");
    gpioSetAlertFunc( SWITCH_FLIPPER_RIGHT, switchRightCallback );
    gpioSetAlertFunc( SWITCH_FLIPPER_LEFT, switchLeftCallback );
}

void flippersDisable(void) {
    printf("flippersDisable()\n");
    gpioSetAlertFunc( SWITCH_FLIPPER_RIGHT, NULL );
    gpioSetAlertFunc( SWITCH_FLIPPER_LEFT, NULL );
    gpioSetTimerFunc( LEFT_TIMER, 0, NULL );
    gpioSetTimerFunc( RIGHT_TIMER, 0, NULL );
    gpioWrite( SOLENOID_FLIPPER_LEFT, SOLENOID_OFF );
    gpioWrite( SOLENOID_FLIPPER_RIGHT,SOLENOID_OFF );    
}


