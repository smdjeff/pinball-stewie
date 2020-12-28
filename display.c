#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <czmq.h> // https://zeromq.org/
#include "portable.h"

#include "display.h"

void *context = NULL;
void *requester = NULL;

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

   printf( "connecting to display server...\n" );
   context = zmq_ctx_new();
   requester = zmq_socket( context, ZMQ_PUSH );
   int err = zmq_connect( requester, "tcp://127.0.0.1:5555" );
   if (err==0) { 
      printf( "connected\n" );
   } else {
      printf( "connect error:%d", err );
   }

   displayCommand( "<font>", "d3" );
   displayCommand( "<brightness>", "0.3" );
   displayCommand( "<text>", "VICTORY SHALL BE MINE!" );
}

void displayDeInit(void) {
   zmq_close( requester );
   zmq_ctx_destroy( context );
}

void displayScore(int score) {
   static int total = 0;
   if ( score ) {
       total += score;
   } else {
       total = 0;
   }
   char s[10] = {0,};
   snprintf( s, sizeof(s)-1, "%d", total );
   displayCommand( "<text>", s );
}

void displayText(char *text) {
   displayCommand( "<text>", text );
}


