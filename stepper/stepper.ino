//This code is designed to control a stepper motor with a pontentiometer as speed control.

#include <Stepper.h>

const int stepsPerRevolution = 200;
const float Pi = 3.141593;
const int spoolDiameter = 10;
float distanceCounter;
float stepDegree = 360/stepsPerRevolution;
int currentSpeed = 0;

// initialize the stepper library on the motor shield
Stepper myStepper(stepsPerRevolution, 12,13);     

// give the motor control pins names:
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int directionA = 12;
const int directionB = 13;

int x = 0;
void setup() {
  Serial.begin(9600);
  // set the PWM and brake pins so that the direction pins  // can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
  
  // initialize the serial port:
  Serial.begin(9600);
  // myStepper.setSpeed(30);
}


void loop() {
  myStepper.setSpeed(currentSpeed);
  currentSpeed = accelerateUp(myStepper, currentSpeed, 200, 1.2);
  
  myStepper.setSpeed(200);
  myStepper.step(200);
  myStepper.step(-200);

}

int accelerateDown(Stepper stepper, int initialSpeed, int maxSpeed, int accelerationRate){
  int currentSpeed = initialSpeed;
  while(currentSpeed <= maxSpeed){
    if(currentSpeed == 0){
      stepper.setSpeed(1);
      stepper.step(5);
      distance(5);
      currentSpeed = 1;
    }
    else if (currentSpeed == 1){
      stepper.setSpeed(2);
      stepper.step(5);
      distance(5);
      currentSpeed = 2; 
    }
    else{
      for(int i = 0; i <= maxSpeed; i++)
        pow(currentSpeed, accelerationRate);
        stepper.setSpeed(currentSpeed);
        stepper.step(5);
        distance(5);
    }
  }
  return currentSpeed;
}

int decelerateDown(Stepper stepper, int initialSpeed, int minSpeed, int decelerationRate){
  int currentSpeed = initialSpeed;
  while(currentSpeed >= minSpeed){
    if (currentSpeed == 1){
      stepper.setSpeed(0);
      currentSpeed = 0; 
    }
    else{
      for(int i = 0; i <= minSpeed; i++)
        pow(currentSpeed, decelerationRate);
        stepper.setSpeed(currentSpeed);
        stepper.step(5);
        distance(5);
    }
  }
  return currentSpeed;
}

int accelerateUp(Stepper stepper, int initialSpeed, int maxSpeed, int accelerationRate){
  int currentSpeed = initialSpeed;
  while(currentSpeed <= maxSpeed){
    if(currentSpeed == 0){
      stepper.setSpeed(1);
      stepper.step(-5);
      distance(-5);
      distanceCounter += 5;
      currentSpeed = 1;
    }
    else if (currentSpeed == 1){
      stepper.setSpeed(2);
      stepper.step(-5);
      distance(-5);
      currentSpeed = 2; 
    }
    else{
      for(int i = 0; i <= maxSpeed; i++)
        pow(currentSpeed, accelerationRate);
        stepper.setSpeed(currentSpeed);
        stepper.step(-5);
        distance(-5);
    }
  }
  return currentSpeed;
}

int decelerateUp(Stepper stepper, int initialSpeed, int minSpeed, int decelerationRate){
  int currentSpeed = initialSpeed;
  while(currentSpeed >= minSpeed){
    if (currentSpeed == 1){
      stepper.setSpeed(0);
      currentSpeed = 0; 
    }
    else{
      for(int i = 0; i <= minSpeed; i++)
        pow(currentSpeed, decelerationRate);
        stepper.setSpeed(currentSpeed);
        stepper.step(-5);
        distance(-5);
    }
  }
  return currentSpeed;
}

float distance(int steps){
  return distanceCounter + (steps * stepDegree);
}

