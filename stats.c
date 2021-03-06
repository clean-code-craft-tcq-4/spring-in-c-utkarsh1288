#include "stats.h"
#include <math.h>
#ifdef NAN
/*NAN is supported*/
#endif
int emailAlertCallCount = 0;
int ledAlertCallCount = 0;
int NAN_Detected =0;
int Simultaneous_Alerts =0;
int Empty_numberset_Detected =0;

struct Stats compute_statistics(const float* numberset, int setlength) 
{
    struct Stats s;
    s.average = 0;
    s.min = 0;
    s.max = 0;
    int i =0;
    float Total =0;
    float min = 0, max =0;
    if((numberset == NULL)&&(setlength ==0))
    {
		Empty_numberset_Detected  =1;
    }
	else
	{
	    for(i =0;i<setlength;i++)
		{
			Total = Total + numberset[i];
		}
		s.average = Total/setlength;
		min = numberset[0];
		max = numberset[0];
		for(i=0;i<setlength;i++)
		{
			if(numberset[i]< min)
			{
				min = numberset[i];
			}
			if(numberset[i]> max)
			{
				max = numberset[i];
			}
		}
		s.min =min;
		s.max = max;	
	}
    if(isnan(s.average))
    {
	 NAN_Detected =1;   
    }    
    return s;
} 

void check_and_alert(float maxThreshold, alerter_funcptr alerters[], struct Stats computedStats)
{
    if(computedStats.max < maxThreshold)
    {
        (*alerters[0])();
    }
    else if(computedStats.max == maxThreshold)
    {
         (*alerters[1])();  
    }
    else if(computedStats.max > maxThreshold)
    {
        (*alerters[0])(); 
        (*alerters[1])(); 
	Simultaneous_Alerts++;
    }
    else
    {
        /*Do Nothing*/
    }
}

void emailAlerter()
{
   emailAlertCallCount++;
}

void ledAlerter()
{
   ledAlertCallCount++;
}
