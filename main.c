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


void attractCallback(void) {
    static int st = 0;
    static uint32_t ct = 1;
    
    switch ( st ) {
            
        case 0:
            ledMatrixBrian( ct & 0x1f );
            ledMatrixMeg( (ct>>5) & 0x07 );
            ledMatrixPeter( (ct>>8) &0x1f  );
            ledMatrixLois( (ct>>13) & 0x0f );
            ledMatrixChris( (ct>>17) & 0x1f );
            ct <<= 1;
            if ( ct > 0x7FFFFF ) {
                ledMatrixClear();
                ct = 1;
                st++;
            }
            break;
        case 1:
            ledMatrixBrian( ct & 0x1f );
            ledMatrixMeg( ct & 0x07 );
            ledMatrixPeter( ct & 0x1f );
            ledMatrixLois( ct & 0x0f );
            ledMatrixChris( ct & 0x1f );
            ct <<= 1;
            if ( ct > 0x3f ) {
                ledMatrixClear();
                ct = 1;
                st++;
            }
            break;
        case 2:
            switch( ct ) {
                case 1: ledMatrixClear(); ledMatrixBrian( 0x1f ); ct++; break;
                case 2: ledMatrixClear(); ledMatrixMeg( 0x07 ); ct++; break;
                case 3: ledMatrixClear(); ledMatrixPeter( 0x1f ); ct++; break;
                case 4: ledMatrixClear(); ledMatrixLois( 0x0f ); ct++; break;
                case 5: ledMatrixClear(); ledMatrixChris( 0x1f ); ct++; break;
                case 6: ledMatrixClear(); ledMatrixLois( 0x0f ); ct++; break;
                case 7: ledMatrixClear(); ledMatrixPeter( 0x1f ); ct++; break;
                case 8: ledMatrixClear(); ledMatrixMeg( 0x07 ); ct++; break;
                case 9: ledMatrixClear(); ledMatrixBrian( 0x1f ); ct++; break;
                case 10: ledMatrixBrian( 0x1f ); ledMatrixMeg( 0x07 ); ledMatrixPeter( 0x1f ); ledMatrixLois( 0x0f ); ledMatrixChris( 0x1f ); ct++; break;
                case 11: ledMatrixClear(); ct++; break;
                case 12: ledMatrixBrian( 0x1f ); ledMatrixMeg( 0x07 ); ledMatrixPeter( 0x1f ); ledMatrixLois( 0x0f ); ledMatrixChris( 0x1f ); ct++; break;
                default: ledMatrixClear(); ct = 1; st++; break;
            }
            break;
            
        default:
            st = 0;
            break;

    }
}


int main (void) {

    // https://github.com/joan2937/pigpio/issues/399
    gpioCfgClock( 5, 0, 0 ); // tell gpio to use PWM peripheral

    gpioInitialise();

    ledMatrixInit();
    flippersInit();
    switchesInit();
    lampsInit();
    displayInit();
    soundInit();

    soundPlay( sound_hit );
    
    assert( gpioSetTimerFunc( TIMER_ATTRACT, 100, attractCallback ) == 0 );

    flippersEnable();

    for (;;) {
        usleep(100);
    }
    
    return 0;
}

