/*
	Test for the Ultrasonic Sensor using VEX robots
  - this example will work for both the VEX ultrasonic sensor and 4-wire Arduino Ultrasonic Sensors 
	
*/

#include <Vex.h> 

////Declare Vex object named Robot
Vex Robot;
Ultrasonic ultrasonic(6,7); //digital pin 6 is the trigger, digital pin 7 is the echo

//Create motor objects
Adafruit_DCMotor *motorA = Robot.setMotor(1); //left motor connected to terminal M1
Adafruit_DCMotor *motorB = Robot.setMotor(2);// right motor connected to terminal M2



void setup()
{
	//set up the serial monitor
	Serial.begin(9600);
  //start up the ultrasonic 
  ultrasonic.begin();
  //start up the robot
  Robot.begin();
  delay(500);
}

void loop()
{
  //ultrasonic
  long distance = ultrasonic.checkUltrasonic();
  Serial.print("Distance: ");
  Serial.println(distance);
  while(distance > 5){ //while the robot is more than 5cm away from an obstacle
    Robot.moveTank(motorA, motorB, 40, 40, 0.1); //move forward slowly for 0.1 seconds
    distance = ultrasonic.checkUltrasonic(); //recheck distance 
    Serial.print("Distance: ");
    Serial.println(distance);
  }
}
