//eddy! <3

#include <Servo.h>
#include <SoftwareSerial.h>

Servo servoL;
Servo servoR;
char data = 0;
SoftwareSerial ble(0,1); //rx and tx

const int buzzPin = 12;

void setup() 
{
  servoL.attach(7);
  servoR.attach(9);
  pinMode(buzzPin, OUTPUT);
  ble.begin(9600);
  Serial.begin(9600);

  Serial.println("AT");
}

void loop() 
{
  //90 = stationary (doesn't mean it stops moving, it just writes to stay in that same place)
  //for servo Right: 180 = forwards
  //for servo Left: 0 = forwards

  if(ble.available() > 0)
  {
    data = ble.read();
    Serial.println(data);
    
    if(data=='a'){forward();}
    else if(data=='b'){left();}
    else if(data=='c'){backward();}
    else if(data=='d'){right();}
    else{stationary();}

    if(data=='G'){horn();}
  }
}

void forward()
{
  Serial.println("going forwards!");
  delay(5);
  servoR.write(180);
  servoL.write(0);
}

void backward()
{
  Serial.println("going backwards!");
  delay(5);
  servoR.write(0);
  servoL.write(180);
}

void left()
{
  Serial.println("going left!");
  delay(5);
  servoR.write(180);
  servoL.write(180);
}

void right()
{
  Serial.println("going right!");
  delay(5);
  servoR.write(0);
  servoL.write(0);
}

void stationary()
{
  Serial.println("stop!");
  delay(5);
  servoR.write(90);
  servoL.write(90);
}

void horn()
{
  tone(buzzPin, 1000, 1000);
}
