#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <czmq.h> // https://zeromq.org/
#include "portable.h"

#include "display.h"

void *context = NULL;
void *requester = NULL;
    
static void *startDisplay(void *arg) {
   system( "python display-server.py" );
}

static void displayCommand(char *cmd, char *data) {
   int sz = strlen(cmd) + strlen(data);
   char *packet = malloc( sz + 1 );
   assert( packet );
   strcpy( packet, cmd );
   strcat( packet, data ); 
   zmq_send( requester, packet, sz, 0 );
   free( packet );
}
    
void displayInit(void) {
   printf( "displayInit()\n" );
   gpioStartThread( startDisplay, "" );

   printf( "connecting to i2c-display server...\n" );
   context = zmq_ctx_new();
   requester = zmq_socket( context, ZMQ_PUSH );
   int err = zmq_connect( requester, "tcp://127.0.0.1:5555" );
   if (err==0) { 
      printf( "connected\n" );
   } else {
      printf( "connect error:%d", err );
   }

   displayCommand( "<font>", "font3x5" );
   displayCommand( "<brightness>", "0.3" );
   displayCommand( "<text>", " VICTORY SHALL BE MINE!" );
   displayCommand( "<scroll>", "start" );
}

void displayDeInit(void) {
   zmq_close( requester );
   zmq_ctx_destroy( context );
}

extern int score;

static void displayCallback(void) {
   printf("displayCallback\n");
   displayCommand( "<scroll>", "stop" );
   displayCommand( "<brightness>", "0.3" );
   char s[10] = {0,};
   snprintf( s, sizeof(s)-1, "%d", score );
   displayCommand( "<text>", s );
   gpioCancelTimer( TIMER_DISPLAY );
}

void displayText(char *text) {
   displayCommand( "<scroll>", "start" );
   displayCommand( "<brightness>", "1.0" );
   displayCommand( "<text>", text );
   gpioSetTimerFunc( TIMER_DISPLAY, 500, displayCallback );
}


