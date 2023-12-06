#pragma once

class Calendar
{
    protected:
        int mo, day, yr;
    public:
        Calendar(int m, int d, int y);
        void setCalendar(int m, int d, int y);
        void readCalendar(int& m, int& d, int& y);
        void advance();
};