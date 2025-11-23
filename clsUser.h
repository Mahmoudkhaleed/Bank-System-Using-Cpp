#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtility.h"

using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode 
	{
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewUserMode = 2,
		DeleteMode = 3
	};
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;

	// methods
	static string _ConvertObjToStrLine(clsUser user, string delim = "#//#")
	{
		string str;
		str += user.FirstName + delim;
		str += user.LastName + delim;
		str += user.Phone + delim;
		str += user.Email + delim;
		str += user._UserName + delim;
		str += clsUtility::EncryptText(user._Password, EncryptKey) + delim;
		str += to_string(user._Permissions);
		return str;
	}
	static clsUser _ConvertStrLineToObj(string line, string delim = "#//#")
	{
		vector<string> userObj = clsString::Split(line, delim);
		return clsUser(
			UpdateMode,
			userObj[0],
			userObj[1],
			userObj[2],
			userObj[3],
			userObj[4],
			userObj[5],
			stoi(userObj[6]));
	}
	static vector<clsUser> _LoadUsersDataFormFile()
	{
		vector<clsUser> users;
		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);
		if (UsersFile.is_open())
		{
			string line;
			while (getline(UsersFile, line))
			{
				users.push_back(_ConvertStrLineToObj(line));
			}
			UsersFile.close();
		}
		return users;
	}
	static void _SaveUsersDataToFile(vector<clsUser> users)
	{
		fstream UsersFile;
		UsersFile.open("Users.txt", ios::out);
		if (UsersFile.is_open())
		{
			for (clsUser user : users)
			{
				UsersFile << _ConvertObjToStrLine(user) << endl;
			}
			UsersFile.close();
		}
	}
	static void _AddDataLineToFile(string Line)
	{
		fstream UsersFile;
		UsersFile.open("Users.txt", ios::out | ios::app);
		if (UsersFile.is_open())
		{
			UsersFile << Line << endl;
			UsersFile.close();
		}
	}
	void _Update()
	{
		vector<clsUser> users = _LoadUsersDataFormFile();
		for (clsUser& user : users)
		{
			if (user._UserName == _UserName)
			{
				user = *this;
			}
		}
		_SaveUsersDataToFile(users);
	}
	void _AddNewUser()
	{
		_AddDataLineToFile(_ConvertObjToStrLine(*this));
	}
	void _DeleteUser()
	{
		vector<clsUser> users = _LoadUsersDataFormFile();
		vector<clsUser> NewUsers;
		for (clsUser& user : users)
		{
			if (user._UserName != _UserName)
			{
				NewUsers.push_back(user);
			}
		}
		_SaveUsersDataToFile(NewUsers);
	}
public:
	enum enUserPermission {
		eShowClientsList = 1,
		eAddNewClient = 2,
		eDeleteClient = 4,
		eUpdateClientInfo = 8,
		eFindClient = 16,
		eTransactions = 32,
		eManageUsers = 64,
		eLoginRegister = 128,
		eCurrencyExchange = 256,
	};
	clsUser(enMode Mode, string FirstName, string LastName, string Phone, string Email,
		string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Phone, Email)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = clsUtility::DecryptText(Password, EncryptKey);
		_Permissions = Permissions;
	}

	string GetUserName()
	{
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	string GetPassword()
	{
		return _Password;
	}
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	int GetPermissions()
	{
		return _Permissions;
	}
	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser EmptyUserObj()
	{
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsUser Find(string UserName)
	{
		vector<clsUser> users;
		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);

		if (UsersFile.is_open())
		{
			string line;
			while (getline(UsersFile, line))
			{
				clsUser user = _ConvertStrLineToObj(line);
				if (user.GetUserName() == UserName)
				{
					UsersFile.close();
					return user;
				}
			}
		}
		return EmptyUserObj();
	}
	static clsUser Find(string UserName, string password)
	{
		vector<clsUser> users;
		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);

		if (UsersFile.is_open())
		{
			string line;
			while (getline(UsersFile, line))
			{
				clsUser user = _ConvertStrLineToObj(line);
				if (user.GetUserName() == UserName && user.Password == password)
				{
					UsersFile.close();
					return user;
				}
			}
		}
		return EmptyUserObj();
	}
	static bool IsUserExist(string UserName)
	{
		clsUser user = clsUser::Find(UserName);
		return user._Mode != clsUser::EmptyMode;
	}
	static bool IsUserExist(string UserName, string Password)
	{
		clsUser user = clsUser::Find(UserName, Password);
		return user._Mode != clsUser::EmptyMode;
	}

	enum enSaveResults { vsFailedEmptyObj = 0, svSucceeded = 1 };
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case clsUser::EmptyMode:

			return vsFailedEmptyObj;

		case clsUser::UpdateMode:
			_Update();
			return svSucceeded;
		case clsUser::AddNewUserMode:
			_AddNewUser();
			_Mode = AddNewUserMode;
			return svSucceeded;
		case clsUser::DeleteMode:
			_DeleteUser();
			return svSucceeded;
		default:
			return vsFailedEmptyObj;
			break;
		}

	}

	static clsUser SetNewUser(string UserName)
	{
		clsUser client(AddNewUserMode, "", "", "", "", "", "", 0);
		client._UserName = UserName;
		return client;
	}

	void Delete()
	{
		string UserName = _UserName;
		*this = EmptyUserObj();
		_Mode = DeleteMode;
		_UserName = UserName;
	}

	static vector<clsUser> GetAllUsers()
	{
		return _LoadUsersDataFormFile();
	}

	static bool HasPermissionTo(int PermissionNumber, int ChoiceNumber)
	{
		return PermissionNumber == -1 ? 1 : (PermissionNumber & ChoiceNumber) == ChoiceNumber;
	}
};
