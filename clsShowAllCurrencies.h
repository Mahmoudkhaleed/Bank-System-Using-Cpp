#pragma once
#include <iomanip>
#include "clsCurrency.h"
#include "clsUtility.h"

class clsShowAllCurrencies
{
	static void _PrintCurrencyInfoInline(clsCurrency& currency)
	{
		cout << "| " << left << setw(30) << currency.Country;
		cout << "| " << left << setw(6) << currency.CurrencyCode;
		cout << "| " << left << setw(40) << currency.CurrencyName;
		cout << "| " << left << setw(10) << currency.Rate << endl;
	}
public:
	static void ShowAllCurrencies()
	{
		vector<clsCurrency> currencies = clsCurrency::GetAllCurrencies();
		cout << "Currency List (" << currencies.size() << ") Currency/s" << endl;
		cout << clsUtility::MakeLineOf(100) << endl << endl;
		cout << "| " << left << setw(4) << "I";
		cout << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(6) << "Code";
		cout << "| " << left << setw(40) << "Currency Name";
		cout << "| " << left << setw(10) << "Rate" << endl;
		cout << clsUtility::MakeLineOf(100) << endl << endl;
		int i = 0;
		for (clsCurrency& currency : currencies)
		{
			cout << "| " << left << setw(4) << i + 1;
			_PrintCurrencyInfoInline(currency);
			i++;
		}
		cout << clsUtility::MakeLineOf(100) << endl;
	}

};

