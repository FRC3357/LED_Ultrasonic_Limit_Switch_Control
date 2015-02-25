//Include libraries
#include <NewPing.h>
#include <AFMotor.h>

//Create motors
AF_DCMotor leftLED(1);
AF_DCMotor rightLED(2);

//Create data variables
int potVal = 0;
int maxDist = 0;
int potPin = A1;
int sonar1avg = 0;
int sonar2avg = 0;
int avgCount = 6;
int i = 0;
int minDist = 2;
int switchPin1 = 5;
int switchPin2 = 6;
boolean switch1 = false;
boolean switch2 = false;

//Create new sonars
NewPing sonar1(A2,A3,100);
NewPing sonar2(A4,A5,100);

void setup() {
  //Set speed
  leftLED.setSpeed(255);
  rightLED.setSpeed(255);
  
  //Start Serial
  Serial.begin(9600);
  Serial.println("Initialized");
  
  //Set pin modes
  pinMode(potPin, INPUT);
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
}

void loop() {
  //Reset averages
  sonar1avg = 0;
  sonar2avg = 0;
  
  //Get data
  switch1 = digitalRead(switchPin1);
  switch2 = digitalRead(switchPin2);
  
  sonar1avg = sonar1.ping_cm();
  sonar2avg = sonar2.ping_cm();
  
  potVal = analogRead(potPin);
  maxDist = map(potVal, 0, 1023, 2, 10);
  
  //Change 0's to 6's
  if(sonar1avg < minDist){
    sonar1avg = 100;
  }
  if(sonar2avg < minDist){
    sonar2avg = 100;
  }
  
  // Print diagnostic data
  Serial.print(maxDist);
  Serial.print("\t");              
  Serial.print(sonar1avg);
  Serial.print("\t");              
  Serial.print(sonar2avg);
  Serial.print("\t");              
  Serial.print(switch1);
  Serial.print("\t");              
  Serial.print(switch2);
  Serial.print("\t");                
  
  //Detect objects
  if(sonar1avg <= maxDist || switch1 == false){          
    //Turn the LED's on
    rightLED.run(BACKWARD);
    Serial.print("Right light on");
    Serial.print("\t");              
  }
  else{
    rightLED.run(FORWARD);
  }
  if(sonar2avg <= maxDist || switch2 == false){                     
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
