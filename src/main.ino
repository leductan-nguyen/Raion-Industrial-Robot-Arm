/**
 * 3DRaion 2018
 * Raion Industrial 6-axis Robot Arm
 */

#include <Arduino.h>
#include <Servo.h>

Servo servo1;               // create servo object to control a servo
Servo servo2;               // create servo object to control a servo
Servo servo3;               // create servo object to control a servo
Servo servo4;               // create servo object to control a servo
Servo servo5;               // create servo object to control a servo
Servo servo6;               // create servo object to control a servo
const int SERVO_PIN_1 = 3;  // defines PIN for servo (PWM)
const int SERVO_PIN_2 = 5;  // defines PIN for servo (PWM)
const int SERVO_PIN_3 = 6;  // defines PIN for servo (PWM)
const int SERVO_PIN_4 = 9;  // defines PIN for servo (PWM)
const int SERVO_PIN_5 = 10; // defines PIN for servo (PWM)
const int SERVO_PIN_6 = 11; // defines PIN for servo (PWM)
const int INIT_POS = 0;     // start at midpoint 0 degrees
const int INIT_SPEED = 3;   // by default servo moves 3 degrees each time left/right is pushed
const int DELAY = 1000;     // delays in ms between servo actions
// int pos;                  // variable to store the servo position
// int speed;                // Number of degrees to move each time a move button is pressed

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ; // wait for serial connection, this loop allows dev to see initializing procedure
  Serial.println("");
  Serial.println("Raion Industrial Robot Arm with IR Controller");
  Serial.println("-------------------------");
  delay(1000);
  Serial.print("Initializing servos... ");
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  servo4.attach(SERVO_PIN_4);
  servo5.attach(SERVO_PIN_5);
  servo6.attach(SERVO_PIN_6);
  initServos();
  Serial.println("Done");
  Serial.println("-------------------------");
  Serial.println("Write command to perform action");
  Serial.println("-------------------------");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    Serial.print("Input string : ");
    Serial.println(input);
    int state = input.toInt();

    if (state >= 0 && state <= 180) {
      Serial.print(">>> ");
      Serial.println(state);
      Serial.print("Turning servo 1 to ");
      Serial.print(state);
      Serial.println(" degrees");
      turnServo(servo1, state);
    } else {
      Serial.println("!!! Invalid turning angle !!!");
    }
  }
}

/**
 * Turn servos with specified angles
 */
void turnServos(int angle1, int angle2, int angle3) {
  servo1.write(angle1);
  servo2.write(angle2);
  if (angle3 >= 90 && angle3 <= 170) {
    servo3.write(angle3);
  }
  delay(DELAY);
}

/**
 * Turn one specified servo with angle
 */
void turnServo(Servo &servo, int angle) {
  servo.write(angle);
  delay(DELAY);
}

/**
 * Initialize all servos
 */
void initServos() {
  servo1.write(145);
  servo2.write(35);
  servo3.write(130);
  servo4.write(140);
  servo5.write(80);
  servo6.write(90);
  delay(DELAY);

  // servo1.write(145);
  // servo2.write(115);
  // servo3.write(170);
  // delay(DELAY);

  // servo1.write(90);
  // servo2.write(90);
  // servo3.write(155);
  // delay(DELAY);
}