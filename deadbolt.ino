#include <Servo.h>

//Led
int soundPin = 11;
int greenPin = 12;
int redPin = 13;

//Button
const byte buttonPin = 2;
bool b = true;

//Servo
Servo myservo;
int servoPos;

//BT
char junk;
String inputString="";

void setup()
{
  //Sound
  pinMode(soundPin, OUTPUT);

  //Led
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);

  //Button
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), swap, RISING);

  //BT
  Serial.begin(9600);

  //Servo
  myservo.attach(9);
  myservo.write(180);
  digitalWrite(greenPin, HIGH);
}

void loop()
{
  if (b) 
  {
    unlock();
    doubleBeep();
    doubleBeep();
    doubleBeep();
    doubleBeep();
    doubleBeep();
    lock();
    b = false;
  }

  if(Serial.available())
  {
    while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
      
    Serial.println(inputString);
    while (Serial.available() > 0)  
      junk = Serial.read();
  
    if(inputString == "#unlock;") unlock();
    if(inputString == "#lock;") lock();
    beep();
    inputString = "";
  }
}

//Func to run when button press
void swap()
{
  b = !b;
}

void lock()
{
  myservo.write(180);
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, LOW);
}

void unlock()
{
  myservo.write(0);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, HIGH);
}

void doubleBeep()
{
  tone(soundPin, 1500, 100);
  delay(200);
  tone(soundPin, 2500, 100);
  delay(800);
}

void beep()
{
  tone(soundPin, 2500, 100);
  delay(1000);
}


