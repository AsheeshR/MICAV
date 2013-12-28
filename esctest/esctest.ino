#include <Servo.h> 
 
Servo esc1, esc2, esc3, esc4;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int t;

char b;

 
void setup() 
{ 
  pinMode(12, OUTPUT);
  esc1.attach(A0);  // attaches the servo on pin 9 to the servo object
  esc2.attach(A1);  // attaches the servo on pin 9 to the servo object
  esc3.attach(A2);  // attaches the servo on pin 9 to the servo object
  esc4.attach(A3);  // attaches the servo on pin 9 to the servo object
  
  
  esc1.writeMicroseconds(20);
  esc2.writeMicroseconds(20);
  esc3.writeMicroseconds(20);
  esc4.writeMicroseconds(20);

  Serial.begin(9600);
  Serial.println("Started!");
  t=500;
  
  digitalWrite(12, LOW);
//  esc.write(0);
//  delay();
  
} 


void loop() 
{
   
    while(Serial.available()==0)
    {
       esc1.writeMicroseconds(t);  
       esc2.writeMicroseconds(t);  
       esc3.writeMicroseconds(t);  
       esc4.writeMicroseconds(t);  
       delayMicroseconds(100);
    }
    
    b=Serial.read();
    
    if(b=='1')
    {
       t=t+25;
    }
    else if(b=='2')
    {
     
      t=t-25;
      if(t<0)
      t=0;
      
    }else if(b=='3')
    {
      t=700;
    }
    
    Serial.println(t);
}
