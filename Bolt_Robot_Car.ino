#include <BoltIoT-Arduino-Helper.h> //Include Bolt-Arduino-Helper Library
# define left_motor1    6 //Pin declaration for left motor
# define left_motor2    7 //Pin declaration for left motor
# define right_motor1   8 //Pin declaration for right motor
# define right_motor2   9 //Pin declaration for right motor
# define sensor1        A0 //Pin declaration for sensor1(Left IR Sensor)
# define sensor2        A1 //Pin declaration for sensor2 (Right IR Sensor)
String command = ""; //variable for storing command
int delay_time = 750; //variable for storing delay time

***************************Command Controll Functions***************************************************
// function for forward movement of robot
String forward(String *data) {
  command = "FORWARD";
  move_forward();
  return "Success:Forward"; 
  Serial.println("Forward");
}
// function for backward movement of robot
String backward(String *data) {
  command = "BACKWARD";
  move_backward();
  return "Success:Backward";
  Serial.println("Backward");
}
// function for right movement of robot
String right(String *data) {
  command = "RIGHT";
  move_right();
  delay(50);
  move_forward();
  return "Success:Right";
  Serial.println("Success:Right");
}
// function for left movement of robot
String left(String *data) {
  command = "LEFT";
  move_left();
  delay(50);
  move_forward();
  return "Success:Left";
  Serial.println("Success:Left");
}
//function for stop the robot
String stopcar(String *data) {
  command = "STOP";
  robot_stop();
  return "Success:Stop";
  Serial.println("Success:STOP");
}
// Function for automatic robot control
String automatic(String *data){
  command = "AUTOMATIC";
  return "AUTOMATIC MODE ON";
  Serial.println("AUTOMATIC MODE IS ON");
}


//*************************************************** setup code of arduino, it runs once ***************************************
void setup() {
  // put your setup code here
  pinMode(left_motor1,OUTPUT); // pinMode decide input or output type
  pinMode(left_motor2,OUTPUT);
  pinMode(right_motor1,OUTPUT);
  pinMode(right_motor2,OUTPUT);
  pinMode(sensor1,INPUT); 
  pinMode(sensor2,INPUT);
  boltiot.begin(Serial); //here hardware serial is used
  Serial.begin(9600); //baud rate for transsmit and receive data
  boltiot.setCommandString("FORWARD",forward);
  boltiot.setCommandString("BACKWARD",backward);
  boltiot.setCommandString("LEFT",left);
  boltiot.setCommandString("RIGHT",right);
  boltiot.setCommandString("STOP",stopcar);
  boltiot.setCommandString("AUTOMATIC",automatic);
}
// ************************************************** main program *****************************************************************
void loop() {
  // put your main code here, to run repeatedly:
  
    boltiot.handleCommand(); //Bolt command controll

   // For Automatic Robot Control
   if(command == "AUTOMATIC"){
    int sensorval1 = analogRead(sensor1);
    int sensorval2 = analogRead(sensor2);
    if((sensorval1<600) && (sensorval2<600)){
       move_forward();
       Serial.println("Success : Forward");
    }
    else if((sensorval1<600) && (sensorval2>600)){
       move_left();
       Serial.println("Success : Left");
    }
    else if((sensorval1>600) && (sensorval2<600)){
       move_right();
       Serial.println("Success : Right");
    }
    else{
       move_backward();
       Serial.println("Success : Backward");
    }
   }
   else{
    Serial.println("Control through Google Assistant or Bolt web page");
    Serial.println("Thank You");
   }
}
// ************************************************* Motor Control Functions ******************************************************************
// function for move motor in forward direction
void move_forward(){
  digitalWrite(left_motor1,LOW);
  digitalWrite(left_motor2,HIGH);
  digitalWrite(right_motor1,HIGH);
  digitalWrite(right_motor2,LOW);
}
// function for move motor in backward direction
void move_backward(){
  digitalWrite(left_motor1,HIGH);
  digitalWrite(left_motor2,LOW);
  digitalWrite(right_motor1,LOW);
  digitalWrite(right_motor2,HIGH);
}
// function for move motor in right direction
void move_right(){
  digitalWrite(left_motor1,LOW);
  digitalWrite(left_motor2,HIGH);
  digitalWrite(right_motor1,LOW);
  digitalWrite(right_motor2,HIGH);
  delay(delay_time);
  digitalWrite(left_motor2,LOW);
  digitalWrite(left_motor1,LOW);
  digitalWrite(right_motor1,LOW);
  digitalWrite(right_motor2,LOW);
}
// function for move motor in left direction
void move_left(){
  digitalWrite(left_motor1,HIGH);
  digitalWrite(left_motor2,LOW);
  digitalWrite(right_motor1,HIGH);
  digitalWrite(right_motor2,LOW);
  delay(delay_time);
  digitalWrite(left_motor2,LOW);
  digitalWrite(left_motor1,LOW);
  digitalWrite(right_motor1,LOW);
  digitalWrite(right_motor2,LOW);
}
// function for stop the robot
void robot_stop(){
  digitalWrite(left_motor2,LOW);
  digitalWrite(left_motor1,LOW);
  digitalWrite(right_motor1,LOW);
  digitalWrite(right_motor2,LOW);
}
