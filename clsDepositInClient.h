#pragma once
#include "clsClient.h"

class clsDepositInClient
{
public:
	static void DepositInClient()
	{
		cout << "Please enter an account number? ";
		string accNumber = clsInputValidate::ReadString();
		vector<clsClient> clients = clsClient::GetAllClients();

		while (!clsClient::IsClientExist(accNumber))
		{
			cout << "CLient with " << accNumber << " account number is not exist" << endl;
			cout << "Please enter an account number? " << endl;
			accNumber = clsInputValidate::ReadString();
		}
		clsClient client = clsClient::Find(accNumber);

		clsScreen::PrintClient(client);
		cout << "please enter a deposit number? ";
		double deposit = clsInputValidate::ReadNumber<double>("Invalid Number, please enter a deposit number? ");

		char state;
		cout << "Are you sure you want to perform this transaction? Y/N ";
		cin >> state;
		if (tolower(state) == 'y')
		{
			client.Deposit(deposit);
			cout << "\nThe Account Salary is updated successfuly!" << endl << endl;
			clsScreen::PrintClient(client);
			cout << "The account balance is now: " << client.Salary << endl;
		}
	}
};

