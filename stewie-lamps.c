#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include "portable.h"
    
#include "mcp23017.h"    


// based on studying the schematic of the led matrix hardware shift registers
// on page 142 of the stern family guy pinball manual

static uint8_t c_0[ 2 ] = { 0x00,0x00 };
static uint8_t c_1[ 2 ] = { 0x00,0x00 };
static uint8_t c_2[ 2 ] = { 0x00,0x00 };
#define        r_0  0
#define        r_1  1

#define SET_BIT(reg,bit)  ((reg) |= (1<<(bit)))
#define CLR_BIT(reg,bit)  ((reg) &= ~(1<<(bit)))
       
void ledMatrixBrian(int value) {
  (value & 0x01) ? SET_BIT(c_0[r_1],4) : CLR_BIT(c_0[r_1],4); // B
  (value & 0x02) ? SET_BIT(c_0[r_1],3) : CLR_BIT(c_0[r_1],3); // R
  (value & 0x04) ? SET_BIT(c_0[r_1],2) : CLR_BIT(c_0[r_1],2); // I
  (value & 0x08) ? SET_BIT(c_0[r_1],1) : CLR_BIT(c_0[r_1],1); // A
  (value & 0x10) ? SET_BIT(c_0[r_1],0) : CLR_BIT(c_0[r_1],0); // N
}

void ledMatrixMeg(int value) {
  (value & 0x01) ? SET_BIT(c_0[r_0],1) : CLR_BIT(c_0[r_0],1); // M
  (value & 0x02) ? SET_BIT(c_0[r_0],2) : CLR_BIT(c_0[r_0],2); // E
  (value & 0x04) ? SET_BIT(c_0[r_0],3) : CLR_BIT(c_0[r_0],3); // G
}

void ledMatrixPeter(int value) {
  (value & 0x01) ? SET_BIT(c_1[r_1],1) : CLR_BIT(c_1[r_1],1); // P
  (value & 0x02) ? SET_BIT(c_1[r_0],0) : CLR_BIT(c_1[r_0],0); // E
  (value & 0x04) ? SET_BIT(c_1[r_0],1) : CLR_BIT(c_1[r_0],1); // T
  (value & 0x08) ? SET_BIT(c_1[r_0],2) : CLR_BIT(c_1[r_0],2); // E
  (value & 0x10) ? SET_BIT(c_1[r_0],3) : CLR_BIT(c_1[r_0],3); // R
}

void ledMatrixLois(int value) {
  (value & 0x01) ? SET_BIT(c_2[r_1],3) : CLR_BIT(c_2[r_1],3); // L
  (value & 0x02) ? SET_BIT(c_2[r_1],2) : CLR_BIT(c_2[r_1],2); // O
  (value & 0x04) ? SET_BIT(c_2[r_1],1) : CLR_BIT(c_2[r_1],1); // I
  (value & 0x08) ? SET_BIT(c_2[r_1],0) : CLR_BIT(c_2[r_1],0); // S
}

void ledMatrixChris(int value) {
  (value & 0x01) ? SET_BIT(c_2[r_0],3) : CLR_BIT(c_2[r_0],3); // C
  (value & 0x02) ? SET_BIT(c_2[r_0],2) : CLR_BIT(c_2[r_0],2); // H
  (value & 0x04) ? SET_BIT(c_2[r_0],1) : CLR_BIT(c_2[r_0],1); // R
  (value & 0x08) ? SET_BIT(c_2[r_0],0) : CLR_BIT(c_2[r_0],0); // I
  (value & 0x10) ? SET_BIT(c_0[r_0],0) : CLR_BIT(c_0[r_0],0); // S
}

static void writeRow(uint8_t b) {
  gpioWrite( LED_MATRIX_CLK, 0 );
  mcp23017Output( b );
  gpioWrite( LED_MATRIX_CLK, 1 );
}

static void matrixRefresh(void) {
  static uint8_t r = 0;
  // d7 blanks all lamps when high (when shifted to IC1's outputs)
  // d0,d1 inverted set row enable (when shifted to IC5's output)
  // the logic of the discretes T1,T2 for display blanking is:
  // CLK d7  OC 
  // L   L   H  blanked
  // L   H   H  blanked
  // H   L   L  (inverted lsb is enabled row)
  // H   H   H  blanked
  if ( r == 0 ) {
    // shift in row 0
    writeRow( 0x81 );
    writeRow( c_2[r_0] | 0x80 );
    writeRow( c_1[r_0] | 0x80 );
    writeRow( c_0[r_0] );
    r = 1;
  } else {
    // shift in row 1
    writeRow( 0x82 );
    writeRow( c_2[r_1] | 0x80 );
    writeRow( c_1[r_1] | 0x80 );
    writeRow( c_0[r_1] );
    r = 0;
  }
}

void ledMatrixClear(void) {
  memset( c_2, 0x00, sizeof(c_2) );
  memset( c_1, 0x00, sizeof(c_1) );
  memset( c_0, 0x00, sizeof(c_0) );
}

void ledMatrixInit(void) {
  printf("ledMatrixInit()\n");
  gpioSetMode( LED_MATRIX_CLK, PI_OUTPUT );
  mcp23017Init();
  writeRow( 0x80 ); // blank all lamps
  assert( gpioSetTimerFunc( TIMER_MATRIX, 10, matrixRefresh ) == 0);
}


