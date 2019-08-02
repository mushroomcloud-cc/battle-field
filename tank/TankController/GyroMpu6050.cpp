#include "GyroMpu6050.h"
#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

GyroMpu6050 *instance;

void dmpDataReady()
{
    instance->mpuInterrupt = true;
}
MPU6050 mpu;
Quaternion q;        // [w, x, y, z]         quaternion container
VectorInt16 aa;      // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity; // [x, y, z]            gravity vector

GyroMpu6050::GyroMpu6050(/* args */)
{
}

GyroMpu6050::~GyroMpu6050()
{
}

void GyroMpu6050::setup()
{
    instance = this;

    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    this->connected = mpu.testConnection();
    // load and configure the DMP
    devStatus = mpu.dmpInitialize();

    mpu.setXGyroOffset(54);
    mpu.setYGyroOffset(-63);
    mpu.setZGyroOffset(41);
    mpu.setZAccelOffset(1301); // use IMU-ZERO to get the offsets
    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        error = true;
    }
}

void GyroMpu6050::update()
{
    // if programming failed, don't try to do anything

    // wait for MPU interrupt or extra packet(s) available
    // while (!mpuInterrupt && fifoCount < packetSize)
    // {
    //     if (mpuInterrupt && fifoCount < packetSize)
    //     {
    //         // try to get out of the infinite loop
    //         fifoCount = mpu.getFIFOCount();
    //     }
    // }

    if (!mpuInterrupt)
    {
        return;
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024)
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        fifoCount = mpu.getFIFOCount();

        // otherwise, check for DMP data ready interrupt (this should happen frequently)
    }
    else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT))
    {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize)
            fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);

        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        yaw = ypr[0] * 180 / M_PI;
        pitch = ypr[1] * 180 / M_PI;
        roll = ypr[2] * 180 / M_PI;
    }
}
