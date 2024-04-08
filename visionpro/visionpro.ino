
#include <SoftwareSerial.h>
#define trig  4
#define echo  6
#define buzz  3




#define TOUCHPIN 2
int count = 0, touch;
long long int lasttouch = 0;
#define THRESHOLD 700


#define GSM_TX 7
#define GSM_RX 8


void buzzon();
void buzzoff();
void checkDistance();
void sendSMS();
void checkEmergency();
SoftwareSerial gsmSerial(GSM_TX, GSM_RX);

void setup() {
  pinMode(touch, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);  pinMode(TOUCHPIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  gsmSerial.begin(38400);
  buzzon();
  delay(100);
  buzzoff();
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  checkDistance();
  checkEmergency();
}
void checkEmergency() {

  touch = digitalRead(TOUCHPIN);
  Serial.println(count);
  if (touch == 1) {
    int mill = millis();//current millis

    if (lasttouch == 0) { //first time
      lasttouch = mill;//first time

    }

    else {
      if ((mill - lasttouch) < THRESHOLD)//if this touch and last touch are less than threshol time diff
      {
      } else {
        count = 0;
      }
    }
    count++;
    while (digitalRead(TOUCHPIN) == 1) {
      delay(10);
    }
    lasttouch = millis();

  }
  if (count == 3) {
    sendSMS();
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(10);
    count = 0;
  }
  if (count != 3)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }



  if ((millis() - lasttouch) > THRESHOLD) {
    count = 0;
  }


}
void checkDistance() {
  int t = digitalRead(touch);
  unsigned long pulseTime;                          //Create a variable to store the pulse travel time
  int distance;                                     //Create a variable to store the calculated distance
  digitalWrite(trig, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pulseTime = pulseIn(echo, HIGH);         //Measure the time for the pulse to return
  distance  = pulseTime / 29 / 2;         //Calculate the object distance based on the pulse time
  Serial.println(distance);
  if (distance < 90 && distance >= 80)
  {
    buzzon();
    delay(450);
    buzzoff();
    delay(450);
  }
  if (distance < 80 && distance >= 70)
  {
    buzzon();
    delay(400);
    buzzoff();
    delay(400);
  }
  if (t == 1)
  {
    delay(100);
    count++;
  }
  if (count == 3)
  {
    count = 0;
  }

  if (distance < 70 && distance >= 60)
  {
    buzzon();
    delay(350);
    buzzoff();
    delay(350);
  }
  if (distance < 60 && distance >= 50)
  {
    buzzon();
    delay(300);
    buzzoff();
    delay(300);
  }

  if (distance < 50 && distance >= 40)
  {
    buzzon();
    delay(250);
    buzzoff();
    delay(250);
  }

  if (distance < 40 && distance >= 30)
  {
    buzzon();
    delay(200);
    buzzoff();
    delay(200);
  }

  if (distance < 30 && distance >= 20)
  {
    buzzon();
    delay(150);
    buzzoff();
    delay(150);
  }
  if (distance < 20)
  {
    buzzon();
  }
  else
  {
    buzzoff();
  }

}
void buzzon()
{
  digitalWrite(buzz, HIGH);

}
void buzzoff()
{
  digitalWrite(buzz, LOW);
}
void sendSMS() {
  Serial.println("Sending message");
  String message = "please help me i'm in danger";
  String encodeMobile = "AT+CMGS=\"+918897008307\"\r\n"; // Replace +1234567890 with the recipient's phone number
  gsmSerial.print(encodeMobile);
  delay(1000);
  gsmSerial.print(message);
  gsmSerial.print(0x1A);
}
