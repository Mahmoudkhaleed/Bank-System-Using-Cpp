#pragma once
#include "clsClient.h"
#include "clsScreen.h"
class clsAddNewClient
{
public:
	static void AddNewClient()
	{
		cout << "Enter An Account Number: ";
		string AccNumber = clsInputValidate::ReadString();
		while (clsClient::IsClientExist(AccNumber))
		{
			cout << "The Client Is already Exist!, Enter another account Number: ";
			AccNumber = clsInputValidate::ReadString();
		}
		clsClient NewClient = clsClient::SetNewClient(AccNumber);

		clsScreen::ReadClientInfo(NewClient, "");

		string choice;
		cout << "Are you Sure You Want to Add This Client? y/n: ";
		cin >> choice;
		if (choice == "y" || choice == "Y")
		{
			clsClient::enSaveResults SaveResult = NewClient.Save();
			switch (SaveResult)
			{
			case clsClient::vsFailedEmptyObj:
				cout << "\nError The account was not saved because it is empty!" << endl;
				break;
			case clsClient::svSucceeded:
				cout << "\nThe Account is Added successfuly!" << endl << endl;
				clsScreen::PrintClient(NewClient);
				break;
			default:
				break;
			}
		}

	}
};

