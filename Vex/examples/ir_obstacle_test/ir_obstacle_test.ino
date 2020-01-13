/*
 * IR_Obstacle_Test.ino
 * - example code to test the IR obstacle avoidance sensor using the Vex library 
 */

#include <Vex.h>

int isObstaclePin = 7;  // This is our input pin

IRObstacle ir(isObstaclePin); //create an IRobstacle object using pin 7 

void setup() {
  ir.begin(); //start up IR sensor 
  Serial.begin(9600);
  
}

void loop() {
  bool obstacle = ir.isObstacle(); //HIGH means there is an obstacle
  if (obstacle == HIGH)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    //digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("clear");
    //digitalWrite(LED, LOW);
  }
  delay(200);
}