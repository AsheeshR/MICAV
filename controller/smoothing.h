//This file will contain prototypes for the smoothing algorithms
#ifndef SMOOTH
#define SMOOTH

#define SMA_LENGTH 11
#define SG_LENGTH 5
#define RDP_LENGTH 5
#define epsilon 30
#define KZ_LENGTH 5
#define KZ_MAX 3
#define KZ_history_LENGTH KZ_LENGTH*KZ_MAX


extern int history_SMA[SMA_LENGTH];

int simple_mov_avg(int current_value);
int cumulative_mov_avg(int current_value);
int exponential_mov_avg(int current_value);


#endif
