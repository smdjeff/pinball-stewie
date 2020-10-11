#ifndef _STEWIE_LAMPS_H_
#define _STEWIE_LAMPS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// convenience functions for applying a bitmask to the letters of a 
// name string of lights
void ledMatrixChris(int value);
void ledMatrixMeg(int value);
void ledMatrixPeter(int value);
void ledMatrixLois(int value);
void ledMatrixBrian(int value);

// shifts our led matrix values into the playfield
void ledMatrixRefresh(void);

void ledMatrixInit(void);
    
#endif // _STEWIE_LAMPS_H_

