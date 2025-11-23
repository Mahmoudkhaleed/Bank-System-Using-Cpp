#pragma once
#include "clsTransferHistory.h"

class clsShowTransferLog
{
private:
	static void _PrintTransferHistoryInfoInline(clsTransferHistory& History)
	{
		cout << "| " << left << setw(20) << History.GetDate();
		cout << "| " << left << setw(10) << History.GetClient1AccountNumber();
		cout << "| " << left << setw(10) << History.GetClient2AccountNumber();
		cout << "| " << left << setw(15) << History.GetAmountOfTransfer();
		cout << "| " << left << setw(15) << History.GetClient1SalaryAfterProcess();
		cout << "| " << left << setw(15) << History.GetClient2SalaryAfterProcess();
		cout << "| " << left << setw(15) << History.GetUserName() << endl;
	}
public:
	static void ShowAllTransferHistory()
	{
		vector<clsTransferHistory> History = clsTransferHistory::GetAllTransfers();
		cout << "Transfer History List (" << History.size() << ")" << endl;
		cout << clsUtility::MakeLineOf(120) << endl << endl;
		cout << "| " << left << setw(4) << "I";
		cout << "| " << left << setw(20) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(15) << "Amount";
		cout << "| " << left << setw(15) << "s.Balance";
		cout << "| " << left << setw(15) << "d.Balance";
		cout << "| " << left << setw(15) << "user" << endl;
		cout << clsUtility::MakeLineOf(120) << endl << endl;
		int i = 0;
		for (clsTransferHistory& History : History)
		{
			cout << "| " << left << setw(4) << i + 1;
			_PrintTransferHistoryInfoInline(History);
			i++;
		}
		cout << clsUtility::MakeLineOf(120) << endl;
	}
};

