#include <PinChangeInt.h>

// PinChangeIntExample, version 1.1 Sun Jan 15 06:24:19 CST 2012
// See the Wiki at http://code.google.com/p/arduino-pinchangeint/wiki for more information.
//-------- define these in your sketch, if applicable ----------------------------------------------------------
// You can reduce the memory footprint of this handler by declaring that there will be no pin change interrupts
// on any one or two of the three ports.  If only a single port remains, the handler will be declared inline
// reducing the size and latency of the handler.
//#define NO_PORTB_PINCHANGES // to indicate that port b will not be used for pin change interrupts
//#define NO_PORTC_PINCHANGES // to indicate that port c will not be used for pin change interrupts
// #define NO_PORTD_PINCHANGES // to indicate that port d will not be used for pin change interrupts
// if there is only one PCInt vector in use the code can be inlined
// reducing latency and code size
// define DISABLE_PCINT_MULTI_SERVICE below to limit the handler to servicing a single interrupt per invocation.
// #define       DISABLE_PCINT_MULTI_SERVICE
//-------- define the above in your sketch, if applicable ------------------------------------------------------
#define PINMODE
#include <PinChangeInt.h>

// This example demonstrates a configuration of 3 interrupting pins and 2 interrupt functions.
// All interrupts are serviced immediately, but one of the pins (pin 4) will show you immediately
// on the Terminal.  The other function connected to 2 pins sets an array member that is queried in loop().
// You can then query the array at your leisure.
// This makes loop timing non-critical.

// Add more Pins at your leisure.
// For the Analog Input pins used as digital input pins, and you can use 14, 15, 16, etc.
// or you can use A0, A1, A2, etc. (the Arduino code comes with #define's
// for the Analog Input pins and will properly recognize e.g., pinMode(A0, INPUT);
#define PIN1 3
#define PIN2 5
#define PIN3 6
#define PIN4 9

//uint8_t latest_interrupted_pin;
//uint8_t interrupt_count[20]={0}; // 20 possible arduino pins

uint8_t mode;
uint32_t t1=0, t2=0;
volatile uint32_t value;

void updatethrottle() {
  
  mode=PCintPort::pinState;  
  
  if(mode)
  {
    t1 = micros();
  }
  else
  {
    //t2 = micros();
    value = micros()-t1;
  }

}

uint8_t ymode;
uint32_t yt1=0, yt2=0;
volatile uint32_t yvalue;

void updateyaw() {
  
  ymode=PCintPort::pinState;  
  
  if(ymode)
  {
    yt1 = micros();
  }
  else
  {
    //t2 = micros();
    yvalue = micros()-yt1;
  }

}

uint8_t rmode;
uint32_t rt1=0, rt2=0;
volatile uint32_t rvalue;

void updateroll() {
  
  rmode=PCintPort::pinState;  
  
  if(rmode)
  {
    rt1 = micros();
  }
  else
  {
    //t2 = micros();
    rvalue = micros()-rt1;
  }

}


uint8_t pmode;
uint32_t pt1=0, pt2=0;
volatile uint32_t pvalue;

void updatepitch() {
  
 pmode=PCintPort::pinState;  
  
  if(pmode)
  {
    pt1 = micros();
  }
  else
  {
    //t2 = micros();
    pvalue = micros()-pt1;
  }

}




// You can assign any number of functions to any number of pins.
// How cool is that?
//void pin3func() {
//  Serial.print("Pin "); Serial.print(PIN3, DEC); Serial.println("!");
//}

//void pin4func() {
//  Serial.print("Pin "); Serial.print(PIN4, DEC); Serial.println("!");
//}

void setup() {
  pinMode(PIN1, INPUT); digitalWrite(PIN1, HIGH);
  PCintPort::attachInterrupt(PIN1, &updatethrottle, CHANGE);  // add more attachInterrupt code as required
  pinMode(PIN2, INPUT); digitalWrite(PIN2, HIGH);
  PCintPort::attachInterrupt(PIN2, &updateyaw, CHANGE);
  pinMode(PIN3, INPUT); digitalWrite(PIN3, HIGH);
  PCintPort::attachInterrupt(PIN3, &updateroll, CHANGE);
  pinMode(PIN4, INPUT); digitalWrite(PIN4, HIGH);
  PCintPort::attachInterrupt(PIN4, &updatepitch, CHANGE);
  Serial.begin(57600);
  Serial.println("---------------------------------------");
}

uint32_t i, start, finish;
void loop() {
  start = millis();
  uint8_t count;
//  Serial.print(".");
  delay(5);
  Serial.println("YPR:");
  Serial.println(value);
  Serial.println(yvalue);
  Serial.println(pvalue);
  Serial.println(rvalue);
  /*for (i=0; i < 20; i++) {
    if (interrupt_count[i] != 0) {
      count=interrupt_count[i];
      interrupt_count[i]=0;
      Serial.print("Count for pin ");
      if (i < 14) {
        Serial.print("D");
        Serial.print(i, DEC);
      } else {
        Serial.print("A");
        Serial.print(i-14, DEC);
      }
      Serial.print(" is ");
      Serial.println(count, DEC);
    }
  }*/
  finish = millis();
  Serial.println(finish - start);
}

