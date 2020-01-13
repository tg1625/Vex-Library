/*
	Movement Test for the VEX Robot with the Motor Shield, Gyro Sensor, Touch Sensor, and Ultrasonic Sensor 
	
*/

#include <Vex.h> 

////Declare Vex object named Robot
Vex Robot;
Gyro gyro;
Touch touch(0);
Ultrasonic ultrasonic(6,7);

//Create motor objects
Adafruit_DCMotor *motorA = Robot.setMotor(3);
Adafruit_DCMotor *motorB = Robot.setMotor(4);
Adafruit_DCMotor *motorC = Robot.setMotor(1);
Adafruit_DCMotor *motorD = Robot.setMotor(2);


void setup()
{
	//set up the serial monitor
	Serial.begin(9600);
	Serial.println("Movement Test for the VEX Robot");

  
  //Ultrasonic 
  ultrasonic.begin();

  //Gyro
  while(!Serial); //wait for Serial monitor to start up
  Serial.println("Starting up Gyro");
  gyro.begin(); //set up gyro sensor

  //Touch
  touch.begin();

 
  //start up the robot
  Robot.begin();
  delay(5000);
}

void turnLeft(){ //makes a 90 degree left turn using the Gyro Sensor 
  Serial.println("Left turn");
  //create angle variables to do turns
  float current_angle = gyro.getZAngle();
  Serial.print("First Angle: ");
  Serial.println(current_angle);
  float wanted_angle = current_angle - 90; //want to do a 90deg left turn
  while (wanted_angle < current_angle){ //while not yet at angle 
    Robot.moveTank(motorA,motorB,-30, 30,0.1); //move right motor forward and left motor backwards slowly to turn
    delay(100); //give robot time to stabilize before next gyro reading
    float temp_angle = gyro.getZAngle();
    if (temp_angle > 0){
      current_angle = gyro.getZAngle(); //update current angle to the new position
      Serial.print("Current Angle: ");
      Serial.println(current_angle);
    }
  }
}

void turnRight(){ //makes a 90 degree right turn with the Gyro Sensor
  Serial.println("Right turn");
  float current_angle = gyro.getZAngle(); //create angle variables to do turns
  Serial.print("First Angle: ");
  Serial.println(current_angle);
  
  float wanted_angle = current_angle + 90; //want to do a 90deg right turn
  
  while (wanted_angle > current_angle){ //while not yet at angle 
    Robot.moveTank(motorA,motorB,30, -30,0.2); //move right motor backwards and left motor forwards slowly to turn
    delay(100); //give robot time to stablilize before next gyro reading
    float temp_angle = gyro.getZAngle();
    if (temp_angle > 0){
      current_angle = gyro.getZAngle(); //update current angle to the new position
      
      Serial.print("Current Angle: ");
      Serial.println(current_angle);
      Serial.print(current_angle);
      Serial.print("\n"); //this is due to a segmentation fault sometimes caused by println
    }
  }
}

void loop()
{
  //forward
  Serial.println("Moving forward");
  Robot.moveTank(motorA, motorB, 50, 50, 1);
  turnRight(); 
  delay(200); 
  Robot.moveTank(motorA, motorB, -50, -50, 1);
  turnLeft(); 
  delay(200); 

  //ultrasonic
  long distance = ultrasonic.checkUltrasonic();
  while(distance > 20){
    Robot.moveTank(motorA, motorB, 40, 40, 0.1);
    distance = ultrasonic.checkUltrasonic();
  }

  //touch 
  bool button = touch.isPushed();
  while(button == true){
    button = touch.isPushed();
  }
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

  //hard code 
//  // move backward
//  Serial.println("Moving Backwards");
//  Robot.moveTank(motorA, motorB, -100, -100, 1);
//  //right swing turn
//  Serial.println("Right Swing Turn");
//  Robot.moveMotor(motorA, 100, 1);
//  //left swing turn
//  Serial.println("Left Swing Turn");
//  Robot.moveMotor(motorB, 100, 1);
//  //right point turn
//  Serial.println("Right point turn");
//  Robot.moveTank(motorA, motorB, 100, -100, 1);
//  //left point turn
//  Serial.println("Left point turn");
//  Robot.moveTank(motorA, motorB, -100, 100, 1);

  //finish
  Serial.println("Done!");
  Robot.end();
}
