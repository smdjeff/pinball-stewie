#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"

#include "lamps.h"

    
void lampsInit(void) {
    printf("lampsInit()\n");
    gpioSetMode( LAMP_PLAYFIELD, PI_OUTPUT );
    gpioSetMode( LAMP_SHOOT_AGAIN, PI_OUTPUT );
    gpioWrite( LAMP_PLAYFIELD, LAMP_OFF );
    gpioWrite( LAMP_SHOOT_AGAIN, LAMP_OFF );
}


