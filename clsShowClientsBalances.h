#pragma once
#include "clsClient.h"

class clsShowClientsBalances
{
private:
	static void _PrintClientBalanceLine(clsClient& client)
	{
		cout << "| " << left << setw(20) << client.GetAccountNumber();
		cout << "| " << left << setw(30) << client.GetFullName();
		cout << "| " << left << setw(30) << client.Salary << endl;
	}
public:
	static void ShowTotalBalances()
	{
		vector<clsClient> clients = clsClient::GetAllClients();
		cout << "\t\t\t\t\tClient List (" << clients.size() << ") Client/s" << endl;
		cout << clsUtility::MakeLineOf(95) << endl << endl;
		cout << "| " << left << setw(3) << "I";
		cout << "| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(30) << "Client Name";
		cout << "| " << left << setw(30) << "Balance" << endl;
		cout << clsUtility::MakeLineOf(95) << endl << endl;
		int i = 0;
		for (clsClient& client : clients)
		{
			cout << "| " << left << setw(3) << ++i;
			_PrintClientBalanceLine(client);
		}
		cout << clsUtility::MakeLineOf(95) << endl;
		float totalBalances = clsClient::GetTotalBalances();
		cout << "\t\t\t\t\tTotal Balances = " << totalBalances << "EP" << endl;
		cout << "\t\t\t\t\t(" << clsUtility::ConvertNumberToText(int(totalBalances)) << ")" << endl;
	}

};

