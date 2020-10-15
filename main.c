#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
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


int main (void) {

    gpioInitialise();

    ledMatrixInit();
    flippersInit();
    switchesInit();
    lampsInit();
    displayInit();
    soundInit();

    for (;;) {

        // attact mode playfield lighting
        uint64_t t = time_ms();
        static uint64_t last_t = 0;
	    if ( t - last_t > 100 ) {
            last_t = t;
            static uint8_t ct = 1;
            ledMatrixBrian( ct );
            ledMatrixMeg( ct );
            ledMatrixPeter( ct );
            ledMatrixLois( ct );
            ledMatrixChris( ct );
            ct <<= 1;
            if ( ct > 0x1f ) {
                ct = 1;
            }
        } 
        
        ledMatrixRefresh();
    }
    
    return 0;
}

