#pragma once
#include "clsClient.h"
class clsUpdateClient
{
public:
	static void UpdateClient()
	{
		cout << "Enter An Account Number To Update: ";
		string AccNumber = clsInputValidate::ReadString();
		while (!clsClient::IsClientExist(AccNumber))
		{
			cout << "The Client is not exist, Enter another Account Number: ";
			AccNumber = clsInputValidate::ReadString();
		}

		clsClient client = clsClient::Find(AccNumber);
		cout << endl;
		clsScreen::PrintClient(client);

		string choice;
		cout << "Are you Sure You Want to Update? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			clsScreen::ReadClientInfo(client, "");
			clsClient::enSaveResults SaveResult = client.Save();
			switch (SaveResult)
			{
			case clsClient::vsFailedEmptyObj:
				cout << "\nError The account was not saved because it is empty!" << endl;
				break;
			case clsClient::svSucceeded:
				cout << "\nThe Account is updated successfuly!" << endl << endl;
				clsScreen::PrintClient(client);
				break;
			default:
				break;
			}
		}

	}

};

