#pragma once
#include "clsUser.h"
#include "clsScreen.h"

class clsUpdateUser
{
public:
	static void UpdateUser()
	{
		cout << "Enter A User Name To Update: ";
		string UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "The User is not exist, Enter another User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::Find(UserName);
		cout << endl;
		clsScreen::PrintUser(user);

		string choice;
		cout << "Are you Sure You Want to Update? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			clsScreen::ReadUserInfo(user, "");
			clsUser::enSaveResults SaveResult = user.Save();
			switch (SaveResult)
			{
			case clsUser::vsFailedEmptyObj:
				cout << "\nError The account was not saved because it is empty!" << endl;
				break;
			case clsUser::svSucceeded:
				cout << "\nThe Account is updated successfuly!" << endl << endl;
				clsScreen::PrintUser(user);
				break;
			default:
				break;
			}
		}

	}

};

