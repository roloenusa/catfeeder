/*
SparkFun Inventor's Kit
Example sketch 08

SINGLE SERVO

  Sweep a servo back and forth through its full range of motion.

  A "servo", short for servomotor, is a motor that includes 
  feedback circuitry that allows it to be commanded to move to
  specific positions. This one is very small, but larger servos
  are used extensively in robotics to control mechanical arms,
  hands, etc. You could use it to make a (tiny) robot arm,
  aircraft control surface, or anywhere something needs to be
  moved to specific positions.

Hardware connections:

  The servo has a cable attached to it with three wires.
  Because the cable ends in a socket, you can use jumper wires
  to connect between the Arduino and the servo. Just plug the
  jumper wires directly into the socket.
  
  Connect the RED wire (power) to 5 Volts (5V)
  Connect the WHITE wire (signal) to digital pin 9
  Connect the BLACK wire (ground) to ground (GND)

  Note that servos can use a lot of power, which can cause your
  Arduino to reset or behave erratically. If you're using large
  servos or many of them, it's best to provide them with their
  own separate 5V supply. See this Arduino Forum thread for info:
  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1239464763

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.

Version 2.0 6/2012 MDG
*/


// If we had to write a sketch to control a servo from scratch,
// it would be a lot of work. Fortunately, others have done the
// hard work for you. We're going to include a "library"
// that has the functions needed to drive servos.

// A library is an set of additional functions you can add to
// your sketch. Numerous libraries are available for many uses,
// see http://arduino.cc/en/Reference/Libraries for information
// on the standard libraries, and Google for others. When you're
// using a new part, chances are someone has written a library
// for it.

#include <Servo.h>  // servo library

// Once you "include" a library, you'll have access to those
// functions. You can find a list of the functions in the servo
// library at: http://arduino.cc/en/Reference/Servo
// Most libraries also have example sketches you can load from
// the "file/examples" menu.

// Now we'll create a servo "object", called myservo. You should
// create one of these for each servo you want to control. 
// You can control a maximum of twelve servos on the Uno 
// using this library. (Other servo libraries may let you
// control more). Note that this library disables PWM on
// pins 9 and 10!

Servo servo1;  // servo control object
const int SERVO_PIN = 9;
const int WAIT = 2000;


void setup()
{
  // We'll now "attach" the servo1 object to digital pin 9.
  // If you want to control more than one servo, attach more
  // servo objects to the desired pins (must be digital).

  // Attach tells the Arduino to begin sending control signals
  // to the servo. Servos require a continuous stream of control
  // signals, even if you're not currently moving them.
  // While the servo is being controlled, it will hold its 
  // current position with some force. If you ever want to
  // release the servo (allowing it to be turned by hand),
  // you can call servo1.detach().
  servo1.attach(SERVO_PIN);
  Serial.begin(9600);
}


void loop()
{
  int position;
  
  // To control a servo, you give it the angle you'd like it
  // to turn to. Servos cannot turn a full 360 degrees, but you
  // can tell it to move anywhere between 0 and 180 degrees.

  // Change position at full speed:
  
  servo_go_to(90, 3000);
  delay(5000);
  servo_go_to(0, 3000);
  delay(5000);
}

void servo_go_to(int angle, int wait)
{
  servo1.attach(9);
  servo1.write(angle);    // Tell servo to go to 90 degrees
  delay(wait);         // Pause to get it time to move
  servo1.detach();
}


void loop_forward(Servo servo)
{
  // Change position at a slower speed:

  // To slow down the servo's motion, we'll use a for() loop
  // to give it a bunch of intermediate positions, with 20ms
  // delays between them. You can change the step size to make 
  // the servo slow down or speed up. Note that the servo can't
  // move faster than its full speed, and you won't be able
  // to update it any faster than every 20ms.

  // Tell servo to go to 180 degrees, stepping by two degrees
 
  for(int position = 0; position < 180; position += 2)
  {
    servo.write(position);  // Move to next position
    Serial.print("Moving to");
    Serial.println(position);
    delay(20);               // Short pause to allow it to move
  }
}

void loop_backward(Servo servo)
{
  // Tell servo to go to 0 degrees, stepping by one degree
  for(int position = 180; position >= 0; position -= 1)
  {                                
    servo.write(position);  // Move to next position
    delay(20);               // Short pause to allow it to move
  }
}
