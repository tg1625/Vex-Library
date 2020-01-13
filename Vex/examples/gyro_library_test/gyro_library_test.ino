/*
 * GYRO_TEST.INO
 * 
 * This code is a test for the gyro sensor with the VEX library. 
 * It will print out the X,Y, and Z Euler Angles
 * This is useful for trouhleshooting any problems with the gyro sensor
 */
#include <Vex.h>

Gyro g; //create a gyro object

//angle variables used to get sensor values
float angleX;
float angleY;
float angleZ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //start up serial monitor
  while (!Serial);
  Serial.println("Gyro Class Test");
  g.begin(); //start up gyro sensor
}

void loop() {
  // put your main code here, to run repeatedly:
  angleZ = g.getZAngle(); //angle about Z axis
  angleY = g.getYAngle(); //angle about Y axis
  angleX = g.getXAngle(); //angle about X axis
  Serial.print("Angle: z: ");
  Serial.print(angleZ);
  Serial.print(" y:  ");
  Serial.print(angleY);
  Serial.print(" x:  ");
  Serial.print(angleX);
  Serial.println(" / ");
  delay(1000);
}
