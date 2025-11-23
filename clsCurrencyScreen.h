#pragma once
#include "clsScreen.h"
#include "clsUtility.h"
#include "clsInputValidate.h"
#include "clsShowAllCurrencies.h"
#include "clsFindCurrency.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCurrencyCalculator.h"


class clsCurrencyScreen : protected clsScreen
{
	enum enMenuTwoChoices { CurrencyList = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalc = 4, MainMenu = 5 };

	static void _ReturnBackToCurrExchangeScreen()
	{
		cout << "\nPress any key to return back to the Currency Exchange menu...." << endl;
		system("pause>0");
	}


	static void _PrintChoices()
	{
		TitleFrame("Currency Menu Screen", '=');

		cout << "\t[1] Currencies List." << endl;
		cout << "\t[2] Find Currency." << endl;
		cout << "\t[3] Update Rate." << endl;
		cout << "\t[4] Currency Calculator." << endl;
		cout << "\t[5] Main Menu." << endl;
		cout << clsUtility::MakeLineOf(40, '=') << endl;
	}

	static void _ShowCurrencies()
	{
		TitleFrame("Currencies List", '-');
		clsShowAllCurrencies::ShowAllCurrencies();
	}
	static void _FindCurrency()
	{
		TitleFrame("Find Currency", '-');
		clsFindCurrency::FindCurrency();
	}
	static void _UpdateRate()
	{
		TitleFrame("Update Rate", '-');
		clsUpdateCurrencyRate::UpdateCurrencyRate();
	}
	static void _CurrencyCalc()
	{
		TitleFrame("Currency Calculator", '-');
		clsCurrencyCalculator::CurrecyCalculator();
	}

	static void _ConfirmChoice(enMenuTwoChoices choice)
	{
		system("cls");
		switch (choice)
		{
		case CurrencyList:
			_ShowCurrencies();
			break;
		case FindCurrency:
			_FindCurrency();
			break;
		case UpdateRate:
			_UpdateRate();
			break;
		case CurrencyCalc:
			_CurrencyCalc();
			break;
		default:
			return;
			break;
		}
		_ReturnBackToCurrExchangeScreen();
	}

public:

	static void ShowCurrencyMenu()
	{
		enMenuTwoChoices choice;
		do
		{
			system("cls");
			_PrintChoices();
			cout << "Choose what do want to do from 1 to " << MainMenu << "? ";
			choice = (enMenuTwoChoices)clsInputValidate::ReadNumberInRange<int>("The number entered is out of range \n Enter another Number: ", 1, MainMenu);
			_ConfirmChoice(choice);
		} while (choice != enMenuTwoChoices::MainMenu);
	}

};


