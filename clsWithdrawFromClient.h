#pragma once
#include "clsClient.h"
#include "clsScreen.h"

class clsWithdrawFromClient
{
public:
	static void WithdrawFromClient()
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
		cout << "please enter a withdraw number? ";
		double withdraw = clsInputValidate::ReadNumber<double>("Invalid Number, please enter a withdraw number? ");
		while (client.Salary <= withdraw)
		{
			cout << "There is not enough money to withdraw!" << endl;
			cout << "please enter another number to withdraw? ";
			withdraw = clsInputValidate::ReadNumber<double>("Invalid Number, please enter a withdraw number? ");
		}
		char state;
		cout << "Are you sure you want to perform this transaction? Y/N ";
		cin >> state;
		if (tolower(state) == 'y')
		{
			client.Withdraw(withdraw);
			cout << "\nThe Account Balance is updated successfuly!" << endl << endl;
			clsScreen::PrintClient(client);
			cout << "The account balance is now: " << client.Salary << endl;

		}
	}
};

