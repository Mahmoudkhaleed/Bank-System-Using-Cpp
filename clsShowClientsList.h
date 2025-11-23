#pragma once
#include "clsClient.h"

class clsShowClientsList
{
	static void _PrintClientInfoInline(clsClient& client)
	{
		cout << "| " << left << setw(16) << client.GetAccountNumber();
		cout << "| " << left << setw(15) << client.PinCode;
		cout << "| " << left << setw(20) << client.GetFullName();
		cout << "| " << left << setw(17) << client.Phone;
		cout << "| " << left << setw(25) << client.Email;
		cout << "| " << left << setw(16) << client.Salary << endl;
	}
public:
	static void ShowAllClients()
	{
		vector<clsClient> clients = clsClient::GetAllClients();
		cout << "Client List (" << clients.size() << ") Client/s" << endl;
		cout << clsUtility::MakeLineOf(120) << endl << endl;
		cout << "| " << left << setw(3) << "I";
		cout << "| " << left << setw(16) << "Account Number";
		cout << "| " << left << setw(15) << "Pin Code";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(17) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(16) << "Balance" << endl;
		cout << clsUtility::MakeLineOf(120) << endl << endl;
		int i = 0;
		for (clsClient& client : clients)
		{
			cout << "| " << left << setw(3) << i + 1;
			_PrintClientInfoInline(client);
			i++;
		}
		cout << clsUtility::MakeLineOf(120) << endl;
	}

};

