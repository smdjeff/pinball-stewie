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
        case sound_start: {
            char* s0[]= {
                "Main theme music",
                "Timed event music",
                "Chris theme music",
            };
//            gpioStartThread(playback, s0[rand()/(RAND_MAX / 3 + 1)]);
            char* s1[]= {
                "Stewie is going to kick your ass",
                "Small playfield intro",
                "Multiball start",
            };
//            gpioStartThread(playback, s1[rand()/(RAND_MAX / 3 + 1)]);
            break; }
        
        case sound_launch: {
            char* s[] = {
                "Launch 1",
                "Launch 2",
                "Launch 3",
                "Launch 4",
                "Launch 5"
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 5 + 1)]);
            break; }
            
        case sound_hit: {
            char* s[] = {
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
            gpioStartThread(playback, s[rand()/(RAND_MAX / 10 + 1)]);
            break; }
            
        case sound_game_over: {
            char* s[]= {
                "Stewie says game over man",
                "Stewie will not tolerate failure"
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 2 + 1)]);
            break; }
            
        case sound_drain: {
            char* s0[] = {
                "Drain music 1",
                "Drain music 2",
                "Drain music 3",
                "Drain music 4",
                "Drain music 5",
            };
            char* s1[] = {
                "Stewie says damn you vile woman",
                "Stewie says one down",
                "Stewie says what the deuce was that",
                "Stewie says you're doin' good"
            };
            gpioStartThread(playback, s0[rand()/(RAND_MAX / 5 + 1)]);
            //gpioStartThread(playback, s1[rand()/(RAND_MAX / 4 + 1)]);
            break; }

        case sound_brian: {
            char* s[]= {
                "Brian asks if anyone wants a mojito",
                "Brian says good good so far",
                "Brian says wow",
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 3 + 1)]);
            break; }

        case sound_meg: {
            char* s[]= {
                "Meg cries",
                "Meg hates everyone",
                "Meg wants Lois to do something"
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 3 + 1)]);
            break; }

        case sound_peter: {
            char* s[]= {
                "Peter giggles",
                "Peter has an idea",
                "Peter says that was awesome",
                "Peter says you bastard"
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 4 + 1)]);
            break; }

        case sound_lois: {
            char* s[]= {
                "Lois advises Meg",
                "Lois isn't wearing any panties",
                "Lois says what on earth was that"
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 3 + 1)]);
            break; }

        case sound_chris: {
            char* s[]= {
                "Chris isn't supposed to mention poo",
                "Someone peed in Chris' pants"
            };
            gpioStartThread(playback, s[rand()/(RAND_MAX / 2 + 1)]);
            break; }
    }
}

