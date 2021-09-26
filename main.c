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
#include "game.h"
    

volatile bool killed = false;
static void intHandler(int sig) {
    printf("intHandler:%d\n",sig);
//    signal(sig, SIG_IGN);
    killed = true;
}


int main(int argc, char *argv[]) {

    // https://github.com/joan2937/pigpio/issues/399
    gpioCfgClock( 5, 0, 0 ); // tell gpio to use PWM peripheral

    gpioInitialise();

    ledMatrixInit();
    flippersInit();
    switchesInit();
    lampsInit();
    displayInit();
    soundInit();
    gameInit();

    // unsigned int seed;
    // getrandom( &seed, sizeof(seed), 0 );
    srand( time(0) );

    //// run
    signal(SIGINT, intHandler);
    while ( !killed ) {
        usleep(100 *1000);
        fflush(stdout);
    }

    //// stop
    printf("killing...\n");
    gameStop();
    for (int i=0;i<10;i++ ) {
       gpioCancelTimer( i );
    }
    ledMatrixClear();
    printf("killed\n");
    
    return 0;
}

