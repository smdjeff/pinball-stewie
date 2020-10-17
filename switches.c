#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"

#include "switches.h"

    
void switchesInit(void) {
    printf("switchesInit()\n");
    gpioSetMode( SWITCH_START, PI_PUD_UP );
    gpioSetMode( SWITCH_LOIS, PI_PUD_UP );
    gpioSetMode( SWITCH_MEG, PI_PUD_UP );
    gpioSetMode( SWITCH_PETER, PI_PUD_UP );
    gpioSetMode( SWITCH_SHOOTER, PI_PUD_UP );
    gpioSetMode( SWITCH_BRIAN_CHRIS, PI_PUD_UP );
    gpioSetMode( SWITCH_CHRIS_BRIAN, PI_PUD_UP );
    
    gpioSetMode( SWITCH_DRIVE_SIGNAL, PI_OUTPUT );
    gpioWrite( SWITCH_DRIVE_SIGNAL, 0 );
}


