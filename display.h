#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void displayInit(void);
void displayDeInit(void);

void displayText(char *text);
void displayScore(int score);
void displayBall(int ball);

#endif // _DISPLAY_H_


