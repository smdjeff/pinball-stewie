#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void displayInit(void);

uint8_t displayChar(char ch, uint8_t x0, uint8_t y0);
void displayText(char *text);
void displayScore(int score);
void displayBall(int ball);

#endif // _DISPLAY_H_


