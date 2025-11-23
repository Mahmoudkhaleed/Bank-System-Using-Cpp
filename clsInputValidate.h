#pragma once
#include <iostream>
#include "clsPeriods.h"
#include "clsDate.h"
using namespace std;

class clsInputValidate
{
public:
	template <typename T> static bool IsNumberBetween(T number, T from, T to)
	{
		return  number >= from && number <= to;
	}

	static bool IsDateBetween(clsDate date, clsDate from, clsDate to)
	{
		clsPeriods period(from, to);
		if (!clsDate::IsDate1LessThanDate2(from, to))
			period = clsPeriods(to, from);
		return clsPeriods::IsDateWithinPeriod(period, date);
	}

	static string ReadString()
	{
		string str;
		getline(cin >> ws, str);
		return str;
	}

	template <typename T> static T ReadNumber(string ErrorMessage)
	{
		T number;
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}
		return number;
	}

	template <typename T> static T ReadNumberInRange(string ErrorMessage, T from, T to)
	{
		T number = ReadNumber<T>("Invalid Number, Enter Again : ");
		while (!IsNumberBetween<T>(number, from, to))
		{
			cout << ErrorMessage;
			cin >> number;
		}
		return number;
	}
};

