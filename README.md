# Welcome to the VEX Library

This is a compilation of various libraries from third-parties as well as code made in-house to easily interact with VEX robots. The code is to be used with an Arduino and the Adafruit Motor Shield. This was made for New York University's Tandon School of Engineering Introduction to Engineering & Design (EG1003).


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
