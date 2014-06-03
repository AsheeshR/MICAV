/* Global Header Files */
#define PINMODE

#include <Wire.h>
#include <Servo.h>
//#include <Serial.h>
#include <Arduino.h>
//#include <PinChangeInt.h>

#define DEBUG_SERIAL 1

/* Project Header Files */
#include "config.h"
#include "PID.h"
#include "drivers.h"
//#include "PID.h"
#include "controller.h"
#include "Razor_AHRS.h"
//#include "pilot.h"
#include <PinChangeInt.h>

float ypr2[3];



void start_pilot()
{
    int st;
    //Initialize IMU
#ifdef DEBUG_SERIAL    
    Serial.println("IMU Setup");
#endif
    imu_setup();
    
    st = millis();
    while(millis()-st<2000)
	imu_loop(ypr2); /*Since initial readings were garbage */

#ifdef DEBUG_SERIAL    
    Serial.println("Arm Motors");
#endif
    arm_motors();
#ifdef DEBUG_SERIAL    
    Serial.println("Controller Setup");
#endif
    setup_channels();
    //Initialize states
    //Initialize control system
    
    delay(100);
    
    Serial.println("First Two Sets");
    imu_loop(ypr2);
    update_state(ypr2); /* To correct the initial dY dP dR values. This should not be reflected in the output state */

    delay(100);
    imu_loop(ypr2);
    update_state(ypr2); /* To correct the initial dY dP dR values. This should not be reflected in the output state */
    
}


//int flag = 1;
int32_t t = 0;

void update_pilot()
{
    //Update IMU
//#ifdef DEBUG_SERIAL    
//    Serial.println("Update IMU");
//#endif
///    t=millis();
    imu_loop(ypr2);
//    Serial.println("IMU Time");
//    Serial.println(millis()-t);
//#ifdef DEBUG_SERIAL    
//   Serial.println("Update X");
//#endif
//    t=millis();
    update_state(ypr2);
//    Serial.println("State Time");
//    Serial.println(millis()-t);
    //Run PID
//#ifdef DEBUG_SERIAL    
//    Serial.println("Update U");
//#endif
//    t=millis();
    update_input();
//    Serial.println("Input Time");
//    Serial.println(millis()-t);
    //Update control system
//#ifdef DEBUG_SERIAL    
//    Serial.println("Update motors");
//#endif
//    t=millis();
    write_output();
//    Serial.println("Output Time");
//    Serial.println(millis()-t);
    //Update thrust values
    

}

void setup()
{
    start_pilot();
    Serial.begin(57600);
};

uint32_t t_mav_pilot = 0, t_mav_pilot_update = 0;

void loop()
{
    t_mav_pilot = t_mav_pilot_update;
    update_pilot();
    t_mav_pilot_update = millis();
    Serial.print("Loop time: ");
    Serial.println(t_mav_pilot_update - t_mav_pilot);
};
