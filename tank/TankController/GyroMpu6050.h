#pragma once
#include "Arduino.h"
#define INTERRUPT_PIN D3

class GyroMpu6050
{
public:
    // MPU control/status vars
    bool dmpReady = false; // set true if DMP init was successful
    bool error = false;
    bool connected = false;
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer

    float euler[3]; // [psi, theta, phi]    Euler angle container
    float ypr[3];   // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    float yaw = 0;
    float pitch = 0;
    float roll = 0;

    // packet structure for InvenSense teapot demo
    uint8_t teapotPacket[14] = {'$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n'};

    volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high

public:
    GyroMpu6050(/* args */);
    ~GyroMpu6050();
    void setup();
    void update();
    void getFIFOCount();
};
