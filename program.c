#include <SoftwareSerial.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

#define GSM_TX 7
#define GSM_RX 8

SoftwareSerial gsmSerial(GSM_TX, GSM_RX);  

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);          
  gsmSerial.begin(9600);       

  delay(1000);
  sendSMS("System Ready: Accident Alert Activated");
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 10) { 
    sendSMS("Alert: Possible accident detected! Immediate attention needed.");
    delay(10000); 
  }

  delay(1000);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; 
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+918610585730\""); 
  delay(1000);
  gsmSerial.print(message);
  delay(500);
  gsmSerial.write(26); 
  delay(5000);
}
