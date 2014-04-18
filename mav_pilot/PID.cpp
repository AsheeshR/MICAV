/* This file implements the PID controllers for each state update */

#include "PID.h"

int16_t pid_dyaw(int16_t dyaw)
{
    static int16_t dyaw_old = 0;
    dyaw_old = 
	KP_DYAW * dyaw + 
	dyaw_old + KI_DYAW * dyaw +
	KD_DYAW * (dyaw - dyaw_old)
	;
    dyaw_old = constrain(dyaw_old, PID_MIN_DYAW, PID_MAX_DYAW);
    return dyaw_old;
}

int16_t pid_dpitch(int16_t dpitch)
{
    static int16_t dpitch_old = 0;
    dpitch_old = 
	(KP_DPITCH * dpitch) + 
	dpitch_old + (KI_DPITCH * dpitch) +
	(KD_DPITCH * (dpitch - dpitch_old))
	;
    dpitch_old = constrain(dpitch_old, PID_MIN_DPITCH, PID_MAX_DPITCH);
    return dpitch_old;
}

int16_t pid_droll(int16_t droll)
{
    static int16_t droll_old = 0; /* These should be signed , always! */
    droll_old = 
	(KP_DROLL * droll) + 
	droll_old + (KI_DROLL * droll) +
	(KD_DROLL * (droll - droll_old))
	;
    droll_old = constrain(droll_old, PID_MIN_DROLL, PID_MAX_DROLL);
    return droll_old;
}

int16_t pid_daltitude(int16_t daltitude)
{
    static int16_t daltitude_old = 0;
    daltitude_old = constrain(daltitude_old, -30, 30);
    return 
	(
	daltitude_old = 
	KP_DALTITUDE * daltitude + 
	daltitude_old + KI_DALTITUDE * daltitude +
	KD_DALTITUDE * (daltitude - daltitude_old)
	);
}
