#include <Time.h>
#include <TimeAlarms.h>
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
  
  setTime(8,29,0,1,1,10); // set time to 8:29:00am Jan 1 2010
  // create the alarms 
  Alarm.alarmRepeat(8,30,0, servoAlarm);  // 8:30am every day
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
 
  //Alarm.timerRepeat(15, Repeats);          // timer for every 15 seconds    
  //Alarm.timerOnce(10, OnceOnly);          // called once after 10 seconds 
}


void loop()
{
  // To control a servo, you give it the angle you'd like it
  // to turn to. Servos cannot turn a full 360 degrees, but you
  // can tell it to move anywhere between 0 and 180 degrees.

  // Change position at full speed:
  
  //turnServoToAngle(90, 3000);
  //delay(5000);
  //turnServoToAngle(0, 3000);
  //delay(5000);
  //digitalClockDisplay();
  delayOverride(1000); // wait one second between clock display
}

void servoAlarm()
{
  int angle = servo1.read();
  Serial.println(angle);
  turnServoToAngle(angle + 10, 5000);
}

void turnServoToAngle(int angle, int wait)
{
  servo1.attach(9);
  servo1.write(angle);    // Tell servo to go to 90 degrees
  delayOverride(wait);         // Pause to get it time to move
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

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void delayOverride(int milliseconds)
{
  Alarm.delay(milliseconds);
  //delay(milliseconds);
}
