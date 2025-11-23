#pragma once
#include "clsScreen.h"
#include "clsUtility.h"
#include "clsInputValidate.h"
#include "clsShowClientsBalances.h"
#include "clsDepositInClient.h"
#include "clsWithdrawFromClient.h"
#include "clsTransferBalance.h"
#include "clsShowTransferLog.h"

class clsTransactionScreen : protected clsScreen
{
	enum enMenuTwoChoices { Deposit = 1, Withdraw = 2, TotalBalance = 3, Transfer = 4, TransferLogs = 5, MainMenu = 6 };

	static void _ReturnBackToTransScreen()
	{
		cout << "\nPress any key to return back to the Transaction menu...." << endl;
		system("pause>0");
	}


	static void _PrintChoices()
	{
		TitleFrame("Transactions Menu Screen", '=');

		cout << "\t[1] Deposit." << endl;
		cout << "\t[2] Withdraw." << endl;
		cout << "\t[3] Total Balance." << endl;
		cout << "\t[4] Transfer." << endl;
		cout << "\t[5] Transfer Logs." << endl;
		cout << "\t[6] Main Menu." << endl;
		cout << clsUtility::MakeLineOf(40, '=') << endl;
	}

	static void _DepositInClientAccount()
	{
		TitleFrame("Deposit screen");
		clsDepositInClient::DepositInClient();
	}
	static void _WithdrawFromClient()
	{
		TitleFrame("Withdraw screen");
		clsWithdrawFromClient::WithdrawFromClient();
	}
	static void _ShowTotalBalances()
	{
		clsShowClientsBalances::ShowTotalBalances();
	}
	static void _TransferFromClientToAnother()
	{
		TitleFrame("Transfer screen", '-');
		clsTransferBalance::TransferFromClientToAnother();
	}
	static void _TransferLogs()
	{
		TitleFrame("Transfer Log screen", '-');
		clsShowTransferLog::ShowAllTransferHistory();
	}

	static void _ConfirmChoice(enMenuTwoChoices choice)
	{
		system("cls");
		switch (choice)
		{
		case Deposit:
			_DepositInClientAccount();
			break;
		case Withdraw:
			_WithdrawFromClient();
			break;
		case TotalBalance:
			_ShowTotalBalances();
			break;
		case Transfer:
			_TransferFromClientToAnother();
			break;
		case TransferLogs:
			_TransferLogs();
			break;
		default:
			return;
			break;
		}
		_ReturnBackToTransScreen();
	}

public:

	static void ShowTransactionMenu()
	{
		enMenuTwoChoices choice;
		do
		{
			system("cls");
			_PrintChoices();
			cout << "Choose what do want to do from 1 to " << MainMenu << "? ";
			choice = (enMenuTwoChoices)clsInputValidate::ReadNumberInRange<int>("The number entered is out of range \n Enter another Number: ", 1, MainMenu);
			_ConfirmChoice(choice);
		} while (choice != enMenuTwoChoices::MainMenu);
	}

};

