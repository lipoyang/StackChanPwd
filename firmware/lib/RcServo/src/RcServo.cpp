#include <RcServo.h>

// pulth width = 0.5ms to 2.5ms (neutral position = 1.5ms)
#define PULSE_MIN  102 // 102/4096 * 20ms = 0.5ms
#define PULSE_MAX  512 // 512/4096 * 20ms = 2.5ms

// begin the RC servo driver
void RcServo::begin()
{
    // setup PCA9685 PWM driver
    Pwm.begin();
    Pwm.setPWMFreq(50);  // cycle = 20msec
}

// set initial position
void RcServo::setInitialPosition(int ch, int value)
{
    RcServo::out(ch, value);
    Position[ch] = value;
    TargetPosition[ch] = value;
}

// set target position
void RcServo::setTargetPosition(int ch, int value)
{
    // set target position
    TargetPosition[ch] = value;
}

// set position
void RcServo::setPosition(int ch, int value)
{
    // set target position
    TargetPosition[ch] = value;
    Position[ch] = value;
    out(ch, value);
}

// control loop
void RcServo::control(int ch)
{
    // if target position is not equal to current position
    if (TargetPosition[ch] != Position[ch]) {
        int diff = TargetPosition[ch] - Position[ch];
        if (diff > 1 || diff < -1) {
            Position[ch] += (diff > 0) ? 1 : -1;
            out(ch, Position[ch]);
        }
    }
}

// control the servo
// ch: channel
// value: output value (-90 to +90 [deg])
void RcServo::out(int ch, int value)
{
    // convert (-90,+90)[deg] -> (0,180)[deg] with offset and polarity
    uint32_t deg = 90 + Offset[ch] + Polarity[ch] * value;
    // convet deg value -> timer count value
    uint16_t cnt = PULSE_MIN + (uint16_t)(deg*(PULSE_MAX-PULSE_MIN)/180);

    Pwm.setPWM(ch, 0, cnt);
}

// set polarity
// ch: channel
// polarity: polarity of output (+1 or -1)
void RcServo::setPolarity(int ch, int polarity)
{
    Polarity[ch] = polarity;
}

// set offset
// ch: channel
// offset: offset of output
void RcServo::setOffset(int ch, int offset)
{
    Offset[ch] = offset;
}

// get polarity
int* RcServo::getPolarity()
{
    return Polarity;
}

// get offset
int* RcServo::getOffset()
{
    return Offset;
}
