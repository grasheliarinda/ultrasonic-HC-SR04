
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <virtuabotixRTC.h>
//Ultrasonic
#define trigPin 3
#define echoPin 4
long duration;
int distance;

//SD Card
File myFile;
int pinCS = 10; // Pin 10 on Arduino Uno

//Real Time Clock
virtuabotixRTC myRTC(5, 6, 7);

void setup() {  
  Serial.begin(9600);
  // Ultrasonic
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(30, 07, 9, 7, 24, 7, 2021);
  
  //SD Card
  pinMode(pinCS, OUTPUT);
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

}

void loop() {
  //Ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2 ;
  Serial.print(distance);
  Serial.println(" cm");
  
  //Real Time Clock
  myRTC.updateTime();
  String Date = myRTC.dayofmonth+String("/")+myRTC.month+String("/")+ myRTC.year+String(" ");
  String Time = myRTC.hours+String(":")+myRTC.minutes+String(":")+myRTC.seconds;
  Serial.print(Date);
  Serial.println(Time);
 
  //SD Card
  myFile = SD.open("Data.txt", FILE_WRITE);
  if (myFile) {    
  myFile.print(Date);
  myFile.println(Time);

  myFile.print(distance);
  myFile.print(" cm");    
  myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  delay(1000);
}
