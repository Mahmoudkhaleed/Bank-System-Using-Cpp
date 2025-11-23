#pragma once
#include "clsUser.h"
class clsShowUsersList
{
private:
	static void _PrintUserInfoInline(clsUser& user)
	{
		cout << "| " << left << setw(16) << user.UserName;
		cout << "| " << left << setw(15) << user.Password;
		cout << "| " << left << setw(24) << user.GetFullName();
		cout << "| " << left << setw(17) << user.Phone;
		cout << "| " << left << setw(20) << user.Email;
		cout << "| " << left << setw(16) << user.Permissions << endl;
	}
public:
	static void ShowAllUsers()
	{
		vector<clsUser> users = clsUser::GetAllUsers();
		cout << "User List (" << users.size() << ") User/s" << endl;
		cout << clsUtility::MakeLineOf(120) << endl << endl;
		cout << "| " << left << setw(3) << "I";
		cout << "| " << left << setw(16) << "User Name";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(24) << "Full Name";
		cout << "| " << left << setw(17) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(16) << "Permissions" << endl;
		cout << clsUtility::MakeLineOf(120) << endl << endl;
		int i = 0;
		for (clsUser& user : users)
		{
			cout << "| " << left << setw(3) << i + 1;
			_PrintUserInfoInline(user);
			i++;
		}
		cout << clsUtility::MakeLineOf(120) << endl;
	}

};

