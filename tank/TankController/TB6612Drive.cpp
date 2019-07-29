#include "TB6612Drive.h"
#include <analogWrite.h>

TB6612Drive::TB6612Drive()
{
}

TB6612Drive::~TB6612Drive()
{
}

void TB6612Drive ::setup(int RightMotorDirPin, int RightMotorPwmPin, int LeftMotorDirPin, int LeftMotorPwmPin)
{
    rightMotor_dir = RightMotorDirPin;
    rightMotor_pwm = RightMotorPwmPin;
    leftMotor_dir = LeftMotorDirPin;
    leftMotor_pwm = LeftMotorPwmPin;
    pinMode(rightMotor_dir, OUTPUT);
    pinMode(leftMotor_dir, OUTPUT);
}

void TB6612Drive::setup()
{
    pinMode(rightMotor_dir, OUTPUT);
    pinMode(leftMotor_dir, OUTPUT);
}

void TB6612Drive::forward(int speedValue)
{
    digitalWrite(rightMotor_dir, HIGH);
    digitalWrite(leftMotor_dir, HIGH);
    analogWrite(rightMotor_pwm, speedValue);
    analogWrite(leftMotor_pwm, speedValue);
}

void TB6612Drive::backward(int speedValue)
{
    digitalWrite(rightMotor_dir, LOW);
    digitalWrite(leftMotor_dir, LOW);
    analogWrite(rightMotor_pwm, speedValue);
    analogWrite(leftMotor_pwm, speedValue);
}

void TB6612Drive::left(int speedValue)
{
    digitalWrite(rightMotor_dir, HIGH);
    digitalWrite(leftMotor_dir, LOW);
    analogWrite(rightMotor_pwm, speedValue);
    analogWrite(leftMotor_pwm, speedValue);
}

void TB6612Drive::right(int speedValue)
{
    digitalWrite(rightMotor_dir, LOW);
    digitalWrite(leftMotor_dir, HIGH);
    analogWrite(rightMotor_pwm, speedValue);
    analogWrite(leftMotor_pwm, speedValue);
}

void TB6612Drive::stop()
{
    digitalWrite(rightMotor_dir, HIGH);
    digitalWrite(leftMotor_dir, HIGH);
    analogWrite(rightMotor_pwm, 0);
    analogWrite(leftMotor_pwm, 0);
}
