#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsUser.h"
#include "clsDate.h"

class clsLoginHistory
{
private:
	string _Date;
	string _Username;
	string _Password;
	int _Permissions;

	static string _ConvertObjToStrLine(clsLoginHistory history, string delim = "#//#")
	{
		string str;
		str += history._Date + delim;
		str += history._Username + delim;
		str += clsUtility::EncryptText(history._Password, EncryptKey) + delim;
		str += to_string(history._Permissions);
		return str;
	}
	static void _AddDataLineToFile(string Line)
	{
		fstream LoginHistoryFile;
		LoginHistoryFile.open("LoginHistory.txt", ios::out | ios::app);
		if (LoginHistoryFile.is_open())
		{
			LoginHistoryFile << Line << endl;
			LoginHistoryFile.close();
		}
	}

	static clsLoginHistory _ConvertStrLineToObj(string line, string delim = "#//#")
	{
		vector<string> historyObj = clsString::Split(line, delim);
		return clsLoginHistory(historyObj[0], historyObj[1], historyObj[2], stoi(historyObj[3]));
	}
	static vector<clsLoginHistory> _LoadLoginHistoryDataFormFile()
	{
		vector<clsLoginHistory> history;
		fstream LoginHistoryFile;
		LoginHistoryFile.open("LoginHistory.txt", ios::in);
		if (LoginHistoryFile.is_open())
		{
			string line;
			while (getline(LoginHistoryFile, line))
			{
				history.push_back(_ConvertStrLineToObj(line));
			}
			LoginHistoryFile.close();
		}
		return history;
	}

public:
	clsLoginHistory(string Date, string Username, string Password, int Permissions)
	{
		_Date = Date;
		_Username = Username;
		_Password = clsUtility::DecryptText(Password, EncryptKey);
		_Permissions = Permissions;
	}

	string GetDate()
	{
		return _Date;
	}
	
	string GetUserName()
	{
		return _Username;
	}

	string GetPassword()
	{
		return _Password;
	}

	int GetPermissions()
	{
		return _Permissions;
	}


	static void AddUserToLoginHistory(clsUser& user)
	{
		string Date = clsDate::DateToString(clsDate::GetSystemDate()) + " - " + clsDate::GetSystemTime();
		clsLoginHistory History(Date, user.UserName, clsUtility::EncryptText(user.Password, EncryptKey), user.Permissions);

		_AddDataLineToFile(_ConvertObjToStrLine(History));
	}

	static vector<clsLoginHistory> GetAllLoginResiger()
	{
		return _LoadLoginHistoryDataFormFile();
	}
};

