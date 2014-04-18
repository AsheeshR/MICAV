#include <microsmooth.h>
#include <stdint.h>
#include <Servo.h> 
//#include "smoothing.h"
#include "driver.h"
#include "constants.h"

int ch1,ch3, ch2, thrust, modifier_pitch, modifier_roll;

int c1_pitch, c2_pitch, c1_roll, c2_roll;   
uint16_t *history;

Servo esc1, esc2, esc3, esc4;

void setup()
{
  esc1.attach(A0);    esc1.writeMicroseconds(750);
  esc2.attach(A1);    esc2.writeMicroseconds(750);
  esc3.attach(A2);    esc3.writeMicroseconds(750);
  esc4.attach(A3);    esc4.writeMicroseconds(750);
  history=ms_init(KZA);
//  digitalWrite(2, LOW);//GND for ESC4
 // digitalWrite(12, LOW);//GND for ESC
  
  //delay(10000);
  
  pinMode(PIN_THROTTLE, INPUT);
  pinMode(PIN_PITCH, INPUT);
  pinMode(PIN_ROLL, INPUT);
  Serial.begin(9600);
  
}

unsigned long t1,t2;
int ch1_smooth;
void loop()
{
  ch1 = pulseIn(PIN_THROTTLE, HIGH, 20000);    //Experimentally obtained value for minimum time out
  t1=micros();
  //Serial.print(millis());
  //Serial.print(",");
  //Serial.print(ch1);
  t2=micros();
  Serial.print(t1);
  Serial.print(",");  
  Serial.print(ch1);
  Serial.print(",");
  Serial.print(t2);
  Serial.print(",");
  Serial.println(ch1_smooth);
  //Serial.print(millis());
  //Serial.print(",");
  
  //Serial.println(ch1);
  
 // ch3 = pulseIn(PIN_PITCH, HIGH, 25000);
 // ch2 = pulseIn(PIN_ROLL, HIGH, 25000);
  
  //Serial.print("Input Value: ");
  //Serial.print(ch1);
//  Serial.print("Input Value2: ");
//  Serial.print(ch3);
//  Serial.print("Input Value2: ");
//  Serial.print(ch2); 
   
  
  esc1.write(thrust);
//  esc2.write(thrust);
//  esc3.write(thrust);
//  esc4.write(thrust);
  
  delayMicroseconds(500); 
}
