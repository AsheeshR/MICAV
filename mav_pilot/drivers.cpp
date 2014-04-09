/* This file handles motors and input channels control */

#include "drivers.h"

/* Setup motors */

static Servo esc[4];

void arm_motors()
{
    //Servo *esc = malloc(sizeof(Servo)*4);
    
    esc[0].attach(PIN_MOTOR1);    esc[0].writeMicroseconds(750);
    esc[1].attach(PIN_MOTOR2);    esc[1].writeMicroseconds(750);
    esc[2].attach(PIN_MOTOR3);    esc[2].writeMicroseconds(750);
    esc[3].attach(PIN_MOTOR4);    esc[3].writeMicroseconds(750);
 
    delay(10000);
    
    //return esc;
}

void update_motors(/*Servo * esc[],*/ uint16_t thrust[])
{
    /* Upper limit constraints */
    thrust[0] = (thrust[0] > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust[0];
    thrust[1] = (thrust[1] > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust[1];
    thrust[2] = (thrust[2] > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust[2];
    thrust[3] = (thrust[3] > THRESHOLD_MOTOR_MAX) ? THRESHOLD_MOTOR_MAX : thrust[3];

    esc[0].write(thrust[0]);
    esc[1].write(thrust[1]);
    esc[2].write(thrust[2]);
    esc[3].write(thrust[3]);

}


void cutoff_motors()
{
    esc[0].attach(PIN_MOTOR1);    esc[0].writeMicroseconds(750);
    esc[1].attach(PIN_MOTOR2);    esc[1].writeMicroseconds(750);
    esc[2].attach(PIN_MOTOR3);    esc[2].writeMicroseconds(750);
    esc[3].attach(PIN_MOTOR4);    esc[3].writeMicroseconds(750);
}


void setup_channels()
{
    
    pinMode(PIN_THROTTLE, INPUT);
    pinMode(PIN_PITCH, INPUT);
    pinMode(PIN_ROLL, INPUT);
    pinMode(PIN_YAW, INPUT);
    
    pinMode(PIN_AUX1, INPUT);
    pinMode(PIN_AUX2, INPUT);
    pinMode(PIN_AUTO, INPUT);


}


void update_channels(uint16_t channels[])
{

    channels[0] = pulseIn(PIN_THROTTLE, HIGH, 25000);
    channels[1] = pulseIn(PIN_PITCH, HIGH, 25000);
    channels[2] = pulseIn(PIN_ROLL, HIGH, 25000);
    channels[3] = pulseIn(PIN_YAW, HIGH, 25000);
    
    
    channels[4] = pulseIn(PIN_AUX1, HIGH, 25000);
    channels[5] = pulseIn(PIN_AUX2, HIGH, 25000);
    channels[6] = pulseIn(PIN_AUTO, HIGH, 25000);

}

