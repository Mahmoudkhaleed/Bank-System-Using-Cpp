#pragma once
#include "clsUtility.h"
#include "clsDate.h"
#include "clsClient.h"
#include "clsUser.h"
#include "clsCurrency.h"
#include <cmath>

class clsScreen
{
private:
	static void _HandlePermissionChoice(clsUser& newUser, int choiceNumber, string choiceName)
	{
		char yOrN;
		do
		{
			cout << choiceName << "? Y/N ";
			cin >> yOrN;
		} while (tolower(yOrN) != 'y' && tolower(yOrN) != 'n');

		if (tolower(yOrN) == 'y')
			newUser.Permissions = (newUser.Permissions | choiceNumber); // 1
	}
	static void _ReadUserPermission(clsUser& newUser)
	{
		newUser.Permissions = 0;
		_HandlePermissionChoice(newUser, clsUser::eShowClientsList, "Show Clients List");
		_HandlePermissionChoice(newUser, clsUser::eAddNewClient, "Add New Client");
		_HandlePermissionChoice(newUser, clsUser::eDeleteClient, "Delete Client");
		_HandlePermissionChoice(newUser, clsUser::eUpdateClientInfo, "Update Client info");
		_HandlePermissionChoice(newUser, clsUser::eFindClient, "Find Client");
		_HandlePermissionChoice(newUser, clsUser::eTransactions, "Transactions");
		_HandlePermissionChoice(newUser, clsUser::eManageUsers, "Manage Users");
		_HandlePermissionChoice(newUser, clsUser::eLoginRegister, "Login Register");
		_HandlePermissionChoice(newUser, clsUser::eCurrencyExchange, "Currency Exchange");
	}
	static string _TranslatePermissionNumber(int PermissionNumber)
	{
		string strPermissions;
		if (PermissionNumber == -1)
			return "All";
		if ((PermissionNumber & clsUser::eShowClientsList) == clsUser::eShowClientsList)
		{
			strPermissions += "Show Clients List, ";
		}
		if ((PermissionNumber & clsUser::eAddNewClient) == clsUser::eAddNewClient)
		{
			strPermissions += "Add New Client, ";
		}
		if ((PermissionNumber & clsUser::eDeleteClient) == clsUser::eDeleteClient)
		{
			strPermissions += "Delete Client, ";
		}
		if ((PermissionNumber & clsUser::eUpdateClientInfo) == clsUser::eUpdateClientInfo)
		{
			strPermissions += "Update Client info, ";
		}
		if ((PermissionNumber & clsUser::eFindClient) == clsUser::eFindClient)
		{
			strPermissions += "Find Client, ";
		}
		if ((PermissionNumber & clsUser::eTransactions) == clsUser::eTransactions)
		{
			strPermissions += "Transactions, ";
		}
		if ((PermissionNumber & clsUser::eManageUsers) == clsUser::eManageUsers)
		{
			strPermissions += "Manage Users, ";
		}
		if ((PermissionNumber & clsUser::eLoginRegister) == clsUser::eLoginRegister)
		{
			strPermissions += "Login Register, ";
		}
		if ((PermissionNumber & clsUser::eCurrencyExchange) == clsUser::eCurrencyExchange)
		{
			strPermissions += "Currency Exchange, ";
		}
		return strPermissions;
	}

public:
	static void TitleFrame(string title, char theme = '-', int width = 40)
	{
		string date = clsDate::DateToTextFormat(clsDate::GetSystemDate());
		cout << clsUtility::MakeLineOf(width, theme) << endl;
		cout << "||" << clsUtility::MakeLineOf((width / 2) - (title.length() / 2) - 2, ' ') << title << clsUtility::MakeLineOf((width / 2) - ceil(float(title.length()) / 2) - 2, ' ') << "||" << endl;
		cout << "||" << clsUtility::MakeLineOf(width - 4, ' ') << "||" << endl;
		cout << "||" << clsUtility::MakeLineOf((width / 2) - (date.length() / 2) - 2, ' ') << date  << clsUtility::MakeLineOf((width / 2) - ceil(float(date.length()) / 2) - 2, ' ') << "||" << endl;
		cout << clsUtility::MakeLineOf(width, theme) << endl << endl;
	}

