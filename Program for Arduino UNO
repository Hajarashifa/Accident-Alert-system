#include <SoftwareSerial.h>

// Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); // SIM800L Tx & Rx is connected to Arduino #3 & #2

#define trigPin 4
#define echoPin 5
#define alarmPin 6

const String PHONE_NUMBER = "+916209403151"; // Replace with recipient number

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(alarmPin, OUTPUT);

  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
 
  // Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  sendATCommand("AT"); // Once the handshake test is successful, it will return OK
  sendATCommand("AT+CMGF=1"); // Configuring TEXT mode
}

void loop()
{
  while (mySerial.available())
  {
    Serial.write(mySerial.read()); // Print the response from the module
  }

  long time_duration, distance_in_cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time_duration = pulseIn(echoPin, HIGH);
  distance_in_cm = time_duration / 29 / 2;

  Serial.print("Distance: ");
  Serial.print(distance_in_cm);
  Serial.println(" cm");

  if (distance_in_cm <= 10)
  {
    Serial.println("Intruder detected!");
    activateAlarm();
    sendSMS(PHONE_NUMBER, "Intruder detected!"); // Send SMS
    makeCall(PHONE_NUMBER); // Make a call
    delay(5000); // Delay to prevent continuous triggering
  }
  else
  {
    deactivateAlarm();
  }

  delay(500);
}

void sendATCommand(const String& command)
{
  mySerial.println(command);
  delay(500);

  while (mySerial.available())
  {
    Serial.write(mySerial.read()); // Print the response from the module
  }
}

void sendSMS(const String& phoneNumber, const String& message)
{
  mySerial.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(1000);
  mySerial.println(message);
  delay(1000);
  mySerial.write(26); // Send Ctrl+Z character to indicate the end of the message
  delay(5000);

  while (mySerial.available())
  {
    Serial.write(mySerial.read()); // Print the response from the module
  }
}

void makeCall(const String& phoneNumber)
{
  mySerial.println("ATD" + phoneNumber + ";");
  delay(10000); // Delay for the call to connect (adjust as needed)
  mySerial.println("ATH"); // Hang up the call
}

void activateAlarm()
{
  digitalWrite(alarmPin, HIGH);
}

void deactivateAlarm()
{
  digitalWrite(alarmPin, LOW);
}
