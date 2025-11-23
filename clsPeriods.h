#pragma once
#include "clsDate.h"

class clsPeriods
{
public:

    clsDate Start;
    clsDate End;

    clsPeriods(clsDate StartDate, clsDate EndDate)
    {
        this->Start = StartDate;
        this->End = EndDate;

    }

    static bool IsOverlapPeriods(clsPeriods Period1, clsPeriods Period2)
    {
        return !(clsDate::IsDate1LessThanDate2(Period1.End, Period2.Start) || clsDate::IsDate1LessThanDate2(Period2.End, Period1.Start));
    }

    static bool IsDateWithinPeriod(clsPeriods Period, clsDate date)
    {
        return clsDate::IsDate1LessThanDate2(Period.Start, date) && clsDate::IsDate1LessThanDate2(date, Period.End);
    }

    static int NumberOfOverlapedDays(clsPeriods Period1, clsPeriods Period2)
    {
        if (!IsOverlapPeriods(Period1, Period2))
            return 0;
        if (IsDateWithinPeriod(Period1, Period2.Start))
        {
            if (IsDateWithinPeriod(Period1, Period2.End))
                return clsDate::DiffBetweenTwoDatesInDays(Period2.Start, Period2.End);
            else
                return clsDate::DiffBetweenTwoDatesInDays(Period2.Start, Period1.End);
        }
        else if (IsDateWithinPeriod(Period2, Period1.Start))
        {
            if (IsDateWithinPeriod(Period2, Period1.End))
                return clsDate::DiffBetweenTwoDatesInDays(Period1.Start, Period1.End);
            else
                return clsDate::DiffBetweenTwoDatesInDays(Period1.Start, Period2.End);
        }
        else
            return 1;
    }


    bool IsOverLapWith(clsPeriods Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        Start.Print();

        cout << "Period End: ";
        End.Print();
    }

};
