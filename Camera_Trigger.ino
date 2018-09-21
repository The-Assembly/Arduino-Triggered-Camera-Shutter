
/*
 * created by Rui Santos, http://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
 *modified by Judhi Prasetyo for camera shutter control
 * 
 * 
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int trigPin = 8;    //Trig - green Jumper
int echoPin = 7;    //Echo - blue Jumper
int camPin = 13;
// camera will take picture if object is closer than this distance (in cm)
int cam_distance = 30;

long duration, cm, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(camPin, OUTPUT);
}
 
void loop()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose duration is the time (in microseconds) 
  // from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74; 

  Serial.print(cm);
  Serial.println("cm");

  if (cm <1) {
    Serial.println("---");
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, HIGH);
    delay(3);
    digitalWrite(echoPin, LOW);
    pinMode(echoPin, INPUT);
  }
  if (cm < cam_distance and cm > 0) { // additional codes by Judhi to trigger the camera
      digitalWrite(camPin, HIGH);
      delay(100);
      digitalWrite(camPin, LOW);
      delay(500);
      Serial.println("Taking picture!");
  }

  delay(50);
}
