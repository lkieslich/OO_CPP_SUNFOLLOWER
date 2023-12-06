#include "Calendar.h"
#include <iostream>
using namespace std;

Calendar::Calendar(int m, int d, int y)
{
    setCalendar(m, d, y);
}

void Calendar::setCalendar(int m, int d, int y)
{
    mo = m;
    day = d;
    yr = y;
}   
void Calendar::readCalendar(int& m, int& d, int& y)
{
    m = mo;
    d = day;
    y = yr;
}
void Calendar::advance()
{
    int N_DAY = 30;
  
    if(mo == 1 || mo == 3 || mo == 5 || mo == 7 || mo == 8 || mo == 10 || mo == 12) N_DAY = 31;
    else if (mo == 2) N_DAY = 28;
    else N_DAY = 30;

    day++;
    if(day>N_DAY)
    {
        day = 1;
        mo++;
    }
    if(mo>12)
    {
        mo = 1;
        yr++;
    }
}
