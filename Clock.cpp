#include "Clock.h"
#include <iostream>

using namespace std;

Clock::Clock(int h, int s, int m, int pm)
{
    setClock(h, s, m, pm);
}
void Clock::setClock(int h, int s, int m, int pm)
{
    hr = h;
    min = m;
    sec = s;
    is_pm = pm;
}
void Clock::readClock(int& h, int& s, int& m, int& pm)
{
    h = hr;
    m = min;
    s = sec;
    pm = is_pm;
}
void Clock::advance()
{       
    sec++;
    if(sec > 59)
    {
        sec = 0;
        min++;
    }
    if(min>59)
    {
        min = 0;
        hr > 11 ? hr = 1:hr++;
        if(is_pm && hr > 11) is_pm = 0; 
        else if(!is_pm && hr > 11) is_pm = 1;
    }
}