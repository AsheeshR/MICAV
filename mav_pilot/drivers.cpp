/* This file handles motors and input channels control */

#include "drivers.h"


static Servo esc[4];

void arm_motors()
{
    //Servo *esc = malloc(sizeof(Servo)*4);
    
    esc[0].attach(PIN_MOTOR0);    esc[0].writeMicroseconds(750);
    esc[1].attach(PIN_MOTOR1);    esc[1].writeMicroseconds(750);
    esc[2].attach(PIN_MOTOR2);    esc[2].writeMicroseconds(750);
    esc[3].attach(PIN_MOTOR3);    esc[3].writeMicroseconds(750);

//#ifndef DEBUG_SERIAL /* Watch out!! */
//    delay(3000);
//#endif

    //return esc;
}

void update_motors(/*Servo * esc[],*/ int16_t thrust[])
{


    thrust[0] = constrain(thrust[0],THRESHOLD_MOTOR0_MIN-25, THRESHOLD_MOTOR0_MAX);
    thrust[1] = constrain(thrust[1],THRESHOLD_MOTOR1_MIN-25, THRESHOLD_MOTOR1_MAX);
    thrust[2] = constrain(thrust[2],THRESHOLD_MOTOR2_MIN-25, THRESHOLD_MOTOR2_MAX);
    thrust[3] = constrain(thrust[3],THRESHOLD_MOTOR3_MIN-25, THRESHOLD_MOTOR3_MAX);

    esc[0].writeMicroseconds(thrust[0]);
    esc[1].writeMicroseconds(thrust[1]);
    esc[2].writeMicroseconds(thrust[2]);
    esc[3].writeMicroseconds(thrust[3]);

}


void cutoff_motors()
{
    esc[0].attach(PIN_MOTOR0);    esc[0].writeMicroseconds(750);
    esc[1].attach(PIN_MOTOR1);    esc[1].writeMicroseconds(750);
    esc[2].attach(PIN_MOTOR2);    esc[2].writeMicroseconds(750);
    esc[3].attach(PIN_MOTOR3);    esc[3].writeMicroseconds(750);
}

/*
void setup_channels()
{
    
    pinMode(PIN_THROTTLE, INPUT);
    pinMode(PIN_PITCH, INPUT);
    pinMode(PIN_ROLL, INPUT);
    pinMode(PIN_YAW, INPUT);
    
    pinMode(PIN_AUX1, INPUT);
    pinMode(PIN_AUX2, INPUT);
//    pinMode(PIN_AUTO, INPUT);
}
*/

/*
void update_channels(uint16_t channels[])
{

    channels[0] = pulseIn(PIN_THROTTLE, HIGH, 20000);
    channels[1] = pulseIn(PIN_YAW, HIGH, 20000);
    channels[2] = pulseIn(PIN_PITCH, HIGH, 20000);
    channels[3] = pulseIn(PIN_ROLL, HIGH, 20000);
  
//    channels[4] = pulseIn(PIN_AUX1, HIGH, 25000);
//    channels[5] = pulseIn(PIN_AUX2, HIGH, 25000);
//    channels[6] = pulseIn(PIN_AUTO, HIGH, 25000);

    channels[0] = constrain(channels[0], CHANNEL1_MIN, CHANNEL1_MAX);
    channels[1] = constrain(channels[1], CHANNEL2_MIN, CHANNEL2_MAX);
    channels[2] = constrain(channels[2], CHANNEL3_MIN, CHANNEL3_MAX);
    channels[3] = constrain(channels[3], CHANNEL4_MIN, CHANNEL4_MAX);

}
*/
/* ISR based Control Inputs */

volatile byte update = 0;


uint8_t tmode;
uint32_t tt1=0;
volatile uint16_t tvalue;

void updatethrottle() 
{
    tmode=PCintPort::pinState;  
    if(tmode)    tt1 = micros();
    else    tvalue = micros()-tt1;
    update = 1;
}

uint8_t ymode;
uint32_t yt1=0;
volatile uint16_t yvalue;

void updateyaw()
{  
  ymode=PCintPort::pinState;  
  if(ymode)    yt1 = micros();
  else yvalue = micros()-yt1;
  update = 1;
}

uint8_t rmode;
uint32_t rt1=0;
volatile uint16_t rvalue;

void updateroll() 
{  
    rmode=PCintPort::pinState;  
    if(rmode)   rt1 = micros();
    else    rvalue = micros()-rt1;
    update = 1;
}


uint8_t pmode;
uint32_t pt1=0;
volatile uint16_t pvalue;

void updatepitch() 
{  
    pmode=PCintPort::pinState;      
    if(pmode)    pt1 = micros();
    else pvalue = micros()-pt1;
    update = 1;
}



void setup_channels()
{
    pinMode(PIN_THROTTLE, INPUT); digitalWrite(PIN_THROTTLE, HIGH);
    PCintPort::attachInterrupt(PIN_THROTTLE, &updatethrottle, CHANGE);

    pinMode(PIN_PITCH, INPUT); digitalWrite(PIN_PITCH, HIGH);
    PCintPort::attachInterrupt(PIN_PITCH, &updatepitch, CHANGE);

    pinMode(PIN_ROLL, INPUT); digitalWrite(PIN_ROLL, HIGH);
    PCintPort::attachInterrupt(PIN_ROLL, &updateroll, CHANGE);

    pinMode(PIN_YAW, INPUT); digitalWrite(PIN_YAW, HIGH);
    PCintPort::attachInterrupt(PIN_YAW, &updateyaw, CHANGE);
    
//    pinMode(PIN_AUX1, INPUT);
//    pinMode(PIN_AUX2, INPUT);
//    pinMode(PIN_AUTO, INPUT);
}

void update_channels(uint16_t channels[])
{

    if(update == 0) return;

    /* else if(update == 1) */

    byte sregRestore = SREG; //save status register value
    cli(); // clear the global interrupt enable flag to disable interrupts
    update = 0;
    
    channels[0] = tvalue;//pulseIn(PIN_THROTTLE, HIGH, 20000);
    channels[1] = yvalue;//pulseIn(PIN_YAW, HIGH, 20000);
    channels[2] = pvalue;//pulseIn(PIN_PITCH, HIGH, 20000);
    channels[3] = rvalue;//pulseIn(PIN_ROLL, HIGH, 20000);
    
    SREG = sregRestore; // restore the status register to its previous value
    
//    channels[4] = pulseIn(PIN_AUX1, HIGH, 25000);
//    channels[5] = pulseIn(PIN_AUX2, HIGH, 25000);
//    channels[6] = pulseIn(PIN_AUTO, HIGH, 25000);

    channels[0] = constrain(channels[0], CHANNEL1_MIN, CHANNEL1_MAX);
    channels[1] = constrain(channels[1], CHANNEL2_MIN, CHANNEL2_MAX);
    channels[2] = constrain(channels[2], CHANNEL3_MIN, CHANNEL3_MAX);
    channels[3] = constrain(channels[3], CHANNEL4_MIN, CHANNEL4_MAX);
}
