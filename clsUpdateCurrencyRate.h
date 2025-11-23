#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsUpdateCurrencyRate
{
public:
	static void UpdateCurrencyRate()
	{
		cout << "Enter A Country or A Currency COde: ";
		string SearchKey = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(SearchKey))
		{
			cout << "The Currency is not exist, Enter another One: ";
			SearchKey = clsInputValidate::ReadString();
		}

		clsCurrency currency = clsCurrency::Find(SearchKey);
		cout << endl;
		clsScreen::PrintCurrency(currency);
		
		cout << "Enter The New Rate: ";
		double NewRate = clsInputValidate::ReadNumber<double>("Invalid input, Try again: ");
		string choice;
		cout << "Are you Sure You Want to Update? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			currency.Rate = NewRate;
			currency.Save();
			cout << endl;
			clsScreen::PrintCurrency(currency);
			cout << "the Rate is Updated Successfully!" << endl;
		}
	}
};

