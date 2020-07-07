
#include <IRremote.h>


IRrecv remote(11);
decode_results results;
//Init Motors

int trig1Pin = 10;    // Trigger
int echo1Pin = 12;    // Echo
long duration2, centimeters;


const int speedPin = 5;
const int motorPin = 2;
const int motor1Pin = 3;

const int speed1Pin = 6;
const int motor2Pin = 8;
const int motor3Pin = 9;

int speed = 100;

void setup(){
  Serial.begin(9600);
  remote.enableIRIn();
  
  pinMode(speedPin,OUTPUT);
  pinMode(speed1Pin,OUTPUT);
  
  pinMode(motorPin,OUTPUT);
  pinMode(motor1Pin,OUTPUT);
  
  pinMode(motor2Pin,OUTPUT);
  pinMode(motor3Pin,OUTPUT);
  
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
}


void loop(){
  startsensor();
  if (centimeters<=10)
  {
  digitalWrite(motorPin, LOW);
  digitalWrite(motor1Pin, LOW);
  
  digitalWrite(motor2Pin, LOW);
  digitalWrite(motor3Pin, LOW);
  }
  if (remote.decode(&results)){
 
       
    	switch(results.value){
          case 0xFD00FF://power
          break;
          case 0xFD807F://vol+
          	forward();
          break;
          case 0xFD40BF://func/stop
          break;
          case 0xFD20DF://|<<
          	turnLeft();
          break;
          case 0xFDA05F://>||
          	stop();
          break ;  
          case 0xFD609F://>>|
           turnRight();
          break ;               
          case 0xFD10EF://down arrow
          	speedDown();
          break ;  
          case 0xFD906F://vol-
          	backward();
          break ;  
          case 0xFD50AF://up arrow
          	speedUp();
          break ;  
           
          
        }
       remote.resume(); 
  }
}



void forward(){
  Serial.println("forward");
  analogWrite(speedPin, speed);
  analogWrite(speed1Pin, speed);
  
  digitalWrite(motorPin, HIGH);
  digitalWrite(motor1Pin, LOW);
  
  digitalWrite(motor2Pin, HIGH);
  digitalWrite(motor3Pin, LOW);
}

void backward(){
  Serial.println("backward");
  analogWrite(speedPin, speed);
  analogWrite(speed1Pin, speed);
  
  digitalWrite(motorPin, LOW);
  digitalWrite(motor1Pin, HIGH);
  
  digitalWrite(motor2Pin, LOW);
  digitalWrite(motor3Pin, HIGH);
}

void turnLeft(){
  Serial.println("turnLeft");
  analogWrite(speedPin, 0);
  analogWrite(speed1Pin, speed);
  
  digitalWrite(motorPin, HIGH);
  digitalWrite(motor1Pin, LOW);
  
  digitalWrite(motor2Pin, HIGH);
  digitalWrite(motor3Pin, LOW);
}

void turnRight(){
  Serial.println("turnRight");
  analogWrite(speedPin, speed);
  analogWrite(speed1Pin, 0);
  
  digitalWrite(motorPin, HIGH);
  digitalWrite(motor1Pin, LOW);
  
  digitalWrite(motor2Pin, HIGH);
  digitalWrite(motor3Pin, LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(motorPin, LOW);
  digitalWrite(motor1Pin, LOW);
  
  digitalWrite(motor2Pin, LOW);
  digitalWrite(motor3Pin, LOW);
}

void speedUp(){
  Serial.println("speedUp");
  speed+=10;
  if(speed>255) speed =255;
  analogWrite(speedPin, speed);
  analogWrite(speed1Pin, speed);
}

void speedDown(){
  Serial.println("speedDown");
  speed-=10;
  if(speed<0) speed =0;
  analogWrite(speedPin, speed);
  analogWrite(speed1Pin, speed);
}

void startsensor(){
  digitalWrite(trig1Pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig1Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1Pin, LOW);
  
  pinMode(echo1Pin, INPUT);
  duration2 = pulseIn(echo1Pin, HIGH);
  
    centimeters = ((duration2/2) / 29.1) *1.33; 
  
  Serial.print(centimeters);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}