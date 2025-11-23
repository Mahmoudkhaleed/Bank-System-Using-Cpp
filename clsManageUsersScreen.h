#pragma once
#include "clsUtility.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsShowUsersList.h"
#include "clsAddNewUser.h"
#include "clsDeleteUser.h"
#include "clsUpdateUser.h"
#include "clsFindUser.h"

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersChoices
	{
		Show = 1,
		Add = 2,
		Delete = 3,
		Update = 4,
		Find = 5,
		MainMenu = 6
	};

	static void _ManageUsersChoices()
	{
		system("cls");
		TitleFrame("Manage Users Screen", '=');

		cout << "\t[1] Show Users List." << endl;
		cout << "\t[2] Add New User." << endl;
		cout << "\t[3] Delete User." << endl;
		cout << "\t[4] Update User info." << endl;
		cout << "\t[5] Find User." << endl;
		cout << "\t[6] Main Menu." << endl;

		cout << clsUtility::MakeLineOf(40, '=') << endl;
	}

	static void _ReturnBackToManageUsersScreen()
	{
		cout << "\nPress any key to return back to Manage Users menu...." << endl;
		system("pause>0");
	}

	static void _ShowAllUsers()
	{
		TitleFrame("Users List", '-');
		clsShowUsersList::ShowAllUsers();
	}
	static void _AddNewUser()
	{
		TitleFrame("Add New User", '-');
		clsAddNewUser::AddNewUser();
	}
	static void _DeleteUser()
	{
		TitleFrame("Delete User", '-');
		clsDeleteUser::DeleteUser();
	}
	static void _UpdateUser()
	{
		TitleFrame("Update User", '-');
		clsUpdateUser::UpdateUser();
	}
	static void _FindUser()
	{
		TitleFrame("Find User", '-');
		clsFindUser::FindUser();
	}

	static void _ConfirmChoice(enManageUsersChoices choice)
	{
		system("cls");
		switch (choice)
		{
		case Show:
			_ShowAllUsers();
			break;
		case Add:
			_AddNewUser();
			break;
		case Delete:
			_DeleteUser();
			break;
		case Update:
			_UpdateUser();
			break;
		case Find:
			_FindUser();
			break;
		default:
			return;
			break;
		}
		_ReturnBackToManageUsersScreen();
	}

public:
	static void ShowManageUsersMenu()
	{
		enManageUsersChoices choice;
		do
		{
			system("cls");
			_ManageUsersChoices();
			cout << "what do you want to do from 1 to 6? ";
			choice = (enManageUsersChoices)clsInputValidate::ReadNumberInRange<int>("The Number is Out of the Range, Enter another Number: ", 1, 6);
			_ConfirmChoice(choice);
		} while (choice != MainMenu);
	}
};

