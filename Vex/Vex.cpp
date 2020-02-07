/*
 Vex.cpp
 - Library for EG1003 VEX robots SLDP.
 - This library is meant for use with the Motor Driver.
 - All sensors are added.
*/

#include "VEX.h"


//Constructor
Vex::Vex() {
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
}

//Method to start the motor shield
void Vex::begin() {
    AFMS.begin();
}

//Method to stop to robot indefinitely
void Vex::end() {
    while (1 == 1) {
        delay(1000);
    }
}

//Method to set up the motors
Adafruit_DCMotor* Vex::setMotor(int num) {
    return AFMS.getMotor(num);
}

//Protected method to set the direction of a motor
void Vex::setDirectionMotor(Adafruit_DCMotor *motor, double power) {
    if (power >= 0) {
        motor->run(FORWARD);
    }
    else {
        motor->run(BACKWARD);
    }
}

//Protected method to set the direction of two motors
void Vex::setDirectionTank(Adafruit_DCMotor *motor1, Adafruit_DCMotor *motor2, double motor1power, double motor2power) {
    if (motor1power >= 0 && motor2power >= 0) { //both forward
        motor1->run(FORWARD);
        motor2->run(FORWARD);
    }
    else if (motor1power >= 0 && motor2power <= 0) { //motor 1 forward, motor 2 backward
        motor1->run(FORWARD);
        motor2->run(BACKWARD);
    }
    else if (motor2power >= 0 && motor1power <= 0) {//motor2 forward, motor 1 backward
        motor1->run(BACKWARD);
        motor2->run(FORWARD);
    }
    else { //both backward
        motor1->run(BACKWARD);
        motor2->run(BACKWARD);
    }
}


//Single motor control
void Vex::moveMotor(Adafruit_DCMotor* motor, double power, double time) {
    Serial.println("Writing motor");
    //set speed of motor, map power value between 0 and 255
    motor->setSpeed(map(abs(power), 0, 100, 0, 255));
    //set direction, motor will start to move
    setDirectionMotor(motor, power);
    //converts time (seconds) to milliseconds, will run motor for this time
    delay(time * 1000);
    //turn off motor
    motor->run(RELEASE);
}
//Dual motor control
void Vex::moveTank(Adafruit_DCMotor* motor1, Adafruit_DCMotor* motor2, double motor1power, double motor2power, double time) {
    Serial.println("Writing tank");
    //set speed of motor, map power value between 0 and 255
    motor1->setSpeed(map(abs(motor1power), 0, 100, 0, 255));
    motor2->setSpeed(map(abs(motor2power), 0, 100, 0, 255));
    //set direction for both, motors will start to move
    setDirectionTank(motor1, motor2, motor1power, motor2power);
    //converts time (seconds) to milliseconds, will run motor for this time
    delay(time * 1000);
    //turn off motor
    motor1->run(RELEASE);
    motor2->run(RELEASE);
}

/*
Gyro Class
- class for getting Euler angle values from the MPU 6050 sensor

*/

volatile bool mpuInterrupt = false;
////method for mpuInterrupt, needed to attach the interrupt
void dmpDataReady() {
    mpuInterrupt = true;
}


//REQUIRED in setup function
void Gyro::begin() {
    //join I2C bus
    Wire.begin();
    Wire.setClock(400000);
    //initialize device
    mpu.initialize();
    pinMode(2, INPUT);
    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);
        // enable Arduino interrupt detection
        digitalPinToInterrupt(2);
        attachInterrupt(digitalPinToInterrupt(2), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print("DMP Failed to Initialize with code: ");
        Serial.println(devStatus);
    }
}

//Value getter
float Gyro::getZAngle() {
    while (!getEulerAngles());
    return (euler[0] * 180 / M_PI);
}

float Gyro::getYAngle() {
    while (!getEulerAngles());
    return (euler[1] * 180 / M_PI);
}

float Gyro::getXAngle() {
    while (!getEulerAngles());
    return (euler[2] * 180 / M_PI);
}

//function to get gyro values
bool Gyro::getEulerAngles() {
    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
            // try to get out of the infinite loop
            fifoCount = mpu.getFIFOCount();
        }
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
    if (fifoCount < packetSize) {
        //Lets go back and wait for another interrupt. We shouldn't be here, we got an interrupt from another event
        // This is blocking so don't do it   while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    }
    // check for overflow (this should never happen unless our code is too inefficient)
    else if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        // otherwise, check for DMP data ready interrupt (this should happen frequently)
    }
    else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT)) {
        // read a packet from FIFO
        while (fifoCount >= packetSize) { // Lets catch up to NOW, someone is using the dreaded delay()!
            mpu.getFIFOBytes(fifoBuffer, packetSize);
            // track FIFO count here in case there is > 1 packet available
            // (this lets us immediately read more without waiting for an interrupt)
            fifoCount -= packetSize;
        }
        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetEuler(euler, &q);
        return true;
    }
    return false;
}

// Touch class constructor
Touch::Touch(int pinNum):
touchPin(pinNum)
{}

// Touch is supposed to
void Touch::begin() {
    Serial.println("Starting up Touch");
    pinMode(touchPin, INPUT_PULLUP);
}

// function to see if touch sensor is pushed
bool Touch::isPushed() {
    int buttonState = digitalRead(touchPin);
    if (buttonState == 1) {
        delay(100);
        return false;
    }
    Serial.println("Pushed");
    return true;
}

// Ultrasonic class constructor
Ultrasonic::Ultrasonic(int pinNum1, int pinNum2):
trigPin(pinNum1), echoPin(pinNum2)
{}

// Ultrasonic is supposed to
void Ultrasonic::begin() {
    Serial.println("Starting up Ultrasonic");
    // initialize the pulse pin as output:
    pinMode(trigPin, OUTPUT);
    // initialize the echo pin as an input:
    pinMode(echoPin, INPUT);
}

// return current distance
long Ultrasonic::checkUltrasonic() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long distance = pulseIn(echoPin,HIGH);
    distance = distance*(171.5/pow(10,4));
    Serial.println("Centimeters:  ");
    Serial.println(distance, DEC);
    delay(500);
    return distance;
}

/*
IRObstacle
- class for the IR Obstacle Avoidance sensor
*/

IRObstacle::IRObstacle(int digitalPin) : pin(digitalPin){}
void IRObstacle::begin(){
pinMode(pin,INPUT);
}
bool IRObstacle::isObstacle(){
 if (digitalRead(pin) == LOW){
   return true;
 }
 return false;
}

