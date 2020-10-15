#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "portable.h"
    
#include "mcp23017.h"    

    
// our led matrix memory map
static uint8_t col_a_row_0 = 0x00;
static uint8_t col_a_row_1 = 0x00;
static uint8_t col_b_row_0 = 0x00;
static uint8_t col_b_row_1 = 0x00;
static uint8_t col_c_row_0 = 0x00;
static uint8_t col_c_row_1 = 0x00;

#define BITON(reg,bit)  ((reg)|=(1<<(bit)))
#define BITOFF(reg,bit) ((reg)&=~(1<<(bit)))

// based on studying the family guy pinball schematics page 142,
// we see the shift register led matrix works like this
#define CHRIS_C(on)  (on) ? BITON(col_c_row_1,3) : BITOFF(col_c_row_1,3)
#define CHRIS_H(on)  (on) ? BITON(col_c_row_1,2) : BITOFF(col_c_row_1,2)
#define CHRIS_R(on)  (on) ? BITON(col_c_row_1,1) : BITOFF(col_c_row_1,1)
#define CHRIS_I(on)  (on) ? BITON(col_c_row_1,0) : BITOFF(col_c_row_1,0)
#define CHRIS_S(on)  (on) ? BITON(col_a_row_1,0) : BITOFF(col_a_row_1,0)

#define MEG_M(on)    (on) ? BITON(col_a_row_1,1) : BITOFF(col_a_row_1,1)
#define MEG_E(on)    (on) ? BITON(col_a_row_1,2) : BITOFF(col_a_row_1,2)
#define MEG_G(on)    (on) ? BITON(col_a_row_1,3) : BITOFF(col_a_row_1,3)

#define PETER_P(on)  (on) ? BITON(col_b_row_0,1) : BITOFF(col_b_row_0,1)
#define PETER_E(on)  (on) ? BITON(col_b_row_1,0) : BITOFF(col_b_row_1,0)
#define PETER_T(on)  (on) ? BITON(col_b_row_1,1) : BITOFF(col_b_row_1,1)
#define PETER_EE(on) (on) ? BITON(col_b_row_1,2) : BITOFF(col_b_row_1,2)
#define PETER_R(on)  (on) ? BITON(col_b_row_1,3) : BITOFF(col_b_row_1,3)

#define LOIS_L(on)   (on) ? BITON(col_c_row_0,3) : BITOFF(col_c_row_0,3)
#define LOIS_O(on)   (on) ? BITON(col_c_row_0,2) : BITOFF(col_c_row_0,2)
#define LOIS_I(on)   (on) ? BITON(col_c_row_0,1) : BITOFF(col_c_row_0,1)
#define LOIS_S(on)   (on) ? BITON(col_c_row_0,0) : BITOFF(col_c_row_0,0)

#define BRIAN_B(on)  (on) ? BITON(col_a_row_0,4) : BITOFF(col_a_row_0,4)
#define BRIAN_R(on)  (on) ? BITON(col_a_row_0,3) : BITOFF(col_a_row_0,3)
#define BRIAN_I(on)  (on) ? BITON(col_a_row_0,2) : BITOFF(col_a_row_0,2)
#define BRIAN_A(on)  (on) ? BITON(col_a_row_0,1) : BITOFF(col_a_row_0,1)
#define BRIAN_N(on)  (on) ? BITON(col_a_row_0,0) : BITOFF(col_a_row_0,0)

       
void ledMatrixChris(int value) {
    CHRIS_C( (value & 0x01) );
    CHRIS_H( (value & 0x02) );
    CHRIS_R( (value & 0x04) );
    CHRIS_I( (value & 0x08) );
    CHRIS_S( (value & 0x10) );
}

void ledMatrixMeg(int value) {
    MEG_M( (value & 0x01) );
    MEG_E( (value & 0x02) );
    MEG_G( (value & 0x04) );
}

void ledMatrixPeter(int value) {
    PETER_P( (value & 0x01) );
    PETER_E( (value & 0x02) );
    PETER_T( (value & 0x04) );
    PETER_EE( (value & 0x08) );
    PETER_R( (value & 0x10) );
}

void ledMatrixLois(int value) {
    LOIS_L( (value & 0x01) );
    LOIS_O( (value & 0x02) );
    LOIS_I( (value & 0x04) );
    LOIS_S( (value & 0x08) );
}

void ledMatrixBrian(int value) {
    BRIAN_B( (value & 0x01) );
    BRIAN_R( (value & 0x02) );
    BRIAN_I( (value & 0x04) );
    BRIAN_A( (value & 0x08) );
    BRIAN_N( (value & 0x10) );
}

void ledMatrixInit(void) {
    printf("ledMatrixInit()\n");
    gpioSetMode( LED_MATRIX_CLK, PI_OUTPUT );
    mcp23017Init();
}

static void ledwrite(uint8_t b) {
    gpioWrite( LED_MATRIX_CLK, 0 );
    mcp23017Output( b );
    gpioWrite( LED_MATRIX_CLK, 1 );
}

#define delay_ms(ms)    do { usleep(ms*1000); } while(0)

void ledMatrixRefresh(void) {        
    ledwrite( 0x82 ); // row 0 latch
    ledwrite( col_c_row_0);
    ledwrite( col_b_row_0);
    ledwrite( col_a_row_0);
    delay_ms( 8 ); //hold

    ledwrite( 0x81 ); // row 1 latch
    ledwrite( col_c_row_1 );
    ledwrite( col_b_row_1 );
    ledwrite( col_a_row_1 );
    delay_ms( 8 ); // hold
}    
