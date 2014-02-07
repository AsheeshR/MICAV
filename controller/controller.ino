#include <Servo.h> 
#include <smoothing.h>
#include "driver.h"
#include "constants.h"

int ch1,ch3, ch2,thrust1, thrust2, thrust3, thrust4, modifier_pitch, modifier_roll;

int c1_pitch, c2_pitch, c1_roll, c2_roll;   
 
Servo esc1, esc2, esc3, esc4;

void setup()
{
  esc1.attach(A0);    esc1.writeMicroseconds(750);
  esc2.attach(A1);    esc2.writeMicroseconds(750);
  esc3.attach(A2);    esc3.writeMicroseconds(750);
  esc4.attach(A3);    esc4.writeMicroseconds(750);
  
//  digitalWrite(2, LOW);//GND for ESC4
 // digitalWrite(12, LOW);//GND for ESC
  
  //delay(10000);
  
  pinMode(PIN_THROTTLE, INPUT);
  pinMode(PIN_PITCH, INPUT);
  pinMode(PIN_ROLL, INPUT);
  
  Serial.begin(9600);
  
}


void loop()
{
  Serial.print(micros());
  Serial.print(",");
  //ch1 = pulseIn(PIN_THROTTLE, HIGH, 25000);
  if(Serial.available()>0)
  ch1=Serial.parseInt();
  ch3 = pulseIn(PIN_PITCH, HIGH, 25000);
  ch2 = pulseIn(PIN_ROLL, HIGH, 25000);
  

  Serial.print(ch1);
  Serial.print(",");
  Serial.println(micros());

  //Serial.print("Input Value2: ");
  //Serial.print(ch3);
  //Serial.print("Input Value2: ");
  //Serial.print(ch2);

  
    
  /*Pitch*/
  
  //Minimum Throttle Constraints
  if(ch1<=THRESHOLD_CHANNEL_THROTTLE_MIN)
  {
    thrust1 = thrust2 = thrust3 = thrust4 = THRESHOLD_CHANNEL_THROTTLE_MIN;
  }
  else if(ch1<=THRESHOLD_CHANNEL_THROTTLE_HOVER)
  {
    if(thrust1 > THRESHOLD_MOTOR_HOVER) thrust1 = THRESHOLD_MOTOR_HOVER;
    if(thrust2 > THRESHOLD_MOTOR_HOVER) thrust2 = THRESHOLD_MOTOR_HOVER;
    if(thrust3 > THRESHOLD_MOTOR_HOVER) thrust3 = THRESHOLD_MOTOR_HOVER;
    if(thrust4 > THRESHOLD_MOTOR_HOVER) thrust4 = THRESHOLD_MOTOR_HOVER; 
  }
  else if(ch1<=THRESHOLD_CHANNEL_THROTTLE_MAX)
  {
    if(thrust1 < THRESHOLD_MOTOR_HOVER) thrust1 = THRESHOLD_MOTOR_HOVER;
    if(thrust2 < THRESHOLD_MOTOR_HOVER) thrust2 = THRESHOLD_MOTOR_HOVER;
    if(thrust3 < THRESHOLD_MOTOR_HOVER) thrust3 = THRESHOLD_MOTOR_HOVER;
    if(thrust4 < THRESHOLD_MOTOR_HOVER) thrust4 = THRESHOLD_MOTOR_HOVER;
  }
  
  
  
  //Upper Limit Constraints -- Will apply to all cases
  
  thrust1 = (thrust1 > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust1;
  thrust2 = (thrust2 > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust2;
  thrust3 = (thrust3 > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust3;
  thrust4 = (thrust4 > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust4;
  
 
  
  esc1.write(thrust1);
  esc2.write(thrust2);
  esc3.write(thrust3);
  esc4.write(thrust4);
  
  delayMicroseconds(500); 
}
