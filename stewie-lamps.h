#ifndef _STEWIE_LAMPS_H_
#define _STEWIE_LAMPS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// bitmask application to letters in a named string
void ledMatrixChris(int value);
void ledMatrixMeg(int value);
void ledMatrixPeter(int value);
void ledMatrixLois(int value);
void ledMatrixBrian(int value);

void ledMatrixInit(void);
    
#endif // _STEWIE_LAMPS_H_

