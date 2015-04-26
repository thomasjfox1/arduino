#include <Stepper.h>

//ALL UNITS NEED TO BE IN CENTIMETERS

const int stepsPerRevolution = 200;
const float Pi = 3.141593;
const int spoolDiameter = 10; //10cm

//distance counter to keep track of roughly where the object is in space 
float distanceCounter = 0;  //starts at 0 meaning that's the location of the ball at the very beginning
const float stepDegree = 360/stepsPerRevolution;
int currentSpeed = 0;
const float stringLength = 200; //200cm

// initialize the stepper library on the motor shield
Stepper myStepper(stepsPerRevolution, 12,13);     

// give the motor control pins names:
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int directionA = 12;
const int directionB = 13;

void setup() {
  Serial.begin(9600);
  // set the PWM and brake pins so that the direction pins  
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
}


void loop() {
  // this will cut the program if the object gets too close to the top or bottom
  while(distanceCounter < stringLength){
    myStepper.setSpeed(currentSpeed);
    
    currentSpeed = accelerateDown(myStepper, currentSpeed, 200, 1.2);
    myStepper.setSpeed(currentSpeed);
    myStepper.step(travelCalc(100));
    distance(travelCalc(100));
    currentSpeed = decelerateDown(myStepper, currentSpeed, 0, 0.8);
  
    delay(100);  
    
    currentSpeed = accelerateUp(myStepper, currentSpeed, 200, 1.2);
    myStepper.setSpeed(currentSpeed);
    myStepper.step(-travelCalc(100));
    distance(-travelCalc(100));
    currentSpeed = decelerateUp(myStepper, currentSpeed, 0, 0.8);
    
    delay(100);
  }
}


//accelerate the object's speed downwards in an exponential manner
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

//decelerate the object's speed downwards in an exponential manner
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

//accelerate the object's speed upwards in an exponential manner
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

//decelerate the object's speed upwards in an exponential manner
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

//returns how many steps are needed to go x number of centimeters
int travelCalc(float measurement){
  float circMeasure = Pi * measurement;
  return stepsPerRevolution * (circMeasure/(Pi*spoolDiameter));
}

//keep track of the distance the object is in the air so it does not go too high or too low
float distance(int steps){
  return distanceCounter + (spoolDiameter * Pi) * (360 / (steps * stepDegree));
}

