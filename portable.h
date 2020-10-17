#ifndef _PORTABLE_H_
#define _PORTABLE_H_

//////////////////////////////////////////////////////////////////////////
// arbitrary connections of stewie pinball machine to raspberry pi io
    
#define SOLENOID_FLIPPER_LEFT    4
#define SOLENOID_FLIPPER_RIGHT   17
#define SOLENOID_SHOOTER         27
#define LAMP_PLAYFIELD           22
#define LAMP_SHOOT_AGAIN         5    

#define SWITCH_START             10
#define SWITCH_FLIPPER_LEFT      11
#define SWITCH_FLIPPER_RIGHT     9    
#define SWITCH_LOIS              23
#define SWITCH_MEG               24
#define SWITCH_PETER             25
#define SWITCH_SHOOTER           8
#define SWITCH_BRIAN_CHRIS       12
#define SWITCH_CHRIS_BRIAN       16    
#define SWITCH_DRIVE_SIGNAL      7
    
#define LED_MATRIX_CLK           6
#define LED_MATRIX_D0_7          MCP23017_A0_7

#define MCP23017_SDA             2
#define MCP23017_SCL             3
    
#define DISPLAY_SDA              2
#define DISPLAY_SCL              3
    
#define AUDIO_PCM_FS             19    
#define AUDIO_PCM_CLK            18    
#define AUDIO_PCM_DOUT           21    
 

    
///////////////////////////////////////////////////////////////////////////
// poorman's hardware abstraction layer 
// allowing this code to be built on a desktop
// basically just a pigpio lib that debug outputs to stdio
// rather than real hardware

#ifdef RASPBERRYPI
  
  #include <pigpio.h> // http://abyz.me.uk/rpi/pigpio/
  
#else

#define PI_INPUT 0
#define PI_OUTPUT 1
#define PI_PUD_OFF  0
#define PI_PUD_DOWN 1
#define PI_PUD_UP   2

typedef void (*gpioTimerFunc_t)    (void);
typedef void (*gpioAlertFunc_t)    (int      gpio,
                                    int      level,
                                    uint32_t tick);
int gpioInitialise(void);
int gpioSetMode(unsigned gpio, unsigned mode);
int gpioSetTimerFunc(unsigned timer, unsigned millis, gpioTimerFunc_t f);
int gpioSetAlertFunc(unsigned user_gpio, gpioAlertFunc_t f);
int gpioWrite(unsigned gpio, unsigned level);
int gpioRead(unsigned gpio);
int gpioSetPullUpDown(unsigned gpio, unsigned pud);
int gpioPWM(unsigned user_gpio, unsigned dutycycle);
int i2cWriteByteData(unsigned handle, unsigned i2cReg, unsigned bVal);
int i2cOpen(unsigned i2cBus, unsigned i2cAddr, unsigned i2cFlags);

#endif

#endif // _PORTABLE_H_

