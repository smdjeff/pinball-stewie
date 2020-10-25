#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"

#include "switches.h"

static char* switchName(int gpio) {
   switch( gpio ) {
       case SWITCH_START:         return "start";
       case SWITCH_FLIPPER_LEFT:  return "flipper_left";
       case SWITCH_FLIPPER_RIGHT: return "flipper_right";
       case SWITCH_LOIS:          return "louis";
       case SWITCH_MEG:           return "meg";
       case SWITCH_PETER:         return "peter";
       case SWITCH_SHOOTER:       return "shooter";
       case SWITCH_BRIAN_CHRIS:   return "brian_chris";
       case SWITCH_CHRIS_BRIAN:   return "chris_brian";
       default: return "?"; 
   }
}

static void shooterOff(void) {
   gpioWrite( SOLENOID_SHOOTER, 0 );
   gpioSetTimerFunc( 5, PI_MIN_MS, 0);
}

static void switchCallback(int gpio, int level, uint32_t tick) {
    printf("switch %s %d\n", switchName(gpio), level);
    switch ( gpio ) {
       case SWITCH_START:
           if ( level == 0 ) { 
              gpioWrite( SOLENOID_SHOOTER, 1 );
              gpioSetTimerFunc( 5, 100, shooterOff );
           }
           break;
    }
}
    
void switchesInit(void) {
    printf("switchesInit()\n");
    int switches[] = {  SWITCH_START, 
			SWITCH_LOIS, 
			SWITCH_MEG, 
			SWITCH_PETER, 
			SWITCH_SHOOTER,
			SWITCH_BRIAN_CHRIS,
			SWITCH_CHRIS_BRIAN };
    for (int i=0; i<sizeof(switches)/sizeof(switches[0]); i++) {
        int gpio = switches[i];
	gpioSetMode( gpio, PI_INPUT );
        gpioSetPullUpDown( gpio, PI_PUD_UP );
        gpioGlitchFilter( gpio, 250 );
        gpioSetAlertFunc( gpio, switchCallback );
    }
    gpioSetMode( SWITCH_DRIVE_SIGNAL, PI_OUTPUT );
    gpioWrite( SWITCH_DRIVE_SIGNAL, 0 );
}


