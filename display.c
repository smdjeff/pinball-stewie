#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"

#include "display.h"

    
static void *startDisplay(void *arg) {
   system( "python i2c-display.py" );
}

    
void displayInit(void) {
    printf("displayInit()\n");
    gpioStartThread( startDisplay, "" );
}


