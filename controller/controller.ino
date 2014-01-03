#include <Servo.h> 
#include "driver.h"
#include "constants.h"

int ch1,ch2,thrust;

int start_low, start_high, disable;
 
Servo esc1, esc2, esc3, esc4;

void setup()
{
  esc1.attach(A0);    esc1.writeMicroseconds(750);
  esc2.attach(A1);    esc2.writeMicroseconds(750);
  esc3.attach(A2);    esc3.writeMicroseconds(750);
  esc4.attach(A3);    esc4.writeMicroseconds(750);
  
  digitalWrite(2, LOW);//GND for ESC4
  digitalWrite(12, LOW);//GND for ESC
  
  delay(10000);
  
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  
  Serial.begin(9600);
  disable=0;
  
}


void loop()
{

  ch1 = pulseIn(5, HIGH, 25000);
  ch2 = pulseIn(6, HIGH, 25000);
  Serial.print("Input Value: ");
  Serial.print(ch1);
  Serial.print("Input Value2: ");
  Serial.print(ch2);
  
  if(ch2<=1100)  
  {
    disable=1;
    thrust=750;
    delay(10);
  }
  else if(ch2>=1500) disable=0;
  
  if(disable==0)
  {
    thrust = map(ch1, 950, 1600, 140, 240);
    thrust=thrust*10;
  }
  
  Serial.print(" Output Pulse:");
  Serial.println(thrust);
  
  esc1.write(thrust);
  esc2.write(thrust);
  esc3.write(thrust);
  esc4.write(thrust);
  
  /*if(ch1<=1100 && disable==0)
  {
    if(start_low < millis()-5000)
    {
      start_low=millis();
    }
    else if(start_low > millis()-5000 && start_low < millis()-6000)
    { 
      thrust=600;
      disable=1;
    }
  }
  else if(ch1<=1100 && disable==1)
  {
    if(start_high < millis()-5000)
    {
      start_high=millis();
    }
    else if(start_low > millis()-5000 && start_low < millis()-6000)
    { 
      disable=0;
    }
  }*/
  
  delay(10); 
}
