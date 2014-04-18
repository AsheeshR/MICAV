/* This file implements the linear time invariant control system */

/* ********************************************************************* */
/* Check whether IMU axis are in the same direction as Motor Update Axis */

#include "controller.h"

#define MIRROR_PI(theeta) ((theeta>=0)?(180-theeta):(-180-(theeta)));

//static int16_t X_dot[12] = {0, };
static int16_t X[12] = {0, };
static int16_t Y[12] = {0, };

/* A and B are too big to be allocated statically */
/* Most likely solution is predefined macros */

static int16_t U[4] = {0, };
/* Output Matrix for Control System
 * 0 : Thrust
 * 1 : Yaw
 * 2 : Pitch
 * 3 : Roll
 */

/*static int8_t C[4][12] = { 
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
    };*/

static uint16_t channels[7];
static int16_t thrust[4]/*, heading[3]*/; /* WARNING: IMU RETURNS FLOATS! */

void update_input()
{
    update_channels(channels);
    
    /* Calculate Errors */
    U[0] = /*X[5] -*/ map(channels[0], CHANNEL1_MIN, CHANNEL1_MAX, -100, 100);
    
    U[0] = (U[0]<20 && U[0]>-20) ? 0 : U[0];

    
    U[1] = X[9] - map(channels[1], CHANNEL2_MIN, CHANNEL2_MAX, MIN_DYAW, MAX_DYAW); 
    U[2] = X[10] - map(channels[2], CHANNEL3_MIN, CHANNEL3_MAX, MIN_DPITCH, MAX_DPITCH);
    U[3] = X[11] - map(channels[3], CHANNEL4_MIN, CHANNEL4_MAX, MIN_DROLL, MAX_DROLL);

    /* Yaw Scaling */
    /* U[0]/=4;    U[1]/=4;    U[2]/=4;*/

#ifdef DEBUG_SERIAL
    Serial.print("Map Values : ");
    Serial.print(map(channels[1], CHANNEL2_MIN, CHANNEL2_MAX, MIN_DYAW, MAX_DYAW));     Serial.print(" ");
    Serial.print(map(channels[2], CHANNEL3_MIN, CHANNEL3_MAX, MIN_DPITCH, MAX_DPITCH));     Serial.print(" ");
    Serial.print(map(channels[3], CHANNEL4_MIN, CHANNEL4_MAX, MIN_DROLL, MAX_DROLL));     Serial.print(" ");
//    Serial.print(U[3]);     Serial.print(" ");
    Serial.println();
#endif
    

#ifdef DEBUG_SERIAL
    Serial.print("U Values : Pre PID ");
//    Serial.print(U[0]);     Serial.print(" ");
//    Serial.print(U[1]);     Serial.print(" ");
    Serial.print(U[2]);     Serial.print(" ");
//    Serial.print(U[3]);     Serial.print(" ");
    Serial.println();
#endif

    U[1]/=4; /* Dividing by 4 to constrain it to -25 +25 range */
    U[2]/=4;
    U[3]/=4;

#ifdef DEBUG_SERIAL
    Serial.print("U Values : After Division ");
//    Serial.print(U[0]);     Serial.print(" ");
//    Serial.print(U[1]);     Serial.print(" ");
    Serial.print(U[2]);     Serial.print(" ");
//    Serial.print(U[3]);     Serial.print(" ");
    Serial.println();
#endif


    /* Apply PID to errors */
    /* This transform E(t) -> U(t) */
    /* U[0] = pid_daltitude(U[0]); No feedback yet*/
    U[1] = pid_dyaw(U[1]); 
    U[2] = pid_dpitch(U[2]);
    U[3] = pid_droll(U[3]);

/*    U[1] = constrain(U[1], -30, 30);
    U[2] = constrain(U[2], -30, 30);
    U[3] = constrain(U[3], -30, 30);
*/    
#ifdef DEBUG_SERIAL
    Serial.print("U Values : ");
//    Serial.print(U[0]);     Serial.print(" ");
//    Serial.print(U[1]);     Serial.print(" ");
    Serial.print(U[2]);     Serial.print(" ");
//    Serial.print(U[3]);     Serial.print(" ");
    Serial.println();
#endif
}

