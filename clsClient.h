#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtility.h"

class clsClient : public clsPerson
{
private:
	enum enMode {
		EmptyMode = 0, 
		UpdateMode = 1, 
		AddNewClientMode = 2, 
		DeleteMode = 3
	};

	// propreties
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _Salary;

	// methods
	static string _ConvertObjToStrLine(clsClient client, string delim = "#//#")
	{
		string str;
		str += client.FirstName + delim;
		str += client.LastName + delim;
		str += client.Phone + delim;
		str += client.Email + delim;
		str += client._AccountNumber + delim;
		str += clsUtility::EncryptText(client._PinCode, EncryptKey) + delim;
		str += to_string(client._Salary);
		return str;
	}
	static clsClient _ConvertStrLineToObj(string line, string delim = "#//#")
	{
		vector<string> clientObj = clsString::Split(line, delim);
		return clsClient(clsClient::UpdateMode,clientObj[0], clientObj[1], clientObj[2], clientObj[3], clientObj[4], clientObj[5], stof(clientObj[6]));
	}
	static clsClient _EmptyClientObj()
	{
		return clsClient(EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector<clsClient> _LoadClientsDataFormFile()
	{
		vector<clsClient> clients;
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::in);
		if (ClientsFile.is_open())
		{
			string line;
			while (getline(ClientsFile, line))
			{
				clients.push_back(_ConvertStrLineToObj(line));
			}
			ClientsFile.close();
		}
		return clients;
	}
	
	static void _SaveClientsDataToFile(vector<clsClient> clients)
	{
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::out);
		if (ClientsFile.is_open())
		{
			for (clsClient client : clients)
			{
				ClientsFile << _ConvertObjToStrLine(client) << endl;
			}
			ClientsFile.close();
		}
	}
	static void _AddDataLineToFile(string Line)
	{
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::out| ios::app);
		if (ClientsFile.is_open())
		{
			ClientsFile << Line << endl;
			ClientsFile.close();
		}
	}
	
	void _Update()
	{
		vector<clsClient> clients = _LoadClientsDataFormFile();
		for (clsClient &client : clients)
		{
			if (client._AccountNumber == _AccountNumber)
			{
				client = *this;
			}
		}
		_SaveClientsDataToFile(clients);
	}
	void _AddNewClient()
	{
		_AddDataLineToFile(_ConvertObjToStrLine(*this));
	}
	void _DeleteClient()
	{
		vector<clsClient> clients = _LoadClientsDataFormFile();
		vector<clsClient> NewClients;
		for (clsClient& client : clients)
		{
			if (client._AccountNumber != _AccountNumber)
			{
				NewClients.push_back(client);
			}
		}
		_SaveClientsDataToFile(NewClients);
	}

public:
	clsClient(enMode Mode, string FirstName, string LastName, string Phone, string Email, string AccountNumber, string PinCode, float Salary)
		: clsPerson(FirstName, LastName, Phone, Email)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = clsUtility::DecryptText(PinCode, EncryptKey);
		_Salary = Salary;
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}
	
	string GetPinCode()
	{
		return _PinCode;
	}
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	float GetSalary()
	{
		return _Salary;
	}
	void SetSalary(float Salary)
	{
		_Salary = Salary;
	}
	__declspec(property(get = GetSalary, put = SetSalary)) float Salary;

	static clsClient Find(string AccountNumber)
	{
		vector<clsClient> clients;
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::in);

		if (ClientsFile.is_open())
		{
			string line;
			while (getline(ClientsFile, line))
			{
				clsClient client = _ConvertStrLineToObj(line);
				if (client.GetAccountNumber() == AccountNumber)
				{
					ClientsFile.close();
					return client;
				}
			}
		}
		return _EmptyClientObj();
	}
	static clsClient Find(string AccountNumber, string pincode)
	{
		vector<clsClient> clients;
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::in);

		if (ClientsFile.is_open())
		{
			string line;
			while (getline(ClientsFile, line))
			{
				clsClient client = _ConvertStrLineToObj(line);
				if (client.GetAccountNumber() == AccountNumber && client.PinCode == pincode)
				{
					ClientsFile.close();
					return client;
				}
			}
		}
		return _EmptyClientObj();
	}
	static bool IsClientExist(string AccountNumber)
	{
		clsClient client = clsClient::Find(AccountNumber);
		return client._Mode != clsClient::EmptyMode;
	}

	enum enSaveResults { vsFailedEmptyObj = 0, svSucceeded = 1};
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case clsClient::EmptyMode:

			return vsFailedEmptyObj;

		case clsClient::UpdateMode:
			_Update();
			return svSucceeded;
		case clsClient::AddNewClientMode:
			_AddNewClient();
			return svSucceeded;
		case clsClient::DeleteMode:
			_DeleteClient();
			return svSucceeded;
		default:
			return vsFailedEmptyObj;
			break;
		}

	}

	static clsClient SetNewClient(string AccNumber)
	{
		clsClient client(AddNewClientMode, "", "", "", "", "", "", 0);
		client._AccountNumber = AccNumber;
		return client;
	}

	void Delete()
	{
		string AccNumber = _AccountNumber;
		*this = _EmptyClientObj();
		_Mode = DeleteMode;
		_AccountNumber = AccNumber;
	}

	void Deposit(int DepositNumber)
	{
		Salary += DepositNumber;
		Save();
	}
	
	void Withdraw(int WithdrawNumber)
	{
		Salary -= WithdrawNumber;
		Save();
	}

	void Transfer(int TransferNumber, clsClient& RecievedClient)
	{
		Withdraw(TransferNumber);
		RecievedClient.Deposit(TransferNumber);
	}

	static vector<clsClient> GetAllClients()
	{
		return _LoadClientsDataFormFile();
	}

	static float GetTotalBalances()
	{
		float totalBalances = 0;
		vector<clsClient> clients = clsClient::GetAllClients();
		for (clsClient& client : clients)
		{
			totalBalances += client.Salary;
		}
		return totalBalances;
	}
};

