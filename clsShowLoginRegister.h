#pragma once
#include "clsLoginHistory.h"

class clsShowLoginRegister
{
private:
	static void _PrintLoginHistoryInfoInline(clsLoginHistory& History)
	{
		cout << "| " << left << setw(23) << History.GetDate();
		cout << "| " << left << setw(20) << History.GetUserName();
		cout << "| " << left << setw(15) << History.GetPassword();
		cout << "| " << left << setw(17) << History.GetPermissions() << endl;
	}
public:
	static void ShowAllLoginRegister()
	{
		vector<clsLoginHistory> Historys = clsLoginHistory::GetAllLoginResiger();
		cout << "Login History List (" << Historys.size() << ") Login/s" << endl;
		cout << clsUtility::MakeLineOf(100) << endl << endl;
		cout << "| " << left << setw(4) << "I";
		cout << "| " << left << setw(23) << "Date";
		cout << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(17) << "Permissions" << endl;
		cout << clsUtility::MakeLineOf(100) << endl << endl;
		int i = 0;
		for (clsLoginHistory& History : Historys)
		{
			cout << "| " << left << setw(4) << i + 1;
			_PrintLoginHistoryInfoInline(History);
			i++;
		}
		cout << clsUtility::MakeLineOf(100) << endl;
	}

};

