#pragma once
#include "clsUser.h"
#include "clsScreen.h"
class clsDeleteUser
{
public:
	static void DeleteUser()
	{
		cout << "Enter A User Name To Delete: ";
		string UserName = clsInputValidate::ReadString();
		while (UserName == "admin")
		{
			cout << "This is the admin user!, Enter another User Name: ";
			UserName = clsInputValidate::ReadString();
		}
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "The User Is not Exist!, Enter another User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser client = clsUser::Find(UserName);
		cout << endl;
		clsScreen::PrintUser(client);

		string choice;
		cout << "Are you Sure You Want to Delete This User? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			client.Delete();
			clsUser::enSaveResults SaveResult = client.Save();
			switch (SaveResult)
			{
			case clsUser::vsFailedEmptyObj:
				cout << "\nError The User was not saved because it is empty!" << endl;
				break;
			case clsUser::svSucceeded:
				cout << "\nThe User is Deleted successfuly!" << endl << endl;
				break;
			default:
				break;
			}
		}
	}

};

