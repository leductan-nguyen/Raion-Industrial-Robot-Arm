/**
 * 3DRaion 2018
 * Raion Industrial Robot Arm with IR Controller
 */

#include <Arduino.h>
#include <Servo.h>
#include <IRremote.h>

// You will have to set these values depending on the protocol
// and remote codes that you are using. These are for Raion remote control
#define MY_PROTOCOL NEC
#define RIGHT_BUTTON 0xFF7A85  // Move several clockwise
#define LEFT_BUTTON 0xFF30CF   // Move servo counterclockwise
#define SELECT_BUTTON 0xFF18E7 // Center the servo
#define UP_BUTTON 0xFF9867     // Increased number of degrees servo moves
#define DOWN_BUTTON 0xFF38C7   // Decrease number of degrees servo moves
#define BUTTON_1_PLAY 0xFF22DD // Pushing buttons 1-6 moves to fixed positions
#define BUTTON_2_INT 0xFF02FD  // each 20 degrees greater
#define BUTTON_3_RPT 0xFFC23D
#define BUTTON_4_RDM 0xFFE01F
#define BUTTON_5_10M 0xFFA857
#define BUTTON_6_10P 0xFF906F

Servo myServo;            // create servo object to control a servo
const int SERVO_PIN = 9;  // defines PIN for servo (PWM)
const int INIT_POS = 90;  // start at midpoint 90 degrees
const int INIT_SPEED = 3; // by default servo moves 3 degrees each time left/right is pushed
int16_t pos;              // variable to store the servo position
int16_t speed;            // Number of degrees to move each time a move button is pressed

const int RECV_PIN = 7;         // defines pin for IR receiver
IRrecv irrecv(RECV_PIN);        // attach defined PIN to the IR Receiver
decode_results results;         // store received key value
unsigned long previous_key = 0; // to store the previous key value when key decoded is 0xFFFFFFFF

void setup()
{
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Raion Industrial Robot Arm with IR Controller");
  Serial.println("Initializing Servo...");
  myServo.attach(SERVO_PIN);
  pos = INIT_POS;
  speed = INIT_SPEED;
  myServo.write(pos);
  Serial.println("Servo set to initial position");

  irrecv.enableIRIn();
  irrecv.blink13(true);
  Serial.println("Start IR Receiver : OK");
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println("Code received");
    Serial.println(results.value, HEX);
    if (results.value == 0XFFFFFFFF)
    {
      results.value = previous_key;
    }

    switch (results.value)
    {
    case LEFT_BUTTON:
      pos = min(180, pos + speed);
      Serial.println("LEFT");
      break;
    case RIGHT_BUTTON:
      pos = max(0, pos - speed);
      Serial.println("RIGHT");
      break;
    case SELECT_BUTTON:
      pos = 90;
      Serial.println("SELECT");
      break;
    case UP_BUTTON:
      speed = min(10, speed + 1);
      Serial.println("UP");
      break;
    case DOWN_BUTTON:
      speed = max(1, speed - 1);
      Serial.println("DOWN");
      break;
    case BUTTON_1_PLAY:
      pos = 0 * 20;
      Serial.println("1");
      break;
    case BUTTON_2_INT:
      pos = 1 * 20;
      Serial.println("2");
      break;
    case BUTTON_3_RPT:
      pos = 2 * 20;
      Serial.println("3");
      break;
    case BUTTON_4_RDM:
      pos = 3 * 20;
      Serial.println("4");
      break;
    case BUTTON_5_10M:
      pos = 4 * 20;
      Serial.println("5");
      break;
    case BUTTON_6_10P:
      pos = 5 * 20;
      Serial.println("6");
      break;
    }
    myServo.write(pos); // tell servo to go to position in variable 'pos'
    previous_key = results.value;
    irrecv.enableIRIn();
  }
}