void update_state(float heading[])
{
    int16_t local_heading[3]; /* Sometimes, the loop time is less than the IMU update time, in which case the heading array is not updated.
			       * If the heading array is not updated, then it gets multiplied by 10 twice, as it retains the previously
			       * modified values. To handle this case, a local copy of the heading array is used 
			       */

    /* X */
    //update_IMU();
    //imu_loop(ypr2);
    //X[0] = ; //x
    //X[1] = ; //y
    //X[2] = ; //z

    //X[3] = X[3] + X[0]; //dx
    //X[4] = X[4] + X[1]; //dy
    //X[5] = X[5] + X[2]; //dz
    
    /* Since our domain is int, and heading carries decimal digits after
       decimal point, upgrading it to int with 1 digit loss of information*/
    local_heading[0] = heading[0] * 10; 
    local_heading[1] = heading[1] * 10; 
    local_heading[2] = MIRROR_PI(heading[2]);  /* Since our IMU is inverted */ 
    local_heading[2] *= 10;

    
    X[9] = local_heading[0] - X[6]; //dYAW
    X[10] = local_heading[1] - X[7]; //dPITCH
    X[11] = local_heading[2] - X[8]; //dROLL

    /* These will be 4 digits long from -3600 to +3600 */
    X[6] = local_heading[0]; //YAW
    X[7] = local_heading[1]; //PITCH
    X[8] = local_heading[2]; //ROLL



#ifdef DEBUG_SERIAL
    Serial.print("YPR Values : ");
    Serial.print(X[6]);   Serial.print(" ");
    Serial.print(X[7]);   Serial.print(" ");
    Serial.print(X[8]);   Serial.print(" ");
    Serial.println();
#endif


#ifdef DEBUG_SERIAL
    Serial.print("dYdPdR Values : ");
//    Serial.print(X[9]);  Serial.print(" ");
    Serial.print(X[10]);  Serial.print(" ");
//    Serial.print(X[11]);  Serial.print(" ");
    Serial.println();
#endif

}

void update_control()
{
    /* X_dot = AX + Bu */
    
    

    
    

}


void update_output()
{
    int i;
    /* Y = CX */
    /* Y 12x1 
       C 12x12 = Identity
       X 12x1
    */
    for(i=0; i<12; i++)
	Y[i] = X[i];
    
}

/* This matrix reflects the motor update policy */

/* Possible Values for each position are
 * 1 : Compensating Motor
 * 0 : Independent Motor
 *-1 : Reverse Compensating Motor
 */

/* Constraints:
 * Col 1 : All have to be similar
 * Col 2 : Motors on one axis have to be similar
 * Col 3&4 : Policy has to be similar for reasonable response
 */

int8_t D[][4] = 
{
    1,  1, -1,  1,
    1, -1, -1, -1,
    1,  1,  1, -1,
    1, -1,  1,  1
};

void write_output()
{
    /* Reflect controls on driver */
    /* Map U to T
     * T_dot = D * U 
     * T = T_old + T_dot
     */

    thrust[0] = thrust[0] + D[0][0] * U[0] + /*D[0][1] * U[1]*/ + D[0][2] * U[2] + D[0][3] * U[3];
    thrust[1] = thrust[1] + D[1][0] * U[0] + /*D[1][1] * U[1]*/ + D[1][2] * U[2] + D[1][3] * U[3];
    thrust[2] = thrust[2] + D[2][0] * U[0] + /*D[2][1] * U[1]*/ + D[2][2] * U[2] + D[2][3] * U[3];
    thrust[3] = thrust[3] + D[3][0] * U[0] + /*D[3][1] * U[1]*/ + D[3][2] * U[2] + D[3][3] * U[3];

    update_motors(/*Servo * esc[],*/thrust);


#ifdef DEBUG_SERIAL
    Serial.print("Motors Values : ");
    Serial.print(thrust[0]);  Serial.print(" ");
    Serial.print(thrust[1]);  Serial.print(" ");
    Serial.print(thrust[2]);  Serial.print(" ");
    Serial.print(thrust[3]);  Serial.print(" ");
    Serial.println();
#endif

}
