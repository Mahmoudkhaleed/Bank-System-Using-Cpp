#pragma once
#include <fstream>
#include "clsString.h"

class clsCurrency
{
private:
	enum enMode {
		EmptyMode = 0,
		UpdateMode = 1,
	};

	// propreties
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	// Methods
	static string _ConvertObjToStrLine(clsCurrency currency, string delim = "#//#")
	{
		string str;
		str += currency._Country + delim;
		str += currency._CurrencyCode + delim;
		str += currency._CurrencyName + delim;
		str += to_string(currency._Rate);
		return str;
	}
	static clsCurrency _ConvertStrLineToObj(string line, string delim = "#//#")
	{
		vector<string> currencyObj = clsString::Split(line, delim);
		return clsCurrency(clsCurrency::UpdateMode, currencyObj[0], currencyObj[1], currencyObj[2], stod(currencyObj[3]));
	}
	static clsCurrency _EmptyCurrencyObj()
	{
		return clsCurrency(EmptyMode, "", "", "", 0);
	}
	static vector<clsCurrency> _LoadCurrenciesDataFormFile()
	{
		vector<clsCurrency> currencies;
		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);
		if (CurrenciesFile.is_open())
		{
			string line;
			while (getline(CurrenciesFile, line))
			{
				currencies.push_back(_ConvertStrLineToObj(line));
			}
			CurrenciesFile.close();
		}
		return currencies;
	}
	static void _SaveCurrenciesDataToFile(vector<clsCurrency> currencies)
	{
		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::out);
		if (CurrenciesFile.is_open())
		{
			for (clsCurrency currency : currencies)
			{
				CurrenciesFile << _ConvertObjToStrLine(currency) << endl;
			}
			CurrenciesFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> currencies = _LoadCurrenciesDataFormFile();
		for (clsCurrency& currency : currencies)
		{
			if (currency._Country == _Country || currency._CurrencyCode == _CurrencyCode)
			{
				currency = *this;
				break;
			}
		}
		_SaveCurrenciesDataToFile(currencies);
	}

public:
	clsCurrency(enMode Mode,
		string Country,
		string CurrencyCode,
		string CurrencyName,
		double Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string GetCountry()
	{
		return _Country;
	}
	void SetCountry(string Country)
	{
		_Country = Country;
	}
	__declspec(property(get = GetCountry, put = SetCountry)) string Country;

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}
	void SetCurrencyCode(string CurrencyCode)
	{
		_CurrencyCode = CurrencyCode;
	}
	__declspec(property(get = GetCurrencyCode, put = SetCurrencyCode)) string CurrencyCode;

	string GetCurrencyName()
	{
		return _CurrencyName;
	}
	void SetCurrencyName(string CurrencyName)
	{
		_CurrencyName = CurrencyName;
	}
	__declspec(property(get = GetCurrencyName, put = SetCurrencyName)) string CurrencyName;

	double GetRate()
	{
		return _Rate;
	}
	void SetRate(double Rate)
	{
		_Rate = Rate;
	}
	__declspec(property(get = GetRate, put = SetRate)) double Rate;

	static clsCurrency Find(string SearchKey)
	{
		vector<clsCurrency> currencies;
		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);

		if (CurrenciesFile.is_open())
		{
			string line;
			while (getline(CurrenciesFile, line))
			{
				clsCurrency currency = _ConvertStrLineToObj(line);
				if (clsString::ToLowerCase(currency.GetCountry()) == clsString::ToLowerCase(SearchKey) || 
					clsString::ToLowerCase(currency.GetCurrencyCode()) == clsString::ToLowerCase(SearchKey))
				{
					CurrenciesFile.close();
					return currency;
				}
			}
		}
		return _EmptyCurrencyObj();
	}

	static bool IsCurrencyExist(string SearchKey)
	{
		clsCurrency currency = clsCurrency::Find(SearchKey);
		return currency._Mode != clsCurrency::EmptyMode;
	}

	static vector<clsCurrency> GetAllCurrencies()
	{
		return _LoadCurrenciesDataFormFile();
	}

	enum enSaveResults { vsFailedEmptyObj = 0, svSucceeded = 1 };
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case EmptyMode:

			return vsFailedEmptyObj;

		case UpdateMode:
			_Update();
			return svSucceeded;
		default:
			return vsFailedEmptyObj;
			break;
		}

	}
};

