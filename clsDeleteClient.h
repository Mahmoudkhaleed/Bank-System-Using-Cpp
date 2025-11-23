#pragma once
#include "clsClient.h"
#include "clsScreen.h"
class clsDeleteClient
{
public:
	static void DeleteClient()
	{
		cout << "Enter An Account Number To Delete: ";
		string AccNumber = clsInputValidate::ReadString();
		while (!clsClient::IsClientExist(AccNumber))
		{
			cout << "The Client Is not Exist!, Enter another account Number: ";
			AccNumber = clsInputValidate::ReadString();
		}

		clsClient client = clsClient::Find(AccNumber);
		cout << endl;
		clsScreen::PrintClient(client);

		string choice;
		cout << "Are you Sure You Want to Delete This User? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			client.Delete();
			clsClient::enSaveResults SaveResult = client.Save();
			switch (SaveResult)
			{
			case clsClient::vsFailedEmptyObj:
				cout << "\nError The account was not saved because it is empty!" << endl;
				break;
			case clsClient::svSucceeded:
				cout << "\nThe Account is Deleted successfuly!" << endl << endl;
				break;
			default:
				break;
			}
		}
	}

};

