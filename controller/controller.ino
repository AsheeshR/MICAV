#include <Servo.h> 
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
  
  delay(10000);
  
  pinMode(PIN_THROTTLE, INPUT);
  pinMode(PIN_PITCH, INPUT);
  pinMode(PIN_ROLL, INPUT);
  
  Serial.begin(9600);
  
}


void loop()
{

  ch1 = pulseIn(PIN_THROTTLE, HIGH, 25000);
  ch3 = pulseIn(PIN_PITCH, HIGH, 25000);
  ch2 = pulseIn(PIN_ROLL, HIGH, 25000);
  
  Serial.print("Input Value: ");
  Serial.print(ch1);
  Serial.print("Input Value2: ");
  Serial.print(ch3);
  Serial.print("Input Value2: ");
  Serial.print(ch2);

  
  thrust1 = map(ch1, 1074, 1645, 1275, 2400);
  thrust2 = map(ch1, 1074, 1645, 1275, 2400);
  thrust3 = map(ch1, 1074, 1645, 1275, 2400);
  thrust4 = map(ch1, 1074, 1645, 1275, 2400);
  
  ch3 = ch3 / 10;
  ch2 = ch2 / 10;
  
  /*Pitch*/
  if(ch3>=114 && ch3<=134)
  {
    modifier_pitch=0;
    c1_pitch = MULTIPLIER_PITCH;
    c2_pitch = MULTIPLIER_PITCH;

  }  
  else if(ch3<=114)
  {
    modifier_pitch = map(ch3, 96, 114, 45, 1);
    c1_pitch = MULTIPLIER_PITCH;
    c2_pitch = -MULTIPLIER_PITCH;
  }
  else if(ch3>=134)
  {
    modifier_pitch = map(ch3, 134, 164, 1, 45);
    c1_pitch = -MULTIPLIER_PITCH;
    c2_pitch = MULTIPLIER_PITCH;
  }

  /*Roll*/
  if(ch2>=114 && ch2<=134)
  {
    modifier_roll=0;
    c1_roll = MULTIPLIER_ROLL;
    c2_roll = MULTIPLIER_ROLL;

  }  
  else if(ch2<=114)
  {
    modifier_roll = map(ch2, 96, 114, 45, 1);
    c1_roll = MULTIPLIER_ROLL;
    c2_roll = -MULTIPLIER_ROLL;
  }
  else if(ch2>=134)
  {
    modifier_roll = map(ch2, 134, 164, 1, 45);
    c1_roll = -MULTIPLIER_ROLL;
    c2_roll = MULTIPLIER_ROLL;
  }

  thrust1 = thrust1 + c1_pitch * modifier_pitch + c2_roll * modifier_roll;
  thrust2 = thrust2 + c1_pitch * modifier_pitch + c1_roll * modifier_roll;
  thrust3 = thrust3 + c2_pitch * modifier_pitch + c1_roll * modifier_roll;
  thrust4 = thrust4 + c2_pitch * modifier_pitch + c2_roll * modifier_roll;
  
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
