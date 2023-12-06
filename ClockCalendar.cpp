#include <iostream>
#include "ClockCalendar.h"
using namespace std;
ClockCalendar::ClockCalendar(int mo, int d, int y, int h, int m, int s, int pm): Clock(h, m, s, pm), Calendar(m, d, y)
{
    setClock(h, s, m, pm);
    setCalendar(mo, d, y);
}

void ClockCalendar::advance()
{
    bool wasPm = is_pm; 
    Clock::advance();
    if (wasPm && !is_pm)
    Calendar::advance();
}