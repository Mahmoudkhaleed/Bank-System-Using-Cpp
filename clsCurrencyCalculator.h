#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculator
{
	static string _Calc(clsCurrency &Curr1, clsCurrency &Curr2, double amount)
	{
		double Exchange = amount * (Curr2.Rate / Curr1.Rate);
		return to_string(amount) + " " + Curr1.CurrencyCode + " = " + to_string(Exchange) + " " + Curr2.CurrencyCode;
	}
public:
	static void CurrecyCalculator()
	{
		cout << "Enter A Country or A Currency Code to Exchange From: ";
		string SearchKey = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(SearchKey))
		{
			cout << "The Currency is not exist, Enter another One: ";
			SearchKey = clsInputValidate::ReadString();
		}
		clsCurrency currency1 = clsCurrency::Find(SearchKey);
		cout << endl;

		cout << "Enter A Country or A Currency Code to Exchange to: ";
		SearchKey = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(SearchKey))
		{
			cout << "The Currency is not exist, Enter another One: ";
			SearchKey = clsInputValidate::ReadString();
		}
		clsCurrency currency2 = clsCurrency::Find(SearchKey);
		cout << endl;
		cout << "Enter The Amount: ";
		double Amount = clsInputValidate::ReadNumber<double>("Invalid, Enter Another Number: ");
		cout << endl;
		cout << _Calc(currency1, currency2, Amount) << endl;
	}
};

