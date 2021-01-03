#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include "portable.h"

#include "flippers.h"

#define SOLENOID_ON       1
#define SOLENOID_OFF      0
#define SOLENOID_ON_MS    200
#define SOLENOID_HOLD     0.80

static void holdLeftCallback(void) {
    printf("flipper left hold\n");
    gpioPWM( SOLENOID_FLIPPER_LEFT, 255.0 * SOLENOID_HOLD );
    assert( gpioCancelTimer( TIMER_LEFT_FLIP ) == 0 );
}

static void holdRightCallback(void) {
    printf("flipper right hold\n");
    gpioPWM( SOLENOID_FLIPPER_RIGHT, 255.0 * SOLENOID_HOLD );
    assert( gpioCancelTimer( TIMER_RIGHT_FLIP ) == 0 );
}

static void switchRightCallback(int gpio, int level, uint32_t tick) {
    if ( level == RISING_EDGE ) {
        printf("flipper right on\n");  
        gpioWrite( SOLENOID_FLIPPER_RIGHT, SOLENOID_ON );
        assert( gpioSetTimerFunc( TIMER_RIGHT_FLIP, SOLENOID_ON_MS, holdRightCallback ) == 0 );
    } else {
        printf("flipper right off\n");  
        gpioWrite( SOLENOID_FLIPPER_RIGHT, SOLENOID_OFF );
        assert( gpioCancelTimer( TIMER_RIGHT_FLIP ) == 0 );
    }
}

static void switchLeftCallback(int gpio, int level, uint32_t tick) {
    if ( level == RISING_EDGE ) {
        printf("flipper left on\n");
        gpioWrite( SOLENOID_FLIPPER_LEFT, SOLENOID_ON );
        assert( gpioSetTimerFunc( TIMER_LEFT_FLIP, SOLENOID_ON_MS, holdLeftCallback ) == 0 );
    } else {
        printf("flipper left off\n");
        gpioWrite( SOLENOID_FLIPPER_LEFT, SOLENOID_OFF );
        assert( gpioCancelTimer( TIMER_LEFT_FLIP ) == 0 );
    }
}

void flippersInit(void) {
    printf("flippersInit()\n");
    gpioSetMode( SOLENOID_FLIPPER_LEFT, PI_OUTPUT );
    gpioSetMode( SOLENOID_FLIPPER_RIGHT, PI_OUTPUT );
    gpioWrite( SOLENOID_FLIPPER_LEFT, SOLENOID_OFF );
    gpioWrite( SOLENOID_FLIPPER_RIGHT, SOLENOID_OFF );

    printf("gpioGetPWMfrequency:%d\n", gpioGetPWMfrequency(SOLENOID_FLIPPER_LEFT) );
    gpioSetPWMfrequency( SOLENOID_FLIPPER_LEFT, 8000 );
    gpioSetPWMfrequency( SOLENOID_FLIPPER_RIGHT, 8000 );

    gpioSetMode( SWITCH_FLIPPER_LEFT, PI_INPUT );
    gpioSetMode( SWITCH_FLIPPER_RIGHT, PI_INPUT );
    gpioSetPullUpDown( SWITCH_FLIPPER_LEFT, PI_PUD_UP );
    gpioSetPullUpDown( SWITCH_FLIPPER_RIGHT, PI_PUD_UP );
    gpioGlitchFilter( SWITCH_FLIPPER_LEFT, 250 );
    gpioGlitchFilter( SWITCH_FLIPPER_RIGHT, 250 );
}

void flippersEnable(bool enable) {
    printf("flippersEnable(%d)\n",enable);
    if ( enable ) {
        gpioSetAlertFunc( SWITCH_FLIPPER_RIGHT, switchRightCallback );
        gpioSetAlertFunc( SWITCH_FLIPPER_LEFT, switchLeftCallback );
    } else {
        gpioSetAlertFunc( SWITCH_FLIPPER_RIGHT, NULL );
        gpioSetAlertFunc( SWITCH_FLIPPER_LEFT, NULL );
        gpioCancelTimer( TIMER_LEFT_FLIP );
        gpioCancelTimer( TIMER_RIGHT_FLIP );
        gpioWrite( SOLENOID_FLIPPER_LEFT, SOLENOID_OFF );
        gpioWrite( SOLENOID_FLIPPER_RIGHT,SOLENOID_OFF );
    }
}


