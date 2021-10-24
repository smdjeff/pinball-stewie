#ifndef _PORTABLE_H_
#define _PORTABLE_H_

//////////////////////////////////////////////////////////////////////////
// arbitrary connections of stewie pinball machine to raspberry pi io

#define SERIAL_TX                0    // uart0_tx
#define SERIAL_RX                1    // uart0_rx
#define SWITCH_FLIPPER_LEFT      2
#define SWITCH_START             3
#define SWITCH_FLIPPER_RIGHT     4
#define SWITCH_SHOOTER           5
#define SOLENOID_FLIPPER_LEFT    6
#define SOLENOID_FLIPPER_RIGHT   7
#define SOLENOID_SHOOTER         8
#define LAMP_PLAYFIELD           9
#define LAMP_SHOOT_AGAIN         10
#define LED_MATRIX_CLK           11    // MCP23017
#define GPIO_UNUSED_12           12
#define GPIO_UNUSED_13           13
#define DISPLAY_SDA              14   // i2c1_sda
#define DISPLAY_SCL              15   // i2c1_scl
#define GPIO_UNUSED_16           16
#define SWITCH_CHRIS_BRIAN       17
#define SWITCH_BRIAN_CHRIS       18
#define SWITCH_DRIVE_SIGNAL      19
#define MCP23017_SDA             20   // i2c0_sda
#define MCP23017_SCL             21   // i2c0_scl
#define SWITCH_PETER             22
#define GPIO_NA_23               23
#define GPIO_NA_24               24
#define PICO_LED                 25   // built in LED
#define SWITCH_MEG               26  
#define SWITCH_LOIS              27
#define GPIO_UNUSED_28           28

// https://github.com/joan2937/pigpio/issues/397
#define gpioCancelTimer(t) gpioSetTimerFunc(t,PI_MIN_MS,0)
#define deferredTimers()    do {} while(0)

#define TIMER_LEFT_FLIP     0
#define TIMER_RIGHT_FLIP    1
#define TIMER_MATRIX        2
#define TIMER_BLINK         3
#define TIMER_ATTRACT       4
#define TIMER_SHOOTER       5
#define TIMER_6             6
#define TIMER_7             7
#define TIMER_8             8
#define TIMER_9             9
    


    
///////////////////////////////////////////////////////////////////////////
// poorman's hardware abstraction layer 
// 
// basically a pigpio compliant api that allows for all 3 of the following targets:
//
// 1. raspberry pi
// 2. desktop (hardware is just stdio)
// 3. pi pico


#if defined( RASPBERRY )
  
    // we're using the real PiGpio C library
    #include <pigpio.h> // http://abyz.me.uk/rpi/pigpio/

#else 

    // we're using a local compliant glue layer
    // desktop or pico

    #if defined( RASPBERRY_PICO )

        #include "pico/stdlib.h" // defs RASPBERRYPI_PICO
        void haltPico(void);

        #undef deferredTimers
        void deferredTimers(void);

    #endif

    #define PI_MIN_MS    0
    #define PI_INPUT     0
    #define PI_OUTPUT    1
    #define PI_PUD_OFF   0
    #define PI_PUD_DOWN  1
    #define PI_PUD_UP    2
    #define RISING_EDGE  0
    #define FALLING_EDGE 1
        

    typedef void (*gpioTimerFunc_t)    (void);
    typedef void (*gpioAlertFunc_t)    (int gpio, int level, uint32_t tick);
    typedef void *(gpioThreadFunc_t)   (void*);

    int gpioCfgClock(unsigned micros, unsigned peripheral, unsigned source);
    int gpioInitialise(void);
    void* gpioStartThread(gpioThreadFunc_t f, void *userdata);
    int gpioSetMode(unsigned gpio, unsigned mode);
    int gpioSetTimerFunc(unsigned timer, unsigned millis, gpioTimerFunc_t f);
    int gpioSetAlertFunc(unsigned user_gpio, gpioAlertFunc_t f);
    int gpioGlitchFilter(unsigned user_gpio, unsigned steady);
    int gpioWrite(unsigned gpio, unsigned level);
    int gpioRead(unsigned gpio);
    int gpioSetPullUpDown(unsigned gpio, unsigned pud);
    int gpioPWM(unsigned user_gpio, unsigned dutycycle);
    int gpioSetPWMfrequency(unsigned gpio, unsigned frequency);
    int gpioGetPWMfrequency(unsigned gpio);
    int i2cWriteByteData(unsigned handle, unsigned i2cReg, unsigned bVal);
    int i2cOpen(unsigned i2cBus, unsigned i2cAddr, unsigned i2cFlags);

#endif

#endif // _PORTABLE_H_

// pico sdk's assert leaves something to be desired, so...
#if defined( RASPBERRY_PICO )
  #undef assert
  #define assert(condition) if (!(condition)) { printf("assert %s line %d\n", __FILE__, __LINE__); haltPico(); }
#endif


