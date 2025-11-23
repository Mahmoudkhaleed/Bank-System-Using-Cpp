#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	int _Days;
	int _Months;
	int _Years;
	static string getDayNameByIndex(int dayIndex)
	{
		string arr[]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sut" };
		return arr[dayIndex];
	}
public:
	clsDate()
	{
		*this = GetSystemDate();
	}
	clsDate(int days, int month, int year)
	{
		_Days = days;
		_Months = month;
		_Years = year;
	}
	clsDate(string ddmmyy)
	{
		vector<string> arr = clsString::Split(ddmmyy, "/");
		_Days = stoi(arr[0]);
		_Months = stoi(arr[1]);
		_Years = stoi(arr[2]);
	}
	clsDate(int indexOfDayInDate, int year)
	{
		*this = DateFromIndex(indexOfDayInDate, year);
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm localDate = *localtime(&t);
		return clsDate(localDate.tm_mday, localDate.tm_mon + 1, localDate.tm_year + 1900);
	}
	
	static string GetSystemTime()
	{
		time_t t = time(0);
		tm localDate = *localtime(&t);
		return to_string(localDate.tm_hour) + ":" + to_string(localDate.tm_min) + ":" + to_string(localDate.tm_sec);
	}


	void SetDay(int day)
	{
		_Days = day;
	}
	int GetDay()
	{
		return _Days;
	}
	__declspec(property(get = GetDay, put = SetDay)) int Day;

	void SetMonth(int month)
	{
		_Months = month;
	}
	int GetMonth()
	{
		return _Months;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) int Month;

	void SetYear(int year)
	{
		_Years = year;
	}
	int GetYear()
	{
		return _Years;
	}
	__declspec(property(get = GetYear, put = SetYear)) int Year;

	static void Print(short day, short month, short year)
	{
		cout << DateToString(day, month, year) << endl;
	}
	static void Print(clsDate date)
	{
		Print(date._Days, date._Months, date._Years);
	}
	void Print()
	{
		Print(*this);
	}

	void PrintInTextFormat()
	{
		cout << DateToTextFormat(*this) << endl;
	}

	static string DateToTextFormat(clsDate date)
	{
		return date.GetDayNameInDate() + ", " + date.GetMonthName() + " " + to_string(date.GetDay());
	}

	static string DateToString(int d, int m, int y)
	{
		return to_string(d) + "/" + to_string(m) + "/" + to_string(y);
	}
	
	static string DateToString(clsDate date)
	{
		return DateToString(date.Day, date.Month, date.Year);
	}

	static bool IsLeapYear(int year)
	{
		return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Years);
	}

	static int GetDaysOfMonth(int month, int year)
	{
		bool leap = IsLeapYear(year);
		return month == 2 ? (leap ? 29 : 28) : to_string(135781012).find(to_string(month)) != string::npos ? 31 : 30;
	}
	int GetDaysOfMonth()
	{
		return GetDaysOfMonth(_Months, _Years);
	}

	static int GetIndexOfDayInWeekInDate(int year, int month, int day)
	{
		return (day + year - ((14 - month) / 12) + (year - ((14 - month) / 12)) / 4 - (year - ((14 - month) / 12)) / 100 + (year - ((14 - month) / 12)) / 400 + (31 * (month + 12 * ((14 - month) / 12) - 2)) / 12) % 7;
	}
	static int GetIndexOfDayInWeekInDate(clsDate date)
	{
		return GetIndexOfDayInWeekInDate(date._Years, date._Months, date._Days);
	}
	int GetIndexOfDayInWeekInDate()
	{
		return GetIndexOfDayInWeekInDate(_Years, _Months, _Days);
	}

	static string GetDayNameInDate(int year, int month, int day, bool isAbbr)
	{
		string _DaysNames[7]{ "Sunday", "Monday", "Tueday", "Wednesday", "Thursday", "Friday", "Suterday" };
		string _DaysNamesAbbr[7]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sut" };
		return !isAbbr ? _DaysNames[GetIndexOfDayInWeekInDate(year, month, day)] : _DaysNamesAbbr[GetIndexOfDayInWeekInDate(year, month, day)];
	}
	string GetDayNameInDate(bool isAbbr = false)
	{
		return GetDayNameInDate(_Years, _Months, _Days, isAbbr);
	}

	static string GetMonthName(int month, bool isAbbr)
	{
		string arr[]{ "January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "Novamber", "December" };
		string arrAbbr[]{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return !isAbbr ? arr[month - 1] : arrAbbr[month - 1];
	}
	string GetMonthName(bool isAbbr = false)
	{
		return GetMonthName(_Months, isAbbr);
	}

	static void PrintMonthCalender(int yr, int mo)
	{
		int daysOfMonth = GetDaysOfMonth(mo, IsLeapYear(yr));
		int indexOfDayToStartFrom = GetIndexOfDayInWeekInDate(yr, mo, 1);

		cout << "___________________( " << GetMonthName(mo, true) << " )___________________\n" << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << setw(6) << getDayNameByIndex(i);
		}
		cout << endl;
		for (int i = 0; i < daysOfMonth + indexOfDayToStartFrom; i++)
		{
			if (i >= indexOfDayToStartFrom)
			{
				if (i % 7 == 0 && i != 0)
					cout << endl;
				cout << setw(6) << i + 1 - indexOfDayToStartFrom;
			}
			else
			{
				cout << setw(6) << "";
			}
		}
		cout << "\n_____________________________________________" << endl;
	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(_Years, _Months);
	}

	static void PrintYearCalender(int yr)
	{
		cout << "\n=============================================\n" << endl;
		cout << "               Calender " << yr << "               " << endl;
		cout << "\n=============================================\n" << endl;
		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalender(yr, i);
			cout << endl;
		}
	}
	void PrintYearCalender()
	{
		PrintYearCalender(_Years);
	}

	static int GetOrderOfDayInDate(int y, int m, int d)
	{
		int days = 0;
		bool leap = IsLeapYear(y);
		for (int i = 1; i < m; i++)
		{
			days += GetDaysOfMonth(m, y);
		}
		days += d;
		return days;
	}
	static int GetOrderOfDayInDate(clsDate date)
	{
		return GetOrderOfDayInDate(date._Years, date._Months, date._Days);
	}
	int GetOrderOfDayInDate()
	{
		return GetOrderOfDayInDate(_Years, _Months, _Days);
	}

	static clsDate DateFromIndex(int index, int y)
	{
		clsDate date;
		int i = 1;
		while (index > 31)
		{
			int m = GetDaysOfMonth(i, y);
			index -= m;
			i++;
			if (i > 12)
			{
				i = 1;
				y++;
			}
		}
		int d = index;
		date._Days = d;
		date._Months = i;
		date._Years = y;

		return date;
	}

	static void PrintDateFromIndex(int index, int y)
	{
		clsDate date = DateFromIndex(index, y);
		date.Print();
	}

	// Manupulate date by increasing and decreasing amount of days
	// ================ 1. Increase ==================== 
	static void AddOneDay(int& y, int& m, int& d)
	{
		int dateIndex = GetOrderOfDayInDate(y, m, d);
		int totalDays = 1 + dateIndex;
		int numOfYears = 0;
		while (totalDays > 366)
		{
			if (IsLeapYear(y + numOfYears))
			{
				totalDays -= 366;
			}
			else
				totalDays -= 365;
			numOfYears++;
		}
		clsDate date = DateFromIndex(totalDays, numOfYears + y);
		d = date._Days;
		m = date._Months;
		y = date._Years;
	}
	static void AddOneDay(clsDate& date)
	{
		AddOneDay(date._Years, date._Months, date._Days);
	}
	void AddOneDay()
	{
		AddOneDay(*this);
	}

	static void AddXDay(clsDate& date, int daysToAdd)
	{
		for (int i = 0; i < daysToAdd; i++)
		{
			AddOneDay(date);
		}
	}
	void AddXDay(int daysToAdd)
	{
		AddXDay(*this, daysToAdd);
	}

	static void AddOneWeek(clsDate& date)
	{
		AddXDay(date, 7);
	}
	void AddOneWeek()
	{
		AddOneWeek(*this);
	}

	static void AddXWeek(clsDate& date, int xWeeks)
	{
		AddXDay(date, 7 * xWeeks);
	}
	void AddXWeek(int xWeeks)
	{
		AddXWeek(*this, xWeeks);
	}

	static void AddOneMonth(clsDate& date)
	{
		int m = GetDaysOfMonth(date._Months, IsLeapYear(date._Years));
		AddXDay(date, m);
	}
	void AddOneMonth()
	{
		AddOneMonth(*this);
	}

	static void AddXMonth(clsDate& date, int xMonths)
	{
		int moIndex = date._Months;
		int m = 0;
		for (int i = 0; i < xMonths; i++)
		{
			m += GetDaysOfMonth(moIndex, IsLeapYear(date._Years));
			if (moIndex > 12)
			{
				moIndex = 1;
			}
			moIndex++;
		}
		AddXDay(date, m);
	}
	void AddXMonth(int xMonths)
	{
		AddXMonth(*this, xMonths);
	}

	static void AddOneYear(clsDate& date)
	{
		date._Years += 1;
	}
	void AddOneYear()
	{
		AddOneYear(*this);
	}

	static void AddXYear(clsDate& date, int xYears)
	{
		date._Years += xYears;
	}
	void AddXYear(int xYears)
	{
		AddXYear(*this, xYears);
	}

	static void AddOneDecade(clsDate& date)
	{
		date._Years += 10;
	}
	void AddOneDecade()
	{
		AddOneDecade(*this);
	}

	static void AddXDecade(clsDate& date, int xDecades)
	{
		date._Years += 10 * xDecades;
	}
	void AddXDecade(int xDecades)
	{
		AddXDecade(*this, xDecades);
	}

	static void AddOneCentury(clsDate& date)
	{
		date._Years += 100;
	}
	void AddOneCentury()
	{
		AddOneCentury(*this);
	}

	static void AddOneMillennium(clsDate& date)
	{
		date._Years += 1000;
	}
	void AddOneMillennium()
	{
		AddOneMillennium(*this);
	}

	// ================== 2. decrease ====================
	static void RemoveOneDay(clsDate& d)
	{
		if (IsItTheFirstDayOfTheMonth(d))
		{
			if (IsItTheFirstMonthOfTheYear(d))
			{
				d._Years--;
				d._Months = 12;
				d._Days = 31;
			}
			else
			{
				d._Months--;
				d._Days = GetDaysOfMonth(d._Months, IsLeapYear(d._Years));
			}
		}
		else
		{
			d._Days--;
		}
	}
	void RemoveOneDay()
	{
		RemoveOneDay(*this);
	}

	static void RemoveXDay(clsDate& date, int daysToRemove)
	{
		for (int i = 0; i < daysToRemove; i++)
		{
			RemoveOneDay(date);
		}
	}
	void RemoveXDay(int daysToRemove)
	{
		RemoveXDay(*this, daysToRemove);
	}

	static void RemoveOneWeek(clsDate& date)
	{
		RemoveXDay(date, 7);
	}
	void RemoveOneWeek()
	{
		RemoveOneWeek(*this);
	}

	static void RemoveXWeek(clsDate& date, int xWeeks)
	{
		RemoveXDay(date, 7 * xWeeks);
	}
	void RemoveXWeek(int xWeeks)
	{
		RemoveXWeek(*this, xWeeks);
	}

	static void RemoveOneMonth(clsDate& date)
	{
		int m = GetDaysOfMonth(date._Months - 1, IsLeapYear(date._Years));
		RemoveXDay(date, m);
	}
	void RemoveOneMonth()
	{
		RemoveOneMonth(*this);
	}

	static void RemoveXMonth(clsDate& date, int xMonths)
	{
		int moIndex = date._Months + 1;
		int m = 0;
		for (int i = 0; i < xMonths; i++)
		{
			m += GetDaysOfMonth(moIndex, IsLeapYear(date._Years));
			if (moIndex < 1)
			{
				moIndex = 12;
			}
			moIndex--;
		}
		RemoveXDay(date, m);
	}
	void RemoveXMonth(int xMonths)
	{
		RemoveXMonth(*this, xMonths);
	}

	static void RemoveOneYear(clsDate& date)
	{
		date._Years -= 1;
	}
	void RemoveOneYear()
	{
		RemoveOneYear(*this);
	}

	static void RemoveXYear(clsDate& date, int xYears)
	{
		date._Years -= xYears;
	}
	void RemoveXYear(int xYears)
	{
		RemoveXYear(*this, xYears);
	}

	static void RemoveOneDecade(clsDate& date)
	{
		date._Years -= 10;
	}
	void RemoveOneDecade()
	{
		RemoveOneDecade(*this);
	}

	static void RemoveXDecade(clsDate& date, int xDecades)
	{
		date._Years -= 10 * xDecades;
	}
	void RemoveXDecade(int xDecades)
	{
		RemoveXDecade(*this, xDecades);
	}

	static void RemoveOneCentury(clsDate& date)
	{
		date._Years -= 100;
	}
	void RemoveOneCentury()
	{
		RemoveOneCentury(*this);
	}

	static void RemoveOneMillennium(clsDate& date)
	{
		date._Years -= 1000;
	}
	void RemoveOneMillennium()
	{
		RemoveOneMillennium(*this);
	}

	// states
	static bool IsDate1LessThanDate2(clsDate d1, clsDate d2)
	{
		return d1._Years < d2._Years ? 1 : (d1._Months < d2._Months ? 1 : d1._Days < d2._Days ? 1
			: 0);
	}
	bool IsItLessThanDate2(clsDate d2)
	{
		return IsDate1LessThanDate2(*this, d2);
	}

	static bool IsDate1EqualToDate2(clsDate d1, clsDate d2)
	{
		return (d1._Years == d2._Years && d1._Months == d2._Months && d1._Days == d2._Days);
	}
	bool IsItEqualToDate2(clsDate d2)
	{
		return IsDate1EqualToDate2(*this, d2);
	}

	static bool IsDate1AfterDate2(clsDate d1, clsDate d2)
	{
		return !IsDate1LessThanDate2(d1, d2) && !IsDate1EqualToDate2(d1, d2);
	}
	bool IsItAfterDate2(clsDate d2)
	{
		return IsDate1AfterDate2(*this, d2);
	}

	static bool IsValid(clsDate date)
	{
		return date._Years > 0 && date._Months <= 12 && date._Months > 0 && date._Days <= GetDaysOfMonth(date._Months, date._Years) && date._Days > 0;
	}
	bool IsValid()
	{
		return IsValid(*this);
	}

	static bool IsItTheLastDayOfTheMonth(int y, int month, int day)
	{
		return GetDaysOfMonth(month, IsLeapYear(y)) == day;
	}
	static bool IsItTheLastDayOfTheMonth(clsDate date)
	{
		return GetDaysOfMonth(date._Months, IsLeapYear(date._Years)) == date._Days;
	}
	bool IsItTheLastDayOfTheMonth()
	{
		return IsItTheLastDayOfTheMonth(*this);
	}

	static bool IsItTheLastMonthOfTheYear(int month)
	{
		return month == 12;
	}
	static bool IsItTheLastMonthOfTheYear(clsDate date)
	{
		return date._Months == 12;
	}
	bool IsItTheLastMonthOfTheYear()
	{
		return IsItTheLastMonthOfTheYear(*this);
	}

	static bool IsItTheFirstDayOfTheMonth(clsDate d)
	{
		return d._Days == 1;
	}
	bool IsItTheFirstDayOfTheMonth()
	{
		IsItTheFirstDayOfTheMonth(*this);
	}
	static bool IsItTheFirstMonthOfTheYear(clsDate d)
	{
		return d._Months == 1;
	}
	bool IsItTheFirstMonthOfTheYear()
	{
		IsItTheFirstMonthOfTheYear(*this);
	}

	static bool IsEndOfWeek(clsDate date)
	{
		return GetIndexOfDayInWeekInDate(date) == 6;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(clsDate date)
	{
		return GetIndexOfDayInWeekInDate(date) == 5 || GetIndexOfDayInWeekInDate(date) == 6;
	}
	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		return !IsWeekend(date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysTillEndOfWeek(clsDate date)
	{
		return 6 - GetIndexOfDayInWeekInDate(date);
	}
	short DaysTillEndOfWeek()
	{
		return DaysTillEndOfWeek(*this);
	}

	static short DaysTillEndOfMonth(clsDate date)
	{
		return GetDaysOfMonth(date._Months, date._Years) - date._Days;
	}
	short DaysTillEndOfMonth()
	{
		return DaysTillEndOfMonth(*this);
	}

	static short DaysTillEndOfYear(clsDate date)
	{
		int yearDays = IsLeapYear(date._Years) ? 366 : 365;
		return yearDays - GetOrderOfDayInDate(date);
	}
	short DaysTillEndOfYear()
	{
		return DaysTillEndOfYear(*this);
	}

	// Numbers
	static int DiffBetweenTwoDatesInDays(clsDate d1, clsDate d2, bool lastDayIncluded = false)
	{
		int flagVe = 1;
		if (!IsDate1LessThanDate2(d1, d2))
		{
			SwapDates(d1, d2);
			flagVe = -1;
		}
		int d1DaysTillDate = GetOrderOfDayInDate(d1);
		int d2DaysToEndYear = (IsLeapYear(d2._Years) ? 366 : 365) - GetOrderOfDayInDate(d2);
		int daysOfYears = 0;
		for (int i = d1._Years; i <= d2._Years; i++)
		{
			daysOfYears += (IsLeapYear(i) ? 366 : 365);
		}

		return (daysOfYears - (d1DaysTillDate + d2DaysToEndYear) + lastDayIncluded) * flagVe;
	}
	int DiffBetweenItAndDate2InDays(clsDate d2, bool lastDayIncluded = false)
	{
		return DiffBetweenTwoDatesInDays(*this, d2, lastDayIncluded);
	}

	static int TotalVacationDaysFromDate1ToDate2(clsDate d1, clsDate d2)
	{
		int daysCount = 0;
		for (int i = 0; i < DiffBetweenTwoDatesInDays(d1, d2, true); i++)
		{
			AddOneDay(d1);
			if (IsBusinessDay(d1))
			{
				daysCount++;
			}
		}
		return daysCount;
	}
	int TotalVacationDaysToDate2(clsDate d2)
	{
		return TotalVacationDaysFromDate1ToDate2(*this, d2);
	}

	static int NumberOfDaysInYear(clsDate date)
	{
		return IsLeapYear(date._Years) ? 366 : 365;
	}
	int NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(*this);
	}

	static clsDate EndOfVacation(clsDate date, int vacationDays)
	{
		while (vacationDays >= 0)
		{
			AddOneDay(date);
			if (IsBusinessDay(date))
				vacationDays--;
		}
		return date;
	}
	clsDate EndOfVacation(int vacationDays)
	{
		return EndOfVacation(*this, vacationDays);
	}

	static void SwapDates(clsDate& d1, clsDate& d2)
	{
		clsDate temp;
		temp = d1;
		d1 = d2;
		d2 = temp;
	}
};