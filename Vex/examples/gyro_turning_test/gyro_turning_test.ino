/*
 * Vex Gyro Turning Example
 * *
 */
 #include <Vex.h>

//Create Vex object named Robot
Vex Robot;

//Create motor objects
Adafruit_DCMotor *motorA = Robot.setMotor(1); //right motor
Adafruit_DCMotor *motorB = Robot.setMotor(2); //left motor


//Create Gyro object named gyro
Gyro gyro;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //set up serial monitor
  while(!Serial); //wait for Serial monitor to start up
  Serial.println("Vex Gyro Turning Test");
  Robot.begin(); //set up robot
  gyro.begin(); //set up gyro sensor
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
   * Left Turn
   */
  Serial.println("Left turn");
  //create angle variables to do turns
  float current_angle = gyro.getZAngle();
  Serial.print("First Angle: ");
  Serial.println(current_angle);
  float wanted_angle = current_angle - 90; //want to do a 90deg left turn
  while (wanted_angle < current_angle){ //while not yet at angle 
    Robot.moveTank(motorA,motorB,30, -30,0.1); //move right motor forward and left motor backwards slowly to turn
    delay(100); //give robot time to stabilize before next gyro reading
    current_angle = gyro.getZAngle(); //update current angle to the new position
    Serial.print("Current Angle: ");
    Serial.println(current_angle);
  }

  /*
   * Right Turn 
   */
  Serial.println("Right turn");
  current_angle = gyro.getZAngle(); //create angle variables to do turns
  Serial.print("First Angle: ");
  Serial.println(current_angle);
  
  wanted_angle = current_angle + 90; //want to do a 90deg right turn
  
  while (wanted_angle > current_angle){ //while not yet at angle 
    Robot.moveTank(motorA,motorB,-30, 30,0.2); //move right motor backwards and left motor forwards slowly to turn
    delay(100); //give robot time to stablilize before next gyro reading
    current_angle = gyro.getZAngle(); //update current angle to the new position
    
    Serial.print("Current Angle: ");
    //Serial.println(current_angle);
    Serial.print(current_angle);
    Serial.print("\n"); //this is due to a segmentation fault sometimes caused by println
    }

  Robot.end(); //stop robot

  
}
