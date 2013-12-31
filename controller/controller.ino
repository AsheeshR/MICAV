#include <Servo.h> 
#include "driver.h"
#include "constants.h"

int ch1,ch4,thrust1, thrust2, thrust3, thrust4, yaw_modifier;

int c1, c2;   
 
Servo esc1, esc2, esc3, esc4;

void setup()
{
  esc1.attach(A0);    esc1.writeMicroseconds(750);
  esc2.attach(A1);    esc2.writeMicroseconds(750);
  esc3.attach(A2);    esc3.writeMicroseconds(750);
  esc4.attach(A3);    esc4.writeMicroseconds(750);
  
//  digitalWrite(2, LOW);//GND for ESC4
 // digitalWrite(12, LOW);//GND for ESC
  
  delay(10000);
  
  pinMode(PIN_THROTTLE, INPUT);
  pinMode(PIN_YAW, INPUT);
  
  Serial.begin(9600);
  
}


void loop()
{

  ch1 = pulseIn(PIN_THROTTLE, HIGH, 25000);
  ch4 = pulseIn(PIN_YAW, HIGH, 25000);
  Serial.print("Input Value: ");
  Serial.print(ch1);
  Serial.print("Input Value2: ");
  Serial.print(ch4  );
  
  thrust1 = map(ch1, 1074, 1645, 1275, 2400);
  thrust2 = map(ch1, 1074, 1645, 1275, 2400);
  thrust3 = map(ch1, 1074, 1645, 1275, 2400);
  thrust4 = map(ch1, 1074, 1645, 1275, 2400);
  
  ch4 = ch4 / 10;
  if(ch4>=120 && ch4<=145)
  {
    yaw_modifier=0;
    c1 = MULTIPLIER_YAW;
    c2 = MULTIPLIER_YAW;

  }
  else if(ch4<=120)
  {
    yaw_modifier = map(ch4, 95, 120, 90, 1);
    c1 = MULTIPLIER_YAW;
    c2 = -MULTIPLIER_YAW;
  }
  else if(ch4>=145)
  {
    yaw_modifier = map(ch4, 145, 165, 1, 90);
    c1 = -MULTIPLIER_YAW;
    c2 = MULTIPLIER_YAW;
  }
  
  thrust1 = thrust1 + c1 * yaw_modifier;
  thrust2 = thrust2 + c2 * yaw_modifier;
  thrust3 = thrust3 + c1 * yaw_modifier;
  thrust4 = thrust4 + c2 * yaw_modifier;
  
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
  
  
  Serial.print(" Output Pulse:");
  Serial.print(thrust1);
  Serial.print(thrust2);
  Serial.print(thrust3);
  Serial.println(thrust4);
  
  esc1.write(thrust1);
  esc2.write(thrust2);
  esc3.write(thrust3);
  esc4.write(thrust4);
  
  delay(100); 
}
