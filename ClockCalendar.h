#include "Clock.h"
#include "Calendar.h"
#include <string>

class ClockCalendar : public Clock, public Calendar {
    public:
        ClockCalendar(int mo, int d, int y, int h, int m, int s, int pm);
        void advance();
        string displayClockCalendar();
};