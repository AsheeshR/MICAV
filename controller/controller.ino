#include <Servo.h> 
#include "driver.h"
#include "constants.h"

int ch1,thrust;
 
Servo esc1, esc2, esc3, esc4;

void setup()
{
  esc1.attach(A0);    esc1.write(20);
  esc2.attach(A1);    esc2.write(20);
  esc3.attach(A2);    esc3.write(20);
  esc4.attach(A3);    esc4.write(20);
  
  digitalWrite(2, LOW);//GND for ESC4
  digitalWrite(12, LOW);//GND for ESC
  
  delay(5000);
  
  pinMode(5, INPUT);

  Serial.begin(9600);
  
}


void loop()
{

  ch1 = pulseIn(5, HIGH, 25000);
  Serial.println(ch1);
  
  thrust = map(ch1, 1074, 1645, 71, 124);
  Serial.println(thrust);
  
  esc1.write(thrust);
  esc2.write(thrust);   
  esc3.write(thrust);
  esc4.write(thrust);
  
  delay(100);
  
}

