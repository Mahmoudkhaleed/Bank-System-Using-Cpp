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
#include "clsClient.h"

class clsTransferHistory
{
private:
	string _Date;
	string _Client1AccountNumber;
	string _Client2AccountNumber;
	float _Client1SalaryAfterProcess;
	float _Client2SalaryAfterProcess;
	float _AmountOfTransfer;
	string _Username;

	static string _ConvertObjToStrLine(clsTransferHistory history, string delim = "#//#")
	{
		string str;
		str += history._Date + delim;
		str += history._Client1AccountNumber + delim;
		str += history._Client2AccountNumber + delim;
		str += to_string(history._Client1SalaryAfterProcess) + delim;
		str += to_string(history._Client2SalaryAfterProcess) + delim;
		str += to_string(history._AmountOfTransfer) + delim;
		str += history._Username;
		return str;
	}
	static void _AddDataLineToFile(string Line)
	{
		fstream TransferHistoryFile;
		TransferHistoryFile.open("TransferLogs.txt", ios::out | ios::app);
		if (TransferHistoryFile.is_open())
		{
			TransferHistoryFile << Line << endl;
			TransferHistoryFile.close();
		}
	}

	static clsTransferHistory _ConvertStrLineToObj(string line, string delim = "#//#")
	{
		vector<string> historyObj = clsString::Split(line, delim);
		return clsTransferHistory(historyObj[0], historyObj[1], historyObj[2], stof(historyObj[3]), stof(historyObj[4]), stof(historyObj[5]), historyObj[6]);
	}
	static vector<clsTransferHistory> _LoadTransferHistoryDataFormFile()
	{
		vector<clsTransferHistory> history;
		fstream TransferHistoryFile;
		TransferHistoryFile.open("TransferLogs.txt", ios::in);
		if (TransferHistoryFile.is_open())
		{
			string line;
			while (getline(TransferHistoryFile, line))
			{
				history.push_back(_ConvertStrLineToObj(line));
			}
			TransferHistoryFile.close();
		}
		return history;
	}

public:
	clsTransferHistory(
		string Date,
		string Client1AccountNumber,
		string Client2AccountNumber,
		int Client1SalaryAfterProcess,
		int Client2SalaryAfterProcess, 
		int AmountOfTransfer,
		string Username)
	{
		_Date = Date;
		_Client1AccountNumber = Client1AccountNumber;
		_Client2AccountNumber = Client2AccountNumber;
		_Client1SalaryAfterProcess = Client1SalaryAfterProcess;
		_Client2SalaryAfterProcess = Client2SalaryAfterProcess;
		_AmountOfTransfer = AmountOfTransfer;
		_Username = Username;
	}

	string GetDate()
	{
		return _Date;
	}

	string GetUserName()
	{
		return _Username;
	}

	string GetClient1AccountNumber()
	{
		return _Client1AccountNumber;
	}

	string GetClient2AccountNumber()
	{
		return _Client2AccountNumber;
	}

	float GetClient1SalaryAfterProcess()
	{
		return _Client1SalaryAfterProcess;
	}
	float GetClient2SalaryAfterProcess()
	{
		return _Client2SalaryAfterProcess;
	}
	float GetAmountOfTransfer()
	{
		return _AmountOfTransfer;
	}


	static void AddProcessToTransferHistory(clsClient &client1, clsClient &client2, float Amount, clsUser &user)
	{
		string Date = clsDate::DateToString(clsDate::GetSystemDate()) + " - " + clsDate::GetSystemTime();
		clsTransferHistory History(Date, client1.GetAccountNumber(), client2.GetAccountNumber(), client1.Salary, client2.Salary, Amount, user.GetUserName());

		_AddDataLineToFile(_ConvertObjToStrLine(History));
	}

	static vector<clsTransferHistory> GetAllTransfers()
	{
		return _LoadTransferHistoryDataFormFile();
	}
};

