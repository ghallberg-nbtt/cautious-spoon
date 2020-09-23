/*
  Reading IR Remote Codes
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/cautious-spoon/blob/master/LICENSE
*/

#include <IRremote.h>

const int RECEIVER = 2;

/*-----( Declare objects )-----*/
IRrecv irrecv(RECEIVER); //Create instance of 'irrecv'
decode_results results;  //Create instance of 'decode_results'

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true); // flash built in LED
}

void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // receive the next value
  }  
}
