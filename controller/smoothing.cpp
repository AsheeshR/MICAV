//This file will contain implementations of the smoothing algorithms
#ifndef SMOOTH2
#define SMOOTH2

#include "smoothing.h"
#include <math.h>

extern int history_SMA[SMA_LENGTH] = {0,};

int simple_mov_avg(int current_value)
{  
  int average=0,sum=0;
  for(int i=1;i<SMA_LENGTH;i++)
  { 
    history_SMA[i-1]=history_SMA[i];
  }
  
  history_SMA[SMA_LENGTH-1]=current_value;
  for(int j=0;j<SMA_LENGTH;j++)
  {
    sum+=history_SMA[j];
  }
  
  average=sum/SMA_LENGTH;
  
  return average;
}

int cumulative_mov_avg(int current_value)  //Seems useless
{ 
  static unsigned long cumulative_average=0;
  static unsigned long k=0;
  k++;
  
  cumulative_average=(current_value+k*cumulative_average)/(k+1);
  return cumulative_average;
}

int exponential_mov_avg(int current_value)
{ 
  static int exponential_average=current_value;
  
  exponential_average=EMA_ALPHA*current_value + (1-EMA_ALPHA)*exponential_average;
  return exponential_average; 
  
}

int history_SG[SG_LENGTH] = {0,};
const long coefficients[]={-3,12,17,12,-3};
const int normalization_value=35;

int savitzky_golay(int current_value)
{ 
  long sum=0;
  int SG_MID = SG_LENGTH/2;
  for(int i=1;i<SG_LENGTH;i++)
  {
         history_SG[i-1]=history_SG[i];
  }
  history_SG[SG_LENGTH-1]=current_value;
    
  for(int i=-SG_MID;i<=(SG_MID);i++)
  {  
    sum+=history_SG[i+SG_MID]*coefficients[i+SG_MID];
  }
  
  history_SG[SG_MID]=sum/normalization_value;
  
  return history_SG[SG_MID];
  
}
    
int history_RDP[RDP_LENGTH] = {0,}; 
//int index_RDP[]={0,};

  
void RDP(int start_index, int end_index)
{
  int a = history_RDP[end_index]-history_RDP[start_index];
  int b = -(end_index-start_index);
  int c = -start_index*a - history_RDP[start_index]*b;
  
  float max_distance = 0;
  int max_index=0;
  float distance = 0;
  
  for( int i=start_index+1;i<end_index;i++)
  {
    distance=(i*a-history_RDP[i]*b+c)/sqrt(a^2+b^2);
    if (distance>max_distance)
    { 
      max_distance=distance;
      max_index=i;
    }
  }
  
  if(max_distance>epsilon)
  { 
        RDP(start_index,max_index);
        RDP(max_index,end_index);
   } 
   else 
    
   {
    for( int i=start_index+1;i<end_index;i++) 
    {
      history_RDP[i]=(-c-a*i)/b;
    }
   }
}
   
  int RDP_caller(int current_value)
{ 
  int update_value=history_RDP[0];
  for(int i=1;i<RDP_LENGTH;i++)
  { 
    history_RDP[i-1]=history_RDP[i];  
  }
  
  history_RDP[RDP_LENGTH-1]=current_value;
  
  RDP(0,RDP_LENGTH-1);
  return update_value;
}

int history_KZ[KZ_history_LENGTH] = {0,};
int KZ_MID=KZ_history_LENGTH/2;
const long coefficients_k2[]={1,2,3,4,5,4,3,2,1};
const long coefficients_k3[]={1,3,6,10,15,18,19,18,15,10,6,3,1};
const long coefficients_k4[]={1,4,10,20,35,52,68,80,85,80,68,52,35,20,10,4,1};

int KZ_filter(int current_value)

{ 
  long updated_value=0; 
  for(int i=1;i<KZ_history_LENGTH;i++)
  {
         history_KZ[i-1]=history_KZ[i];
  }
    history_KZ[KZ_history_LENGTH-1]=current_value;
    
    for(int i=-KZ_LENGTH/2;i<=KZ_LENGTH/2;i++)
   {
     updated_value+=history_KZ[i+KZ_MID];
   } 
   updated_value/=KZ_LENGTH;
   history_KZ[KZ_MID]=updated_value;
   
   updated_value=0;

   for(int i=-KZ_LENGTH+1;i<KZ_LENGTH;i++)
   {
     updated_value+=history_KZ[i+KZ_MID]*coefficients_k2[i+4];
   } 
   updated_value/=KZ_LENGTH*KZ_LENGTH;
   history_KZ[KZ_MID]=updated_value;
   
   updated_value=0;

   for(int i=-(3*KZ_LENGTH-1)/2;i<=3*(KZ_LENGTH)/2;i++)
   {
     updated_value+=history_KZ[i+KZ_MID]*coefficients_k3[i+6];
   } 
   updated_value/=KZ_LENGTH*KZ_LENGTH*KZ_LENGTH;
   history_KZ[KZ_MID]=updated_value;
   
   updated_value=0;
   
   
   for(int i=-(4*KZ_LENGTH-1)/2;i<=4*(KZ_LENGTH)/2;i++)
   {
     updated_value+=history_KZ[i+KZ_MID]*coefficients_k4[i+8];
   } 
   updated_value/=KZ_LENGTH*KZ_LENGTH*KZ_LENGTH*KZ_LENGTH;
   return history_KZ[KZ_MID]=updated_value;

    
}

#endif
