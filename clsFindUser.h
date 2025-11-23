#pragma once
#include "clsUser.h"
#include "clsScreen.h"

class clsFindUser
{
public:
	static void FindUser()
	{
		cout << "Enter A User Name: ";
		string UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "The User is not exist, Enter another User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::Find(UserName);
		cout << endl;
		clsScreen::PrintUser(user);
	}
};

