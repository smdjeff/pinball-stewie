#ifndef _SOUNDS_H_
#define _SOUNDS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    sound_boot,
    sound_start,
    sound_launch,
    sound_hit,
    sound_game_over,
    sound_drain,
    sound_brian,
    sound_meg,
    sound_peter,
    sound_lois,
    sound_chris
} sound_t;
    
void soundInit(void);
void soundEnableMusic(bool enable);
void soundPlay(sound_t sound);
void soundStopAll(void);

#endif // _SOUNDS_H_

