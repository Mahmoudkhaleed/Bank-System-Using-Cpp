#pragma once
#include "clsUser.h"
#include "clsScreen.h"
class clsAddNewUser
{
public:
	static void AddNewUser()
	{
		cout << "Enter A User Name: ";
		string UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "The User Is already Exist!, Enter another User Name: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser NewUser = clsUser::SetNewUser(UserName);

		clsScreen::ReadUserInfo(NewUser, "");

		string choice;
		cout << "Are you Sure You Want to Add This User? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			clsUser::enSaveResults SaveResult = NewUser.Save();
			switch (SaveResult)
			{
			case clsUser::vsFailedEmptyObj:
				cout << "\nError The User was not saved because it is empty!" << endl;
				break;
			case clsUser::svSucceeded:
				cout << "\nThe User is Added successfuly!" << endl << endl;
				clsScreen::PrintUser(NewUser);
				break;
			default:
				break;
			}
		}

	}
};

