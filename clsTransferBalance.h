#pragma once
#include "clsClient.h"
#include "clsTransferHistory.h"

class clsTransferBalance
{
private:
	static void _PrintClient(clsClient& client)
	{
		cout << "Client Card " << endl;
		cout << "___________________________________\n" << endl;
		cout << "- Full Name      : " << client.GetFullName() << endl;
		cout << "- Account number : " << client.GetAccountNumber() << endl;
		cout << "- Salary         : " << client.Salary << endl;
		cout << "___________________________________" << endl;
	}
	static clsClient _ReadClientAccountNumber(string operation, bool Withdraw = true)
	{
		cout << "Enter An Account Number To " + operation + ": ";
		string AccNumber = clsInputValidate::ReadString();
		while (!clsClient::IsClientExist(AccNumber))
		{
			cout << "The Client is not exist, Enter another Account Number To " + operation + ": ";
			AccNumber = clsInputValidate::ReadString();
		}
		clsClient client = clsClient::Find(AccNumber);

		if (Withdraw)
		{
			while (client.Salary == 0)
			{
				cout << "The Client has no enough money, Enter another Account Number To " + operation + ": ";
				AccNumber = clsInputValidate::ReadString();
				while (!clsClient::IsClientExist(AccNumber))
				{
					cout << "The Client is not exist, Enter another Account Number To " + operation + ": ";
					AccNumber = clsInputValidate::ReadString();
				}
				client = clsClient::Find(AccNumber);
			}
		}

		cout << endl;
		_PrintClient(client);
		return clsClient::Find(AccNumber);
	}
	static void _PerformTransferOperation(clsClient& FromClient1, clsClient& ToClient2)
	{
		cout << "Please enter a number to transfer to " << ToClient2.GetAccountNumber() << ": ";
		double Amount = clsInputValidate::ReadNumber<double>("Invalid Number, please enter another number: ");
		while (FromClient1.Salary < Amount)
		{
			cout << "There is not enough money to transfer!" << endl;
			cout << "please enter another number to transfer? ";
			Amount = clsInputValidate::ReadNumber<double>("Invalid Number, please enter another number: ");
		}
		char state;
		cout << "Are you sure you want to perform this Transfer? Y/N ";
		cin >> state;
		if (tolower(state) == 'y')
		{
			FromClient1.Transfer(Amount, ToClient2);
			clsTransferHistory::AddProcessToTransferHistory(FromClient1, ToClient2, Amount, CurrentUser);
			cout << "\nThe Transfer is Done successfuly!" << endl << endl;
			_PrintClient(FromClient1);
			cout << endl;
			_PrintClient(ToClient2);
		}
	}

public:
	static void TransferFromClientToAnother()
	{
		clsClient FromClient1 = _ReadClientAccountNumber("Withdraw From");
		cout << endl;
		clsClient ToClient2 = _ReadClientAccountNumber("Transfer To", false);
		cout << endl;
		_PerformTransferOperation(FromClient1, ToClient2);
	}
	

};

