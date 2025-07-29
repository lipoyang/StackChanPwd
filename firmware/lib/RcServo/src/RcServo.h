#pragma once

#include <Adafruit_PWMServoDriver.h>

// total number of servos
#define SERVO_NUM  16

// RC servo driver class
class RcServo
{
public:
    // begin the RC servo driver
    void begin();
    // set polarity
    void setPolarity(int ch, int polarity);
    // set offset
    void setOffset(int ch, int offset);
    // get polarity
    int* getPolarity();
    // get offset
    int* getOffset();
    // set initial position
    void setInitialPosition(int ch, int value);
    // set target position
    void setTargetPosition(int ch, int value);
    // set position
    void setPosition(int ch, int value);
    // control loop
    void control(int ch);

private:
    // control the servo
    void out(int ch, int value);
    
private:
    Adafruit_PWMServoDriver Pwm;// PCA9685 PWM driver
    int Polarity[SERVO_NUM];    // polarity of servos
    int Offset[SERVO_NUM];      // offset of servos
    int Position[SERVO_NUM];        // current position of servos
    int TargetPosition[SERVO_NUM];  // target position of servos
};

