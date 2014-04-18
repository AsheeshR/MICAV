#include "pilot.h"

#ifdef DEBUG_SERIAL
#undef DEBUG_SERIAL /* Saving Time as Serial guzzles up loads of it */


float ypr2[3];
int st;


void start_pilot()
{
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


int flag = 1;

void update_pilot()
{
    //Update IMU
#ifdef DEBUG_SERIAL    
    Serial.println("Update IMU");
#endif
    imu_loop(ypr2);
//    update_channels();
#ifdef DEBUG_SERIAL    
    Serial.println("Update X");
#endif
    update_state(ypr2);
    //Run PID
#ifdef DEBUG_SERIAL    
    Serial.println("Update U");
#endif
    update_input();

    //Update control system
#ifdef DEBUG_SERIAL    
    Serial.println("Update motors");
#endif
    write_output();
    //Update thrust values
    

}

#endif
