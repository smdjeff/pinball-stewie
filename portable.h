#ifndef _PORTABLE_H_
#define _PORTABLE_H_

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