	static void ReadClientInfo(clsClient& client, string headline)
	{
		cout << headline;
		cout << "Enter First Name: ";
		client.FirstName = clsInputValidate::ReadString();
		cout << "Enter Last Name: ";
		client.LastName = clsInputValidate::ReadString();
		cout << "Enter Phone: ";
		client.Phone = clsInputValidate::ReadString();
		cout << "Enter Email: ";
		client.Email = clsInputValidate::ReadString();
		cout << "Enter Pin Code: ";
		client.PinCode = clsInputValidate::ReadString();
		cout << "Enter Salary: ";
		client.Salary = clsInputValidate::ReadNumber<double>("Invalid, Enter Again: ");
	}
	static void ReadUserInfo(clsUser& user, string headline)
	{
		cout << headline;
		cout << "Enter First Name: ";
		user.FirstName = clsInputValidate::ReadString();
		cout << "Enter Last Name: ";
		user.LastName = clsInputValidate::ReadString();
		cout << "Enter Phone: ";
		user.Phone = clsInputValidate::ReadString();
		cout << "Enter Email: ";
		user.Email = clsInputValidate::ReadString();
		cout << "Enter Password: ";
		user.Password = clsInputValidate::ReadString();
		cout << "Premissions" << endl;
		char choice;
		cout << "Do you want full permissions? y/n ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			user.Permissions = -1;
			return;
		}
		cout << "Do you want to give access to: \n\n";
		_ReadUserPermission(user);
	}

	static void PrintClient(clsClient& client)
	{
		cout << "Client With (" << client.GetAccountNumber() << ") Account Number" << endl;
		cout << "___________________________________\n" << endl;
		cout << "- First Name    : " << client.FirstName << endl;
		cout << "- Last Name     : " << client.LastName << endl;
		cout << "- Name          : " << client.GetFullName() << endl;
		cout << "- Phone         : " << client.Phone << endl;
		cout << "- Email         : " << client.Email << endl;
		cout << "- Pin Code      : " << client.PinCode << endl;
		cout << "- Salary        : " << client.Salary << endl;
		cout << "___________________________________" << endl;
	}
	static void PrintUser(clsUser user)
	{
		cout << "User With (" << user.UserName << ") Account Number" << endl;
		cout << "___________________________________\n" << endl;
		cout << "- First Name    : " << user.FirstName << endl;
		cout << "- Last Name     : " << user.LastName << endl;
		cout << "- Name          : " << user.GetFullName() << endl;
		cout << "- Phone         : " << user.Phone << endl;
		cout << "- Email         : " << user.Email << endl;
		cout << "- Password      : " << user.Password << endl;
		cout << "- Permissions   : " << _TranslatePermissionNumber(user.Permissions) << endl;
		cout << "___________________________________" << endl;
	}
	static void PrintCurrency(clsCurrency currency)
	{
		cout << "Currency Card" << endl;
		cout << "___________________________________\n" << endl;
		cout << "- Country       : " << currency.Country << endl;
		cout << "- Currency Code : " << currency.CurrencyCode << endl;
		cout << "- Currency Name : " << currency.CurrencyName << endl;
		cout << "- Rate          : " << currency.Rate << endl;
		cout << "___________________________________" << endl;
	}

	static void PermissionDenied()
	{
		system("cls");
		cout << "--------------------------------------" << endl;
		cout << "Access Denied" << endl;
		cout << "You don't have permission to do this," << endl;
		cout << "Please connect your admin." << endl;
		cout << "--------------------------------------" << endl;
	}

};

