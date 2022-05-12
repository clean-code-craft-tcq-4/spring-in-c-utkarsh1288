#include <math.h>
#ifdef NAN
/*NAN is supported*/
#endif
struct Stats
{
    float average;
    float min;
    float max;
};

extern int emailAlertCallCount;

extern int ledAlertCallCount;

extern int NAN_Detected;

extern int Empty_numberset_Detected;

extern int Simultaneous_Alerts;

typedef void (*alerter_funcptr)();

void emailAlerter();

void ledAlerter();

extern void check_and_alert(float maxThreshold, alerter_funcptr alerters[], struct Stats computedStats);

extern struct Stats compute_statistics(const float* numberset, int setlength);


