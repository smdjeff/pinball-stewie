#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"

#include "sounds.h"

    
void soundInit(void) {
    printf("soundInit()\n");
}

static void *playback(void *arg) {
   char cmd[64] = {0,};
   snprintf ( cmd, sizeof(cmd), "aplay \"sounds/%s.wav\"", arg );
   printf( "system:%s\n", cmd );
   system( cmd );
}

void soundPlay(sound_t sound) {
    printf("soundPlay:%d\n", sound);
    
    switch( sound ) {
        case sound_start:
            gpioStartThread(playback, "Main theme music");
            break;
        
        case sound_launch: {
            const char* s[] = {
                "Launch 1",
                "Launch 2",
                "Launch 3",
                "Launch 4",
                "Launch 5"
            };
            gpioStartThread(playback, s[rand()%(5 + 1)]);
            break; }
            
        case sound_hit: {
            const char* s[] = {
                "Hit 1",
                "Hit 2 (fart)",
                "Hit 3",
                "Hit 4",
                "Hit 5",
                "Hit 6",
                "Hit 7",
                "Hit 8",
                "Hit 9",
                "Hit 10",
                "Hit 11"
            };
            gpioStartThread(playback, s[rand()%(11 + 1)]);
            break; }
            
        case sound_game_over: {
            const char* s[]= {
                "Stewie says game over man",
                "Stewie will not tolerate failure"
            };
            int i = (rand()%(2 + 1));    
            gpioStartThread(playback, s[i]);
            break; }
            
        case sound_drain: {
            const char* s0[] = {
                "Drain music 1",
                "Drain music 2",
                "Drain music 3",
                "Drain music 4",
                "Drain music 5",
            };
            const char* s1[] = {
                "Stewie says damn you vile woman",
                "Stewie says one down",
                "Stewie says what the deuce was that",
                "Stewie says you're doin' good"
            };
            gpioStartThread(playback, s0[rand()%(5 + 1)]);
            gpioStartThread(playback, s1[rand()%(4 + 1)]);
            break; }
            
    }
}

