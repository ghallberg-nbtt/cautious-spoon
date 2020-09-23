/*
  IR Controlled Vehicle
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/cautious-spoon/blob/master/LICENSE
*/

#include <IRremote.h>
//Remote code definitions
const long FORWARD = 0xFF629D;
const long REVERSE = 0xFFA857;
const long RIGHT = 0xFFC23D;
const long LEFT = 0xFF22DD;
const long STOP = 0xFF02FD;
const long LOW_SPEED = 0xFF6897;
const long MEDIUM_SPEED = 0xFF9867;
const long TOP_SPEED = 0xFFB04F;
//pin assignments
const int RECEIVER = 12;
const int ENABLE1 = 6;
const int INPUT1 = 4;
const int INPUT2 = 5;
const int ENABLE2 = 9;
const int INPUT3 = 7;
const int INPUT4 = 10;

//variables
int vehicleSpeed = 150;
long remoteCode = 0;
String direction = "stop";

/*-----( Declare objects )-----*/
IRrecv irrecv(RECEIVER); //Create instance of 'irrecv'
decode_results results;  //Create instance of 'decode_results'

void setup() {
  pinMode (ENABLE1, OUTPUT);
  pinMode (INPUT1, OUTPUT);
  pinMode (INPUT2, OUTPUT);
  pinMode (ENABLE2, OUTPUT);
  pinMode (INPUT3, OUTPUT);
  pinMode (INPUT4, OUTPUT);
  Serial.begin(9600); //Only needed for troubleshooting
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true); // flash built in LED
  brake ("left");
  brake ("right");
}

void loop() {
  //First read the remote
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    remoteCode = results.value;
    switch (remoteCode) {
      case (FORWARD): {
          Serial.println ("Forward");
          forward ("left", vehicleSpeed);
          forward ("right", vehicleSpeed);
          break;
        }
      case (REVERSE): {
          Serial.println ("Reverse");
          reverse ("left", vehicleSpeed);
          reverse ("right", vehicleSpeed);
          break;
        }
      case (RIGHT): {
          Serial.println ("Right");
          forward ("left", 255);
          forward ("right", 150);
          break;
        }
      case (LEFT): {
          Serial.println ("left");
          forward ("left", 150);
          forward ("right", 255);
          break;
        }
      case (STOP): {
          Serial.println ("Stop");
          brake ("left");
          brake ("right");
          break;
        }
      case (LOW_SPEED): {
          Serial.println ("Low speed");
          vehicleSpeed = 150;
          break;
        }
      case (MEDIUM_SPEED): {
          Serial.println ("Medium speed");
          vehicleSpeed = 200;
          break;
        }
      case (TOP_SPEED): {
          Serial.println ("Top speed");
          vehicleSpeed = 255;
          break;
        }
    }
    irrecv.resume(); // receive the next value
  }
  delay (50);
}

void forward (String motor, int speed)
{

  if (motor == "left") {
    digitalWrite (ENABLE1, LOW); //Disable H-Bridge
    digitalWrite (INPUT1, HIGH);
    digitalWrite (INPUT2, LOW);
    analogWrite (ENABLE1, speed); //PWM to drive left motor
    Serial.println (speed);
  } else {
    digitalWrite (ENABLE2, LOW); //Disable H-Bridge
    digitalWrite (INPUT3, HIGH);
    digitalWrite (INPUT4, LOW);
    analogWrite (ENABLE2, speed); //PWM to drive right motor
    Serial.println (speed);
  }
}

//Drive motor backward at the specified speed (0 – 255)
void reverse (String motor, int speed)
{
  if (motor == "left") {
    digitalWrite (ENABLE1, LOW); //Disable H-Bridge
    digitalWrite (INPUT1, LOW);
    digitalWrite (INPUT2, HIGH);
    analogWrite (ENABLE1, speed); //PWM to drive left motor
  } else {
    digitalWrite (ENABLE2, LOW); //Disable H-Bridge
    digitalWrite (INPUT3, LOW);
    digitalWrite (INPUT4, HIGH);
    analogWrite (ENABLE2, speed); //PWM to drive right motor
  }
}

//Stop motor
void brake (String motor)
{
  if (motor == "left") {
    digitalWrite (ENABLE1, LOW); //Disable H-Bridge
    digitalWrite (INPUT1, LOW);
    digitalWrite (INPUT2, LOW);
    analogWrite (ENABLE1, HIGH); //Brake left motor
  } else {
    digitalWrite (ENABLE2, LOW); //Disable H-Bridge
    digitalWrite (INPUT3, LOW);
    digitalWrite (INPUT4, LOW);
    analogWrite (ENABLE2, HIGH); //Brake right motor
  }
}
