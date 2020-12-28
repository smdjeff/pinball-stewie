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
static uint8_t sequence3[] = { 0x06, 0x04, 0x00, 0x07, 0x06, 0x04, 0x00 };
static uint8_t sequence4[] = { 0x0e, 0x0c, 0x08, 0x00, 0x0f, 0x0e, 0x0c, 0x08, 0x00 };
static uint8_t sequence5[] = { 0x1e, 0x1c, 0x18, 0x10, 0x00, 0x1f, 0x1e, 0x1c, 0x18, 0x10, 0x00 };

static void blinkCallback(void) {
    switch ( blinker ) {
        case blink_shoot_again:
             gpioWrite( LAMP_SHOOT_AGAIN, !gpioRead( LAMP_SHOOT_AGAIN ) );
             break;
        case blink_brian: {
             static int i = 0;
             uint8_t s = sequence5[ i++ ];
             ledMatrixBrian( s );
             if ( i >= sizeof(sequence5) ) {
               i = 0;
               gpioCancelTimer( TIMER_BLINK );
             }
             break; }
         case blink_meg: {
              static int i = 0;
              uint8_t s = sequence3[ i++ ];
              ledMatrixMeg( s );
              if ( i >= sizeof(sequence3) ) {
                i = 0;
                gpioCancelTimer( TIMER_BLINK );
              }
              break; }
        case blink_peter: {
             static int i = 0;
             uint8_t s = sequence5[ i++ ];
             ledMatrixPeter( s );
             if ( i >= sizeof(sequence5) ) {
               i = 0;
               gpioCancelTimer( TIMER_BLINK );
             }
             break; }
         case blink_lois: {
              static int i = 0;
              uint8_t s = sequence4[ i++ ];
              ledMatrixLois( s );
              if ( i >= sizeof(sequence4) ) {
                i = 0;
                gpioCancelTimer( TIMER_BLINK );
              }
              break; }
        case blink_chris: {
             static int i = 0;
             uint8_t s = sequence5[ i++ ];
             ledMatrixChris( s );
             if ( i >= sizeof(sequence5) ) {
               i = 0;
               gpioCancelTimer( TIMER_BLINK );
             }
             break; }
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
            assert( gpioSetTimerFunc( TIMER_BLINK, 200, blinkCallback ) == 0 );
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

