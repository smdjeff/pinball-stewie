#ifndef _LAMPS_H_
#define _LAMPS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define LAMP_OFF      0
#define LAMP_ON       1

typedef enum {
  blink_none,
  blink_shoot_again,
  blink_brian,
  blink_meg,
  blink_peter,
  blink_lois,
  blink_chris
} blinks_t;
    
void lampsInit(void);
void lampsBlink(blinks_t blink);

#endif // _LAMPS_H_

