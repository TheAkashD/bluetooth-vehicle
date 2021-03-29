#include <Servo.h>
#include <SoftwareSerial.h>

Servo servoL;
Servo servoR;
char data = 0;

SoftwareSerial ble(0,1); //rx and tx
// software serial may be overkill esp. since this is BLE on RX and TX pins naturally anyway ???? but ok

//NOW USE Serial1

const int buzzPin = 12; //attach buzzer here

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

    if(data=='w'){forward();} //switch case? but if im doing differential drive this should not be the case.
    else if(data=='a'){left();}
    else if(data=='s'){backward();}
    else if(data=='d'){right();}
    
    else if(data=='e'){horn();}
    else if(data=='x'){stationary();}

    // INSTALL DIFFERENTIAL DRIVE INTO THIS IN ORDER TO STEER AND DRIVE //
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
  //tone(buzzPin, 1000, 1000);

  digitalWrite(buzzPin, HIGH);
}
