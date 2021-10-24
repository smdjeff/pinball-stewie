#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "hardware/sync.h"
#include "hardware/watchdog.h"

#include "../portable.h"

// portability layer, making the raspberrypi pico fit the pigpio api from regular pi

static int64_t halt_alarm(alarm_id_t id, void *user_data) {
  watchdog_enable(100,false);
  for (;;) { __wfi(); };
}

void haltPico(void) {
  // delay for stdio flush
  add_alarm_in_ms( 1000, halt_alarm, 0/*user_data*/, true/*fire_if_past*/ );
}
    
int usleep(useconds_t usec) {
    sleep_us( usec );
}

int gpioInitialise(void) { 
    stdio_init_all();
    usleep(1000* 5000);
    printf("pico booted\n");
    return 0; 
}

int gpioSetMode(unsigned gpio, unsigned mode) { 
    gpio_init( gpio );
    gpio_set_dir( gpio, mode );
    return 0; 
}

static struct repeating_timer timers[10] = {0,};

static bool repeating_timer_callback(struct repeating_timer *t) {
    // extra call accounts for differing callback prototype
    assert( t );
    gpioTimerFunc_t f = t->user_data;
    assert( f );
    f( );
    return true;
}

int gpioSetTimerFunc(unsigned timer, unsigned millis, gpioTimerFunc_t f) {
    bool success = false;
    assert( timer < sizeof(timers)/sizeof(timers[0]) );
    if ( millis ) {
      success = add_repeating_timer_ms( millis, repeating_timer_callback, f/*userdata*/, &timers[timer] );
      printf("add_repeating_timer_ms:%d %d\n", success, timers->alarm_id);
    } else {
      success = cancel_repeating_timer( &timers[timer] );
    }
    return (success == true)? 0 : 1; // error = 0 == success
}

typedef struct {
    alarm_id_t id;
    uint32_t events;
    uint steady;
    uint gpio;
    gpioAlertFunc_t callback;
} glitch_t;
static glitch_t glitches[32] = {0,};

#define PICO_GPIO_EVENT_LEVEL_LOW   (1<<0)
#define PICO_GPIO_EVENT_LEVEL_HIGH  (1<<1)
#define PICO_GPIO_EVENT_EDGE_LOW    (1<<2)
#define PICO_GPIO_EVENT_EDGE_HIGH   (1<<3)

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    glitch_t* glitch = user_data;
    glitch->id = 0;
    if ( glitch->callback ) {
        int level = -1;
        if ( glitch->events & PICO_GPIO_EVENT_EDGE_HIGH ) {
            if ( gpio_get( glitch->gpio ) != 0 ) {
                level = RISING_EDGE;
            }
        }
        if ( glitch->events & PICO_GPIO_EVENT_EDGE_LOW ) {
            if ( gpio_get( glitch->gpio ) == 0 ) {
                level = FALLING_EDGE;
            }
        }
        glitch->callback( glitch->gpio, level, 0/*tick*/ );
    }
    return 0; //no auto-reschedule
}

void gpio_callback(uint gpio, uint32_t events) {
    glitch_t* glitch = &glitches[gpio];
    glitch->events = events;
    if ( glitch->id > 0 ) {
        bool success = cancel_alarm( glitch->id );
        assert( success );
    }
    glitch->id = add_alarm_in_us( glitch->steady, alarm_callback, &glitches[gpio]/*user_data*/, true/*fire_if_past*/ );
    assert ( glitch->id > 0 );
}

int gpioSetAlertFunc(unsigned gpio, gpioAlertFunc_t f) {
    glitch_t* glitch = &glitches[gpio];
    if ( f ) {
        glitch->callback = f;
        glitch->gpio = gpio;
        gpio_set_irq_enabled_with_callback( gpio, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true/*enable*/, &gpio_callback);
    } else {
        memset( glitch, 0x00, sizeof(glitch_t) );
    }
    return 0;
}

int gpioGlitchFilter(unsigned gpio, unsigned steady) {
    glitch_t* glitch = &glitches[gpio];
    glitch->steady = steady;
    return 0;
}

void* gpioStartThread(gpioThreadFunc_t f, void *userdata) {
    return 0;
}

int gpioWrite(unsigned gpio, unsigned level) {
    gpio_set_function( gpio, GPIO_FUNC_SIO );
    gpio_put( gpio, level );
    return 0; 
}

int gpioRead(unsigned gpio) {
    return gpio_get( gpio );
}

int gpioSetPullUpDown(unsigned gpio, unsigned pud) { 
    switch ( pud ) {
      case PI_PUD_OFF:
        gpio_disable_pulls( gpio ); 
        break;
      case PI_PUD_DOWN:
        gpio_pull_down( gpio );
        break;
      case PI_PUD_UP:
        gpio_pull_up( gpio );
        break;
      default: assert( false );
    }
    return 0; 
}

int gpioPWM(unsigned gpio, unsigned dutycycle) {
    gpio_set_function( gpio, GPIO_FUNC_PWM );
    pwm_set_gpio_level( gpio, dutycycle );
    return 0; 
}

int gpioSetPWMfrequency(unsigned gpio, unsigned frequency) {
    pwm_set_wrap( pwm_gpio_to_slice_num( gpio ), 255);
    pwm_set_enabled( pwm_gpio_to_slice_num( gpio ), true );
    return 0;
}

int gpioGetPWMfrequency(unsigned gpio) {
    return 0;
}

int gpioCfgClock(unsigned micros, unsigned peripheral, unsigned source) {
    return 0;
}

static uint8_t myAddr[2] = {0,};

static i2c_inst_t* i2cHandle(unsigned id) {
  switch ( id ) {
    case 0: return( i2c0 );
    case 1: return( i2c1 );
    default: assert( false );
  }
  return 0;
}

int i2cWriteByteData(unsigned id, unsigned i2cReg, unsigned bVal) {
    const uint8_t byte = bVal;
    printf("i2c_write_blocking id:%d handle:%p addr:%x\n", id, i2cHandle(id), myAddr[id]);
    int ret = i2c_write_blocking(	i2cHandle(id), myAddr[id], &byte, 1/*len*/, false/*nostop*/ );
    if ( ret < sizeof(byte) ) {
        assert( ret != PICO_ERROR_GENERIC );
    }
    return ret; 
}

int i2cOpen(unsigned id, unsigned addr, unsigned i2cFlags) { 
    const uint baud = 100e3;
    //const uint baud = 400e3;
    // const uint baud = 1700e3;
    int ret = i2c_init(	i2cHandle(id), baud );
    printf("i2c_init ret:%d id:%d handle:%p addr:%x\n", ret, id, i2cHandle(id), addr); // mux=0x20
    assert( ret > baud * 0.99 && ret < baud * 1.01 );
    myAddr[ id ] = addr;
    
    uint8_t sda;
    uint8_t scl;
    switch ( id ) { 
      case 0:
        sda = MCP23017_SDA;   // i2c0_sda
        scl = MCP23017_SCL;   // i2c0_scl
        break;
      case 1:
        sda = DISPLAY_SDA;   // i2c1_sda
        scl = DISPLAY_SCL;   // i2c1_scl
        break;
      default: assert( false );
    }
    gpio_set_function( sda, GPIO_FUNC_I2C );
    gpio_set_function( scl, GPIO_FUNC_I2C );
    gpio_pull_up( sda );
    gpio_pull_up( scl );
    printf("i2copen:%d\n",id);
    return id; 
}

