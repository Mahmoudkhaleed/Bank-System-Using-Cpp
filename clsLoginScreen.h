#pragma once
#include "clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUtility.h"
#include "clsLoginHistory.h"
#include "global.h"

class clsLoginScreen : protected clsScreen
{
public:
	static void ShowLoginScreen()
	{
		int trails;
		do
		{
			trails = 2;
			TitleFrame("Login Screen", '=');
			cout << "Enter Your Username: ";
			string UserName = clsInputValidate::ReadString();
			cout << "Enter Your Password: ";
			string Password = clsInputValidate::ReadString();
			while (!clsUser::IsUserExist(UserName, Password) && trails > 0)
			{
				system("cls");
				TitleFrame("Login Screen", '=');
				cout << "Incorrect username or password" << endl;
				cout << "You still have " << clsUtility::ConvertNumberToText(trails) << " attempt" << (trails > 1 ? "s" : "") << endl;

				cout << "Enter Your Username: ";
				UserName = clsInputValidate::ReadString();
				cout << "Enter Your Password: ";
				Password = clsInputValidate::ReadString();
				trails--;
			}
			if (trails > 0)
			{
				CurrentUser = clsUser::Find(UserName, Password);
				clsLoginHistory::AddUserToLoginHistory(CurrentUser);
				clsMainScreen::ShowMainMenu();
			}
			else
			{
				cout << "You are locked after Three attempts!" << endl;
			}
		} while (trails > 0);
	}
};

