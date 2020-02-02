/*
	Test for the VEX Touch Sensor/Limit Switch
  - both sensors use the same code/wiring and can be used with this example
	*/

#include <Vex.h> 

Touch touch(0);

void setup()
{
	//set up the serial monitor
	Serial.begin(9600);
  touch.begin();
}


void loop()
{ 
  bool button = touch.isPushed();
  Serial.println(button);
  while(button == true){
    button = touch.isPushed();
    Serial.println(button);
  }
}
