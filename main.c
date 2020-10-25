#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include "portable.h"

#include "stewie-lamps.h"
#include "flippers.h"
#include "switches.h"
#include "lamps.h"
#include "display.h"
#include "sounds.h"    

    
uint64_t time_ms(void) {
    struct timeval tv;
    gettimeofday( &tv,NULL );
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void blinkCallback(void) {
    gpioWrite( LAMP_PLAYFIELD, !gpioRead(LAMP_PLAYFIELD) );
    gpioWrite( LAMP_SHOOT_AGAIN, !gpioRead(LAMP_SHOOT_AGAIN) );   
}

void attractCallback(void) {
	static uint32_t ct = 1;
        ledMatrixBrian( ct & 0x1f );
        ledMatrixPeter( ct & 0x1f );
        ledMatrixMeg( (ct>>5) & 0x07 );
//        ledMatrixPeter( (ct>>8) &0x1f  );
        ledMatrixLois( (ct>>13) & 0x0f );
        ledMatrixChris( (ct>>17) & 0x1f );
        ct <<= 1;
        if ( ct > 0x3FFFFF ) {   
            ct = 1;
        } 
}


int main (void) {

//    gpioCfgClock( 2, 0, 0 ); // allow a 20khz pwm
    gpioInitialise();

    ledMatrixInit();
    flippersInit();
    switchesInit();
    lampsInit();
    displayInit();
    soundInit();

    assert( gpioSetTimerFunc( 3, 1000, blinkCallback ) == 0 );
    assert( gpioSetTimerFunc( 4, 100, attractCallback ) == 0 );

    flippersEnable();

    for (;;) {
        usleep(100);
    }
    
    return 0;
}

