int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;
int ch7;

#include "Servo.h"

Servo ch7s;

void setup() {

  pinMode(5, INPUT); // Set our input pins as such
  pinMode(6, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);

//  ch7s.attach(3);
  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  ch1 = pulseIn(3, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(5, HIGH, 25000); // each channel
  ch3 = pulseIn(6, HIGH, 25000);
  ch4 = pulseIn(9, HIGH, 25000);
//  ch5 = pulseIn(3, HIGH, 25000); 
 // ch6 = pulseIn(2, HIGH, 25000);*/
  //ch7 = pulseIn(3, HIGH);
//  ch7 = ch7s.read();
  Serial.print("Channel 1:"); // Print the value of */
  Serial.print(ch1);        // each channel

  Serial.print(" Channel 2:");
  Serial.print(ch2);

  Serial.print(" Channel 3:");
  Serial.print(ch3);
  
  Serial.print(" Channel 4:");
  Serial.println(ch4);

/*  Serial.print(" Channel 5:");
  Serial.println(ch5);

  Serial.print("Channel 6:"); // Print the value of 
  Serial.print(ch6);        // each channel

  Serial.print("Channel 7:"); // Print the value of 
  Serial.println(ch7);        // each channel
*/
  //delay(10); // I put this here just to make the terminal 
              // window happier
}
