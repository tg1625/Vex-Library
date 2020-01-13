/*
	Movement Test for the VEX Robot with the Motor Shield
	
*/

#include <Vex.h>

////Declare Vex object named Robot
Vex Robot;

//Create motor objects
Adafruit_DCMotor *motorA = Robot.setMotor(1);
Adafruit_DCMotor *motorB = Robot.setMotor(2);
Adafruit_DCMotor *motorC = Robot.setMotor(3);
Adafruit_DCMotor *motorD = Robot.setMotor(4);


void setup()
{
	//set up the serial monitor
	Serial.begin(9600);
	Serial.println("Movement Test for the VEX Robot");
  //start up the robot
  Robot.begin();
  delay(5000);
}


void loop()
{
  //forward
  Serial.println("Moving forward");
  Robot.moveTank(motorA, motorB, 100, 100, 1);
  //backward
  Serial.println("Moving Backwards");
  Robot.moveTank(motorA, motorB, -100, -100, 1);
  //right swing turn
  Serial.println("Right Swing Turn");
  Robot.moveMotor(motorA, 100, 1);
  //left swing turn
  Serial.println("Left Swing Turn");
  Robot.moveMotor(motorB, 100, 1);
  //right point turn
  Serial.println("Right point turn");
  Robot.moveTank(motorA, motorB, 100, -100, 1);
  //left point turn
  Serial.println("Left point turn");
  Robot.moveTank(motorA, motorB, -100, 100, 1);
  //lift claw
  Serial.println("Claw lift");
  Robot.moveMotor(motorC,80,1);
  //lower claw
  Serial.println("Claw lower");
  Robot.moveMotor(motorC,-80,1);
  //open claw
  Serial.println("Open Claw");
  Robot.moveMotor(motorD,80,1);
  //close claw
  Serial.println("Close Claw");
  Robot.moveMotor(motorD,-80,1);
  //finish
  Serial.println("Done!");
  Robot.end();
}