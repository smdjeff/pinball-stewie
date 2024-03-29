#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include "portable.h"

#include "is31fl3731.h"
    
    
#define ISSI_REG_PICTUREFRAME           0x01
#define ISSI_REG_SHUTDOWN               0x0A
#define ISSI_COMMANDREGISTER            0xFD
#define ISSI_BANK_FUNCTIONREG           0x0B 

    
#ifndef _swap_int16_t
#define _swap_int16_t(a, b)             \
  {                                     \
    int16_t t = a;                      \
    a = b;                              \
    b = t;                              \
  }
#endif

static const int width = 17;
static const int height = 7;
static const int i2c_bus = 1;
static const int i2c_addr = 0x74;
static const int rotation = 4;
static const float brightness = 0.3;

static int i2c_handle = -1;
static uint8_t _frame = 0;


static void selectBank(uint8_t bank) {
   // printf("selectBank\n");
   i2cWriteByteData( i2c_handle, ISSI_COMMANDREGISTER, bank );
}

static void writeRegister8(uint8_t bank, uint8_t reg, uint8_t data) {
   // printf("writeRegister8\n");
   selectBank(bank);
   i2cWriteByteData( i2c_handle, reg, data );
}

void is31fl3731Init(void) {
    printf("is31fl3731Init\n");
    i2c_handle = i2cOpen( i2c_bus, i2c_addr, 0/*i2cFlags*/ );
    assert( i2c_handle );
    
    writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);
    usleep(10);
    writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);

    _frame = 0;
    is31fl3731Clear(); // all leds to 0 PWM

    for (uint8_t f = 0; f < 8; f++) {
        for (uint8_t i = 0; i <= 0x11; i++) {
            writeRegister8(f, i, 0xff); // all 8 LEDs on
        }
    }

    is31fl3731DisplayFrame(_frame);
}
    
void is31fl3731Clear(void) {
  printf("is31fl3731Clear\n");
  selectBank(_frame);
  char erasebuf[25] = {0,};
  for (uint8_t i = 0; i < 6; i++) {
    erasebuf[0] = 0x24 + i * 24;
    i2cWriteDevice( i2c_handle, erasebuf, sizeof(erasebuf)/sizeof(erasebuf[0]));
  }
}

void is31fl3731SetLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank) {
  //printf("is31fl3731SetLEDPWM\n");
  if (lednum >= 144)
    return;
  writeRegister8(bank, 0x24 + lednum, (float)pwm * brightness);
}

void is31fl3731DrawPixel(int16_t x, int16_t y, uint16_t color) {
  //printf("is31fl3731DrawPixel\n");
  switch ( rotation ) {
  case 1:
    _swap_int16_t(x, y);
    x = 16 - x - 1;
    break;
  case 2:
    x = 16 - x - 1;
    y = 9 - y - 1;
    break;
  case 3:
    _swap_int16_t(x, y);
    y = 9 - y - 1;
    break;
  case 4:
    _swap_int16_t(x, y);
    x = 16 - x - 1;
    y = 9 - y - 1;
    break;
  }

  if ((x < 0) || (x >= 16))
    return;
  if ((y < 0) || (y >= 9))
    return;
  if (color > 255)
    color = 255;

  is31fl3731SetLEDPWM(x + y * 16, color, _frame);
}


void is31fl3731SetFrame(uint8_t frame) { 
    printf("is31fl3731SetFrame\n");
    _frame = frame; 
}

void is31fl3731DisplayFrame(uint8_t frame) {
  printf("is31fl3731DisplayFrame\n");
  if (frame > 7) {
    frame = 0;
  }
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_PICTUREFRAME, frame);
}



