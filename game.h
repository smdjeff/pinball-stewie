#ifndef _GAME_H_
#define _GAME_H_

#include <stdint.h>
#include <stdbool.h>

void gameInit(void);
void gameStart(void);
void gameStop(void);
bool gameOn(void);

extern int balls;

#endif // _GAME_H_
