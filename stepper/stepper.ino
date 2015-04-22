//This code is designed to control a stepper motor with a pontentiometer as speed control.

#include <Stepper.h>

const int stepsPerRevolution = 200;

// initialize the stepper library on the motor shield
Stepper myStepper(stepsPerRevolution, 12,13);     

// give the motor control pins names:
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int directionA = 12;
const int directionB = 13;

const int potentiometer = A1;

int x = 0;
void setup() {
Serial.begin(9600);
// set the PWM and brake pins so that the direction pins  // can be used to control the motor:
pinMode(pwmA, OUTPUT);
pinMode(pwmB, OUTPUT);
pinMode(brakeA, OUTPUT);
pinMode(brakeB, OUTPUT);

pinMode(potentiometer, INPUT);

digitalWrite(pwmA, HIGH);
digitalWrite(pwmB, HIGH);
digitalWrite(brakeA, LOW);
digitalWrite(brakeB, LOW);

// initialize the serial port:
Serial.begin(9600);
// myStepper.setSpeed(30);
}


void loop() {
  
  int potentioValue = analogRead(potentiometer); //potentiometer can read between 0 and 1023
  
  Serial.write("potentioValue: " + potentioValue); //debugging purposes
  
  int calculatedSpeed = potentioValue/4;         //divided by 4 to limit rpms
  
  myStepper.setSpeed(calculatedSpeed);

  myStepper.step(1); //not sure if I can get away with having no value here. 

//  myStepper.step(200);
//  myStepper.step(-200);
//  delay(2000);

}
