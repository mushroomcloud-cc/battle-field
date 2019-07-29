#pragma once
#include "Arduino.h"

class TB6612Drive
{
public:
    /* data */
    int speedValue = 0;
    int rightMotor_dir = D6;
    int rightMotor_pwm = D7;
    int leftMotor_dir = D8;
    int leftMotor_pwm = D9;

public:
    TB6612Drive(/* args */);
    ~TB6612Drive();
    void setup();
    void setup(int RightMotorDirPin,int RightMotorPwmPin,int LeftMotorDirPin,int LeftMotorPwmPin);
    void forward(int speedValue);
    void backward(int speedValue);
    void right(int speedValue);
    void left(int speedValue);
    void stop();
};
