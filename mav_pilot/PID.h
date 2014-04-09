/* This file defines the PID controllers for each state update */

#define KP_DYAW 0
#define KI_DYAW 0
#define KD_DYAW 0

#define KP_DPITCH 0
#define KI_DPITCH 0
#define KD_DPITCH 0

#define KP_DROLL 0
#define KI_DROLL 0
#define KD_DROLL 0

#define KP_DALTITUDE 0
#define KI_DALTITUDE 0
#define KD_DALTITUDE 0

int16_t pid_dyaw(int16_t dyaw);
int16_t pid_dpitch(int16_t dpitch);
int16_t pid_droll(int16_t droll);
int16_t pid_daltitude(int16_t daltitude);

