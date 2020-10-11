#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include "portable.h"
    
#include "mcp23017.h"
    

#define GPIOA	0
#define GPIOB	1

#define IODIR	0
#define IPOL	1
#define GPINTEN	2
#define DEFVAL	3
#define INTCON	4
#define IOCON	5
#define GPPU	6
#define INTF	7
#define INTCAP	8
#define GPIO	9
#define OLAT	10

#define MCP_REGISTER(r,g) (((r)<<1)|(g)) /* For I2C routines */

static int i2c_handle = -1;

static void mcp23017_write(int reg, int AB, int value) {
	unsigned reg_addr = MCP_REGISTER(reg, AB);
	i2cWriteByteData(i2c_handle, reg_addr, value);
}

static void mcp23017_write_both(int reg, int value) {
	mcp23017_write(reg, GPIOA, value);
	mcp23017_write(reg, GPIOB, value);
}

void mcp23017Output(uint8_t value) {
	unsigned reg_addr = MCP_REGISTER(GPIO, GPIOA);
	i2cWriteByteData(i2c_handle, reg_addr, value);
}

void mcp23017Init(void) {
    i2c_handle = i2cOpen(0/*i2cBus*/, 0x20/*i2cAddr*/, 0/*i2cFlags*/);
    assert( i2c_handle >= 0 );
    
	mcp23017_write_both(IOCON,0b00000000);	// MIRROR=0,ODR=0
	mcp23017_write_both(GPINTEN,0x00);	    // no ints
	mcp23017_write_both(DEFVAL,0x00);
	mcp23017_write_both(OLAT,0x00);
	mcp23017_write_both(GPPU,0b00000000);	// pullups disabled
	mcp23017_write_both(IPOL,0b00000000);   // no polarity inversion
	mcp23017_write_both(IODIR,0b00000000);	// all outputs
	mcp23017_write_both(INTCON,0b00000000);	// cmp inputs to previous
	mcp23017_write_both(GPINTEN,0b00000000);// no int on change 
}
