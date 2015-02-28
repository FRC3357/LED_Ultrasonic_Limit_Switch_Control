//Include libraries
#include <NewPing.h>
#include <AFMotor.h>

//Create motors
AF_DCMotor leftLED(1);
AF_DCMotor rightLED(2);

//Create data variables
int potVal = 0;
int maxDist = 0;
int potPin = A0;
int rightSonar = 0;
int leftSonar = 0;
int minDist = 2;
int rightSwitchPin = 5;
int leftSwitchPin = 6;
boolean rightSwitch = false;
boolean leftSwitch = false;
int triggerPin1 = A2;
int echoPin1 = A1;
int triggerPin2 = 10;
int echoPin2 = 9;

//Create new sonars
NewPing sonar1(triggerPin1,echoPin1,100);
NewPing sonar2(triggerPin2,echoPin2,100);

void setup() {
  //Set speed
  leftLED.setSpeed(255);
  rightLED.setSpeed(255);
  
  //Start Serial
  Serial.begin(9600);
  Serial.println("Initialized");
  
  //Set pin modes
  pinMode(potPin, INPUT);
  pinMode(rightSwitchPin, INPUT);
  pinMode(leftSwitchPin, INPUT);
}

void loop() {
  
  //Get data
  rightSwitch = digitalRead(rightSwitchPin);
  leftSwitch = digitalRead(leftSwitchPin);
  
  rightSonar = sonar1.ping_cm();
  leftSonar = sonar2.ping_cm();
  
  potVal = analogRead(potPin);
  maxDist = map(potVal, 0, 1023, 2, 10);
  
  //Change 0's to 6's
  if(rightSonar < minDist){
    rightSonar = 100;
  }
  if(leftSonar < minDist){
    leftSonar = 100;
  }
  
  // Print diagnostic data
  Serial.print(maxDist);
  Serial.print("\t");              
  Serial.print(rightSonar);
  Serial.print("\t");              
  Serial.print(leftSonar);
  Serial.print("\t");              
  Serial.print(rightSwitch);
  Serial.print("\t");              
  Serial.print(leftSwitch);
  Serial.print("\t");                
  
  //Detect objects
  if(rightSonar <= maxDist || leftSwitch == false){          
    //Turn the LED's on
    rightLED.run(BACKWARD);
    Serial.print("Right light on");
    Serial.print("\t");              
  }
  else{
    rightLED.run(FORWARD);
  }
  if(leftSonar <= maxDist || rightSwitch == false){                     
    //Turn the LED's on
    leftLED.run(BACKWARD);
    Serial.print("Left light on");
  }
  else{
    leftLED.run(FORWARD);
  }
  
  //Print new line
  Serial.print("\n");
}
