/*
 Vex.h
 - Library for EG1003 VEX robots SLDP.
 - This library is meant for use with the Motor Driver.
 - All sensors are added.
*/

#ifndef Vex_h
#define Vex_h

#include "Arduino.h"
#include "Adafruit_MotorShield.h"
#include "MPU6050.h"
#include "Wire.h"
class Touch {
public:
    // Touch class constructor
    Touch(int pinNum);
    // REQUIRED in setup function
    void begin(); // Touch is supposed to
    // function to see if touch sensor is pushed
    bool isPushed();
private:
    const int touchPin;
};

class Ultrasonic {
public:
    // Ultrasonic class constructor
    Ultrasonic(int pinNum1, int pinNum2);
    // REQUIRED in setup function
    void begin(); // Ultrasonic is supposed to
    // return current distance
    long checkUltrasonic();
private:
    const int trigPin;
    const int echoPin;
};

class Gyro {
public:
    // REQUIRED in setup function
    void begin(); // Gyro is supposed to
    // Value getters
    float getZAngle();
    float getYAngle();
    float getXAngle();
    // function to get gyro values
protected:
    bool getEulerAngles();
private:
    // MPU object
    MPU6050 mpu;

    // MPU control/status vars
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    // orientation/motion vars
    Quaternion q;           // [w, x, y, z]         quaternion container
    VectorFloat gravity;    // [x, y, z]            gravity vector
    float euler[3];         // [psi, theta, phi]    Euler angle container
};

class IRObstacle{
public:
  IRObstacle(int digitalPin);
  void begin(); //begin method for setup 
  bool isObstacle();
private:
  int pin; //digital pin
 
};
	

class Vex {
public:
    Vex();
    Adafruit_DCMotor* setMotor(int num);
    void begin();
    void end();
    void moveMotor(Adafruit_DCMotor *motor, double power, double time);
    void moveTank(Adafruit_DCMotor *motor1, Adafruit_DCMotor *motor2, double motor1power, double motor2power, double time);
protected:
    void setDirectionMotor(Adafruit_DCMotor* motor, double power);
    void setDirectionTank(Adafruit_DCMotor* motor1, Adafruit_DCMotor* motor2, double motor1power, double motor2power);
private:
    Adafruit_MotorShield AFMS;
};

#endif
