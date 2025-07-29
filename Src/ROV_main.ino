#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX for Raspberry Pi Pico

Servo myservo;  
int potpin = A5;  
int val;    

#define joystickX1  A0
#define joystickY1  A1
#define joystickX2  A2
#define joystickY2  A3

#define Thrust_pwm1  2
#define Thrust_pwm2  3
#define Yaw_pwm1  4
#define Yaw_pwm2  5
#define Pitch_pwm1  6
#define Pitch_pwm2  7
#define Roll_pwm1  8
#define Roll_pwm2  9

int motor_controlX1;
int motor_controlY1;
int motor_controlX2;
int motor_controlY2;

void setup() {
  myservo.attach(12);

  pinMode(Thrust_pwm1, OUTPUT);
  pinMode(Thrust_pwm2, OUTPUT);
  pinMode(Yaw_pwm1, OUTPUT);
  pinMode(Yaw_pwm2, OUTPUT);
  pinMode(Pitch_pwm1, OUTPUT);
  pinMode(Pitch_pwm2, OUTPUT);
  pinMode(Roll_pwm1, OUTPUT);
  pinMode(Roll_pwm2, OUTPUT);

  Serial.begin(9600);
  delay(500);
}

void loop() {
  // Read potentiometer and map to servo angle//
  val = analogRead(potpin);            
  val = map(val, 0, 1023, 0, 180);    
  myservo.write(90); 
  delay(15);  

  if (Serial.available()){
    String command = Serial.readStringUntil('\n');
        Serial.println(command);
        if (command == "M1- M2-") {
            digitalWrite(Thrust_pwm1, HIGH);
            digitalWrite(Thrust_pwm2, LOW);
            digitalWrite(Yaw_pwm1, HIGH);
            digitalWrite(Yaw_pwm2, LOW);
        } else if (command == "M1+ M2+") {
            digitalWrite(Thrust_pwm1, LOW);
            digitalWrite(Thrust_pwm2, HIGH);
            digitalWrite(Yaw_pwm1, HIGH);
            digitalWrite(Yaw_pwm2, LOW);
        } else if (command == "M1+ M2-") {
            digitalWrite(Thrust_pwm1, HIGH);
            digitalWrite(Thrust_pwm2, LOW);
            digitalWrite(Yaw_pwm1, HIGH);
            digitalWrite(Yaw_pwm2, LOW);
        } else if (command == "M1- M2+") {
            digitalWrite(Thrust_pwm1, LOW);
            digitalWrite(Thrust_pwm2, HIGH);
            digitalWrite(Yaw_pwm1, HIGH);
            digitalWrite(Yaw_pwm2, LOW);
        }
  
  
  else{
  // divide joystick reading by 2//
  motor_controlX1 = analogRead(joystickX1) >> 1; // Scale to 0-511
  motor_controlY1 = analogRead(joystickY1) >> 1; // Scale to 0-511

  motor_controlX2 = analogRead(joystickX2) >> 1; // Scale to 0-511
  motor_controlY2 = analogRead(joystickY2) >> 1; // Scale to 0-511

  //Convert joysticks reading into Throttle, Yaw, Roll and Pitch//

  // Throttle Control (Y-axis)
  int throttleA = 0, throttleB = 0;
  if (motor_controlY1 > 320) {
    throttleA = motor_controlY1 - 256; // Forward thrust
    throttleB = motor_controlY1 - 256; // Forward thrust
  } else if (motor_controlY1 < 150) {
    throttleA = -(255 - motor_controlY1); // Reverse thrust
    throttleB = -(255 - motor_controlY1); // Reverse thrust
  }

  // Yaw Control (X-axis)
  int yawA = 0, yawB = 0;
  if (motor_controlX1 > 320) {
    yawA = motor_controlX1 - 256; // Positive yaw
    yawB = motor_controlX1 - 256;
  } else if (motor_controlX1 < 150) {
    yawA = -(255 - motor_controlX1); // Negative yaw
    yawB = -(255 - motor_controlX1);
  }

    // Roll Control (X-axis)
  int rollA = 0, rollB = 0;
  if (motor_controlX2 > 320) {
    rollA = motor_controlX2 - 256; // Positive yaw
    rollB = motor_controlX2 - 256;
  } else if (motor_controlX2 < 150) {
    rollA = -(255 - motor_controlX2); // Negative yaw
    rollB = -(255 - motor_controlX2);
  }

      // Pitch Control (Y-axis)
  int PitchA = 0, PitchB = 0;
  if (motor_controlY2 > 320) {
    PitchA = motor_controlY2 - 256; // Positive yaw
    PitchB = motor_controlY2 - 256;
  } else if (motor_controlY2 < 150) {
    PitchA = -(255 - motor_controlY2); // Negative yaw
    PitchB = -(255 - motor_controlY2);
  }

  // Combine throttle and yaw for  motorA, B//
  int motorA = constrain(throttleA + yawA, -255, 255);
  int motorB = constrain(throttleB - yawB, -255, 255);

  // Combine pitch and roll for each motorC, D//
  int motorC = constrain(PitchA + rollA, -255, 255);
  int motorD = constrain(PitchB - rollB, -255, 255);

  //Motor PWM and direction control logic//

  // Set motor A
  if (motorA > 0) {
    analogWrite(Thrust_pwm1, motorA);
    digitalWrite(Thrust_pwm2, LOW);
  } else if (motorA < 0) {
    analogWrite(Thrust_pwm2, -motorA);
    digitalWrite(Thrust_pwm1, LOW);
  } else {
    digitalWrite(Thrust_pwm1, LOW);
    digitalWrite(Thrust_pwm2, LOW);
  }

  // Set motor B
  if (motorB > 0) {
    analogWrite(Yaw_pwm1, motorB);
    digitalWrite(Yaw_pwm2, LOW);
  } else if (motorB < 0) {
    analogWrite(Yaw_pwm2, -motorB);
    digitalWrite(Yaw_pwm1, LOW);
  } else {
    digitalWrite(Yaw_pwm1, LOW);
    digitalWrite(Yaw_pwm2, LOW);
  }

    // Set motor C
  if (motorC > 0) {
    analogWrite(Pitch_pwm1, motorC);
    digitalWrite(Pitch_pwm2, LOW);
  } else if (motorC < 0) {
    analogWrite(Pitch_pwm2, -motorC);
    digitalWrite(Pitch_pwm1, LOW);
  } else {
    digitalWrite(Pitch_pwm1, LOW);
    digitalWrite(Pitch_pwm2, LOW);
  }

    // Set motor D
  if (motorD > 0) {
    analogWrite(Roll_pwm1, motorD);
    digitalWrite(Roll_pwm2, 0);
  } else if (motorD < 0) {
    analogWrite(Roll_pwm2, -motorD);
    digitalWrite(Roll_pwm1, 0);
  } else {
    digitalWrite(Roll_pwm1, 0);
    digitalWrite(Roll_pwm2, 0);
  }
  }
  }
}


