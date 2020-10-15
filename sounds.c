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


void soundPlay(sound_t sound) {
    printf("soundPlay:%d\n", sound);
}

