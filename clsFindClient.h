#pragma once
#include "clsClient.h"
class clsFindClient
{
public:
	static void FindClient()
	{
		cout << "Enter An Account Number: ";
		string AccNumber = clsInputValidate::ReadString();
		while (!clsClient::IsClientExist(AccNumber))
		{
			cout << "The Client is not exist, Enter another Account Number: ";
			AccNumber = clsInputValidate::ReadString();
		}

		clsClient client = clsClient::Find(AccNumber);
		cout << endl;
		clsScreen::PrintClient(client);
	}
};

