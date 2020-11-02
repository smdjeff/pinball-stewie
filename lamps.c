#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include "portable.h"
#include "stewie-lamps.h"

#include "lamps.h"

    
void lampsInit(void) {
    printf("lampsInit()\n");
    gpioSetMode( LAMP_PLAYFIELD, PI_OUTPUT );
    gpioSetMode( LAMP_SHOOT_AGAIN, PI_OUTPUT );
    gpioWrite( LAMP_PLAYFIELD, LAMP_OFF );
    gpioWrite( LAMP_SHOOT_AGAIN, LAMP_OFF );
}


static blinks_t blinker = 0;

static void blinkCallback(void) {
    static int j = 0;
    switch ( blinker ) {
        case blink_shoot_again:
             gpioWrite( LAMP_SHOOT_AGAIN, !gpioRead( LAMP_SHOOT_AGAIN ) );
             break;
        case blink_brian:
             switch(j) {
                 case 0: ledMatrixBrian( 0x1e ); j++; break;
                 case 1: ledMatrixBrian( 0x1c ); j++; break;
                 case 2: ledMatrixBrian( 0x18 ); j++; break;
                 case 3: ledMatrixBrian( 0x10 ); j++; break;
                 case 4: ledMatrixBrian( 0x00 ); j++; break;
                 case 5: ledMatrixBrian( 0x1f ); j++; break;
                 case 6: ledMatrixBrian( 0x1e ); j++; break;
                 case 7: ledMatrixBrian( 0x1c ); j++; break;
                 case 8: ledMatrixBrian( 0x18 ); j++; break;
                 case 9: ledMatrixBrian( 0x10 ); j++; break;
                 case 10: ledMatrixBrian( 0x00 ); j=0; gpioCancelTimer( TIMER_BLINK ); break;
             }
             break; 
         case blink_meg:
             break;
         case blink_peter:
             break; 
        case blink_lois:
             break;
        case blink_chris:
             break; 
   }    
}

void lampsBlink( blinks_t blink ) {
    switch ( blinker ) {
        case blink_shoot_again:
            gpioWrite( LAMP_SHOOT_AGAIN, LAMP_OFF );
            gpioCancelTimer( TIMER_BLINK );
            break;
    }

    blinker = blink;

    switch ( blink ) {
        case blink_none:
            break;
        case blink_shoot_again:
            gpioWrite( LAMP_SHOOT_AGAIN, LAMP_ON );
            assert( gpioSetTimerFunc( TIMER_BLINK, 250, blinkCallback ) == 0 );
            break;
        case blink_brian:
        case blink_meg:
        case blink_peter:
        case blink_lois:
        case blink_chris:
            assert( gpioSetTimerFunc( TIMER_BLINK, 100, blinkCallback ) == 0 );
            break;
    }
}

