#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsFindCurrency
{
public:
	static void FindCurrency()
	{
		cout << "Enter A Country or A Currency Code: ";
		string SearchKey = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(SearchKey))
		{
			cout << "The Currency is not exist, Enter another One: ";
			SearchKey = clsInputValidate::ReadString();
		}

		clsCurrency currency = clsCurrency::Find(SearchKey);
		cout << endl;
		clsScreen::PrintCurrency(currency);
	}
};

