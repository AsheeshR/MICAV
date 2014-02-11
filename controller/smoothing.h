//This file will contain prototypes for the smoothing algorithms
#ifndef SMOOTH
#define SMOOTH

#define SMA_LENGTH 43
#define EMA_ALPHA 0.10
#define SG_LENGTH 5
#define RDP_LENGTH 11
#define epsilon 50
#define KZ_LENGTH 5
#define KZ_MAX 4
#define KZ_history_LENGTH KZ_LENGTH*KZ_MAX


extern int history_SMA[SMA_LENGTH];
extern int history_SG[SG_LENGTH];
extern int history_KZ[KZ_history_LENGTH];
extern int history_RDP[RDP_LENGTH];
extern int index_RDP[];



int simple_mov_avg(int current_value);
int cumulative_mov_avg(int current_value);
int exponential_mov_avg(int current_value);
int savitzky_golay(int current_value);
int KZ_filter(int current_value);
int RDP_caller(int current_value);



#endif
