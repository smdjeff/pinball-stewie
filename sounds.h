#ifndef _SOUNDS_H_
#define _SOUNDS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    sound_start,
    sound_game_over,
    sound_drain,
} sound_t;
    
void soundInit(void);

void soundPlay(sound_t sound);

#endif // _SOUNDS_H_
