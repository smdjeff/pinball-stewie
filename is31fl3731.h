#ifndef _IS31FL3731_H_
#define _IS31FL3731_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
    
void is31fl3731Init(void);    
void is31fl3731DrawPixel(int16_t x, int16_t y, uint16_t color);
void is31fl3731Clear(void);
void is31fl3731SetLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank);
void is31fl3731SetFrame(uint8_t b);
void is31fl3731DisplayFrame(uint8_t frame);


#endif //_IS31FL3731_H_
