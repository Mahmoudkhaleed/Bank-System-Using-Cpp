#pragma once
#include "clsUtility.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
// Client
#include "clsShowClientsList.h"
#include "clsAddNewClient.h"
#include "clsDeleteClient.h"
#include "clsUpdateClient.h"
#include "clsFindClient.h"
/////
#include "clsTransactionScreen.h"
#include "clsManageUsersScreen.h"
#include "clsCurrencyScreen.h"
////
#include "clsShowLoginRegister.h"


class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuChoices
	{
		Show = 1,
		Add = 2,
		Delete = 3,
		Update = 4,
		Find = 5,
		Trans = 6,
		ManageUsers = 7,
		LoginRegister = 8,
		CurrencyExchange = 9,
		Logout = 10
	};

	static void _MainMenuChoices(int Permissions)
	{
		system("cls");
		TitleFrame("Main Menu Screen", '=');

		cout << "\t[1] Show Clients List." << (!clsUser::HasPermissionTo(Permissions, 1) ? " (Denied)" : "") << endl;
		cout << "\t[2] Add New Client." << (!clsUser::HasPermissionTo(Permissions, 2) ? " (Denied)" : "") << endl;
		cout << "\t[3] Delete Client." << (!clsUser::HasPermissionTo(Permissions, 4) ? " (Denied)" : "") << endl;
		cout << "\t[4] Update Client info." << (!clsUser::HasPermissionTo(Permissions, 8) ? " (Denied)" : "") << endl;
		cout << "\t[5] Find Client." << (!clsUser::HasPermissionTo(Permissions, 16) ? " (Denied)" : "") << endl;
		cout << "\t[6] Transactions." << (!clsUser::HasPermissionTo(Permissions, 32) ? " (Denied)" : "") << endl;
		cout << "\t[7] Manage Users." << (!clsUser::HasPermissionTo(Permissions, 64) ? " (Denied)" : "") << endl;
		cout << "\t[8] Login Register." << (!clsUser::HasPermissionTo(Permissions, 128) ? " (Denied)" : "") << endl;
		cout << "\t[9] Currency Exchange." << (!clsUser::HasPermissionTo(Permissions, clsUser::eCurrencyExchange) ? " (Denied)" : "") << endl;
		cout << "\t[10] Logout." << endl;

		cout << clsUtility::MakeLineOf(40, '=') << endl;
	}

	static void _ReturnBackToMainScreen()
	{
		cout << "\npress any key to return back to the main menu...." << endl;
		system("pause>0");
	}

	static void _ShowAllClients()
	{
		TitleFrame("Clients List", '-');
		clsShowClientsList::ShowAllClients();
	}
	static void _AddNewClient()
	{
		TitleFrame("Add New Client", '-');
		clsAddNewClient::AddNewClient();
	}
	static void _DeleteClient()
	{
		TitleFrame("Delete Client", '-');
		clsDeleteClient::DeleteClient();
	}
	static void _UpdateClient()
	{
		TitleFrame("Update Client", '-');
		clsUpdateClient::UpdateClient();
	}
	static void _FindClient()
	{
		TitleFrame("Find Client", '-');
		clsFindClient::FindClient();
	}

	static void _Transaction()
	{
		clsTransactionScreen::ShowTransactionMenu();
	}
	static void _ManageUsers()
	{
		clsManageUsersScreen::ShowManageUsersMenu();
	}
	static void _ShowLoginRegister()
	{
		TitleFrame("Login Register", '-');
		clsShowLoginRegister::ShowAllLoginRegister();
	}
	static void _CurrencyExchange()
	{
		TitleFrame("Currency Exchange", '-');
		clsCurrencyScreen::ShowCurrencyMenu();
	}

	static void _ConfirmChoice(enMainMenuChoices choice)
	{
		system("cls");
		switch (choice)
		{
		case Show:
			if ((CurrentUser.Permissions & clsUser::eShowClientsList) == clsUser::eShowClientsList || CurrentUser.Permissions == -1)
				_ShowAllClients();
			else
				PermissionDenied();
			_ReturnBackToMainScreen();
			break;
		case Add:
			if ((CurrentUser.Permissions & clsUser::eAddNewClient) == clsUser::eAddNewClient || CurrentUser.Permissions == -1)
				_AddNewClient();
			else
				PermissionDenied();
			_ReturnBackToMainScreen();
			break;
		case Delete:
			if ((CurrentUser.Permissions & clsUser::eDeleteClient) == clsUser::eDeleteClient || CurrentUser.Permissions == -1)
				_DeleteClient();
			else
				PermissionDenied();
			_ReturnBackToMainScreen();
			break;
		case Update:
			if ((CurrentUser.Permissions & clsUser::eUpdateClientInfo) == clsUser::eUpdateClientInfo || CurrentUser.Permissions == -1)
				_UpdateClient();
			else
				PermissionDenied();
			_ReturnBackToMainScreen();
			break;
		case Find:
			if ((CurrentUser.Permissions & clsUser::eFindClient) == clsUser::eFindClient || CurrentUser.Permissions == -1)
				_FindClient();
			else
				PermissionDenied();
			_ReturnBackToMainScreen();
			break;
		case Trans:
			if ((CurrentUser.Permissions & clsUser::eTransactions) == clsUser::eTransactions || CurrentUser.Permissions == -1)
				_Transaction();
			else
			{
				PermissionDenied();
				_ReturnBackToMainScreen();
			}
			break;
		case ManageUsers:
			if ((CurrentUser.Permissions & clsUser::eManageUsers) == clsUser::eManageUsers || CurrentUser.Permissions == -1)
				_ManageUsers();
			else
			{
				PermissionDenied();
				_ReturnBackToMainScreen();
			}
			break;
		case LoginRegister:
			if ((CurrentUser.Permissions & clsUser::eLoginRegister) == clsUser::eLoginRegister || CurrentUser.Permissions == -1)
				_ShowLoginRegister();
			else
			{
				PermissionDenied();
			}
			_ReturnBackToMainScreen();
			break;
		case CurrencyExchange:
			if ((CurrentUser.Permissions & clsUser::eCurrencyExchange) == clsUser::eCurrencyExchange || CurrentUser.Permissions == -1)
				_CurrencyExchange();
			else
			{
				PermissionDenied();
				_ReturnBackToMainScreen();
			}
			break;
		default:
			return;
		}
	}

public:
	static void ShowMainMenu()
	{
		enMainMenuChoices choice;
		do
		{
			system("cls");
			_MainMenuChoices(CurrentUser.Permissions);
			cout << "Hello " << CurrentUser.GetFullName() << "," << endl;
			cout << "What do you want to do from 1 to " << Logout << "? ";
			choice = (enMainMenuChoices)clsInputValidate::ReadNumberInRange<int>("The Number is Out of the Range, Enter another Number: ", 1, Logout);
			_ConfirmChoice(choice);
		} while (choice != enMainMenuChoices::Logout);
		CurrentUser = clsUser::Find("");
	}
};

