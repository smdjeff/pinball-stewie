#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "portable.h"
#include "is31fl3731.h"

#include "display.h"

static int frame = 0;

typedef struct __attribute__((packed)) {
  uint8_t ascii;
  uint8_t width;
  uint8_t height;
  uint8_t data[];
} font_t;

const uint8_t font_d3[] = {
  #include "fonts/d3.txt"
};


static font_t *findChar( char ch, font_t *font, int font_sz ) {
  if ( font && font_sz ) {
    uint8_t *p = (uint8_t*)font; 
    do {
      font_t *f = (font_t*)p;
      printf( "f:%p a:%x w:%d h:%d\n", f, f->ascii, f->width, f->height );
      if ( f->ascii == ch ) {
        return f;
      }
      p += sizeof(font_t) + (f->width * f->height);
    } while ( p < (uint8_t*)font + font_sz );
  }
  return NULL;
}

uint8_t displayChar(char ch, uint8_t x0, uint8_t y0) {
  printf("findChar:%c ...",ch);
  font_t *font = findChar(ch, (font_t*)font_d3, sizeof(font_d3) );
  printf("%p\n",font_d3);
  if ( font ) {
    for (int x=0; x<font->width; x++) {
        for (int y=0; y<font->height; y++) {
            int color = font->data[ (y*font->height) + x ];
            is31fl3731DrawPixel( x0+x, y0+y, color );
        }
    }
    return font->width;
  }
  return 0;
}

void displayText(char *text) {
    printf("displayText.strlen:%d\n", (int)strlen(text));
    frame = !frame;
    printf("displayText.frame:%d\n", frame);
    
    is31fl3731SetFrame( frame );
    is31fl3731Clear();
    
    // int width = 0;
    // for (int i=0; i<strlen(text); i++) {
    //   font_t *f = findChar(text[i], (font_t*)font_d3, sizeof(font_d3));
    //   width += f->width + 1;
    // }
    // int y0 = 2;        
    // int x0 = (17/2) - (width/2);
    // if ( x0 < 0 ) { x0 = 0; }

    int y0 = 1;
    int x0 = 0;
    
    for (int i=0; i<strlen(text); i++) {
      x0 += displayChar( text[i], x0, y0 ) + 1;
    }
    
    is31fl3731DisplayFrame( frame );
}

void displayScore(int score) {
    static int total = 0;
    if ( score ) {
        total += score;
    } else {
        total = 0;
    }
    char s[10] = {0,};
    snprintf( s, sizeof(s)-1, "%d", total );
    displayText( s );
}

void displayBall(int ball) { 
}

void displayInit(void) {
    printf("displayInit()\n");
    is31fl3731Init(); 
    displayText("helo");
}

