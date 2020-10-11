#ifndef _MCP23017_H_
#define _MCP23017_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void mcp23017Init(void);
void mcp23017Output(uint8_t value);

#endif // _MCP23017_H_

