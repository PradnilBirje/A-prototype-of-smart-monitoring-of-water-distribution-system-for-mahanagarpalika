#define BLYNK_TEMPLATE_ID "TMPLGc2JPCI-"
#define BLYNK_TEMPLATE_NAME "smart water"
#define BLYNK_AUTH_TOKEN "OL0PtchSTsYyW-bUqX8ObbqaMQhxEyj2"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "K50i";
char pass[] = "123456789";
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 19800;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);


#include <AccelStepper.h>
int pulse = D5;
int dir = D6;
int numberofSteps = 1000;
AccelStepper stepper(1,pulse,dir);
int pin0 = V0;
int pin1 = V1;


int startTime1;
int endTime1;
int startTime2;
int endTime2;

BLYNK_WRITE(V0) // Valve opening 
{
  int pinValue = param.asInt();
  Serial.print(pinValue);
  if (pinValue == 1)
  {
  stepper.moveTo(-20000);
  stepper.run();
    
  // stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition();  
  }
}


BLYNK_WRITE(V1) { // Valve CLOSING 
int pinValue = param.asInt();
Serial.print(pinValue);
if (pinValue == 1)
{
stepper.moveTo(20000);
stepper.run();
  
// stepper.stop(); // Stop as fast as possible: sets new target
stepper.runToPosition();  
}
}

BLYNK_WRITE(V2) // Valve opening 25
{
  int pinValue = param.asInt();
  Serial.print(pinValue);
  if (pinValue == 1)
  {
  stepper.moveTo(5000);
  stepper.run();
  
  // stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  }
}BLYNK_WRITE(V3) // Valve opening 50
{
  int pinValue = param.asInt();
  Serial.print(pinValue);
  if (pinValue == 1)
  {
  stepper.moveTo(10000);
  stepper.run();
  
  // stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  }
}
BLYNK_WRITE(V4) // Valve opening 75
{
  int pinValue = param.asInt();
  Serial.print(pinValue);
  if (pinValue == 1)
  {
  stepper.moveTo(15000);
  stepper.run();
  
  // stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  }
}

BLYNK_WRITE(V5) // Valve open 100
{
  int pinValue = param.asInt();
  Serial.print(pinValue);
  if (pinValue == 1)
  {
  stepper.moveTo(22000);
  stepper.run();
  
  // stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  }
}
BLYNK_WRITE(V6)// valve opening according to time
{
    int value = param.asInt();
    if(value == 1)
      stepper.moveTo(20000);
  stepper.run();
}


BLYNK_WRITE(V7)// valve closing according to time 
{
 startTime1 = param[0].asInt();
 endTime1 = param[1].asInt();
 if(startTime1 == 0 && endTime1 == 0)
 {
  stepper.moveTo(-22000);
  stepper.run();
  
 }
}

void setup()
{
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  stepper.setSpeed(700);
  Serial.begin(115200);
  
  pinMode(V0,OUTPUT);
  pinMode(V1,OUTPUT);
  Blynk.begin(auth,ssid,pass);
  Serial.begin(115200);
  delay(100);

  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  
 
  digitalWrite(pin0, HIGH);
  digitalWrite(pin1, HIGH);
  
  timeClient.begin();
 
   Blynk.begin(auth,ssid,pass);
}

void loop() {
  timeClient.update();
  int HH = timeClient.getHours();
  int MM = timeClient.getMinutes();
  int SS = timeClient.getSeconds();
  int server_time = 3600*HH + 60*MM + SS;
//    Serial.print(starttime);
   if(startTime1 == server_time)
   {
    BLYNK_WRITE(V0);
   }

   if(startTime2 == server_time)
   {
     BLYNK_WRITE(V1);
   }

  
   


  Blynk.run();
}
