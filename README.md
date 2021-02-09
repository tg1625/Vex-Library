# Welcome to the VEX Library

The code is to be used with an Arduino and the Adafruit Motor Shield. This library was made for New York University's Tandon School of Engineering Introduction to Engineering & Design (EG1003), to be used when completing Robotics projects using VEX structural components. This is a compilation of various libraries from third-parties as well as a new library made in-house to easily interact with the Arduino Uno and Adafruit Motor Shield used in these robotics projects. Full documentation for this library can be found [here](https://manual.eg.poly.edu/index.php/VEX_Library_Guide) 


# Files

- Adafruit_Motor_Shield_V2_Library
	- Adafruit Library for the motor shield, **unedited**
- I2Cdev
	- Third party library for I2C communication, **unedited**
- MPU6050
	- **Edited** third party library for the MPU6050 gyro
- Vex
	- Main library for the VEX robots
	
# Sensors

The third party libraries, along with additional implementations in the main VEX library enable Arduino to interact with the following sensors:

- Gyro Sensor (MPU6050)
- Ultrasonic Sensor ([VEX brand](https://www.robotshop.com/media/files/pdf/vex-ultrasonic-range-finder-insert.pdf "VEX Ultrasonic Documentation") & [HC-SR04](http://web.eece.maine.edu/~zhu/book/lab/HC-SR04%20User%20Manual.pdf "HC-SR04 Ultrasonic Documentation"))
- Touch Sensors ([VEX Brand](http://cdn.robotc.net/pdfs/natural-language/hp_touch.pdf "VEX Button Documentation") & [Capacitive Touch Sensors TTP223B](https://www.instructables.com/id/Tutorial-for-TTP223-Touch-Sensor-Module-Capacitive/ "Capactive Touch Sensor Instructable"))
- IR Range Sensor (EK1254)
