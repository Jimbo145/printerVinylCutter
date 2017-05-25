#ifndef _PRINTERCUTTER_H
#define _PRINTERCUTTER_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t millis_t;

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#undef min
#undef max


#define ENCODERY_PIN_A 2
#define ENCODERY_PIN_B 3
#define MOTORY_PIN_PWM 13
#define MOTORY_PIN_DIR0 38
#define MOTORY_PIN_DIR1 40

#define ENCODERX_PIN_A 18
#define ENCODERX_PIN_B 19
#define MOTORX_PIN_PWM (12)
#define MOTORX_PIN_DIR0 (42)
#define MOTORX_PIN_DIR1 (44)

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48

#define END_STOP_PIN 53

#define STEP_PIN 22

#define MOTORX 0
#define MOTORY 1

#define FORWARD 1
#define BACKWARD 2
#define STOP 0

#define MAX_X_LENGTH 14700
#define Y_STEPS_PER_MM 70
#define X_STEPS_PER_MM 6
#define Z_STEPS_PER_MM 4
#define XSPEED 255
#define YSPEED 255

#define Z_DOWN 33
#define Z_UP 30

#define UNUSED -999999

class RMath
{
public:
    static inline float min(float a,float b)
    {
        if(a < b) return a;
        return b;
    }
    static inline float max(float a,float b)
    {
        if(a < b) return b;
        return a;
    }
    static inline int32_t min(int32_t a,int32_t b)
    {
        if(a < b) return a;
        return b;
    }
    static inline int32_t min(int32_t a,int32_t b, int32_t c)
    {
        if(a < b) return a < c ? a : c;
        return b<c ? b : c;
    }
    static inline float min(float a,float b, float c)
    {
        if(a < b) return a < c ? a : c;
        return b < c ? b : c;
    }
    static inline int32_t max(int32_t a,int32_t b)
    {
        if(a < b) return b;
        return a;
    }
    static inline int min(int a,int b)
    {
        if(a < b) return a;
        return b;
    }
    static inline uint16_t min(uint16_t a,uint16_t b)
    {
        if(a < b) return a;
        return b;
    }
    static inline int16_t max(int16_t a,int16_t b)
    {
        if(a < b) return b;
        return a;
    }
    static inline uint16_t max(uint16_t a,uint16_t b)
    {
        if(a < b) return b;
        return a;
    }
    static inline unsigned long absLong(long a)
    {
        return a >= 0 ? a : -a;
    }
    static inline int32_t sqr(int32_t a)
    {
        return a*a;
    }
    static inline uint32_t sqr(uint32_t a)
    {
        return a*a;
    }
    static inline float sqr(float a)
    {
        return a*a;
    }
};

#include "serial.h"
#include "gcode.h"
#include "motor.h"
#include "Commands.h"


#endif

