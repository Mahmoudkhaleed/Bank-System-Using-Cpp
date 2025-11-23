#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "clsDate.h"

using namespace std;

class clsUtility
{
private:
	static int _GetSecondNumber(int number)
	{
		return number % 10;
	}
	static int _GetFirstNumbers(int number) // 10,000
	{
		string strNumber = to_string(number);
		if (strNumber.length() == 16 ||
			strNumber.length() == 13 ||
			strNumber.length() == 10 ||
			strNumber.length() == 7 ||
			strNumber.length() == 3 ||
			strNumber.length() == 4)
			return stoi(strNumber.substr(0, 1)); // 1,000,000,000
		else if (strNumber.length() == 15 ||
			strNumber.length() == 12 ||
			strNumber.length() == 6 ||
			strNumber.length() == 9)
			return stoi(strNumber.substr(0, 3));
		else if (strNumber.length() == 14 ||
			strNumber.length() == 5 ||
			strNumber.length() == 11 ||
			strNumber.length() == 8)
			return stoi(strNumber.substr(0, 2));
		else
			return stoi(strNumber.substr(0));
	}
	static int _GetNumsAfterFirst(int number)
	{
		string strNumber = to_string(number); // 55,002
		if (strNumber.length() == 13 ||
			strNumber.length() == 10 ||
			strNumber.length() == 7 ||
			strNumber.length() == 3 ||
			strNumber.length() == 4)
			return stoi(strNumber.substr(1));
		else if (strNumber.length() == 15 ||
			strNumber.length() == 12 ||
			strNumber.length() == 6 ||
			strNumber.length() == 9)
			return stoi(strNumber.substr(3));
		else if (strNumber.length() == 14 ||
			strNumber.length() == 5 ||
			strNumber.length() == 11 ||
			strNumber.length() == 8)
			return stoi(strNumber.substr(2));
		else
			return stoi(strNumber.substr(0));
	}
	static string _MakeNums(int number, vector<string> singleNums, string tag) // 100
	{
		int index = _GetFirstNumbers(number); // 55
		string str = ConvertNumberToText(index);
		if (to_string(number).length() > 2 && to_string(number).length() < 4)
		{
			str += " " + tag;
			str += _GetNumsAfterFirst(number) > 0 ? " and " + ConvertNumberToText(_GetNumsAfterFirst(number)) : "";
		}
		else
		{
			str += " " + tag;
			if (_GetNumsAfterFirst(number) > 0 && _GetNumsAfterFirst(number) < 4)
			{
				str += " and " + ConvertNumberToText(_GetNumsAfterFirst(number));
			}
			else
			{
				str += _GetNumsAfterFirst(number) > 0 ? " " + ConvertNumberToText(_GetNumsAfterFirst(number)) : "";
			}
		}
		return str;
	}


public:
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}
	static int GenerateRandomNum(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}
	enum enChar
	{
		smallLitter = 1,
		capitalLitter = 2,
		digit = 3,
		MixedLetter = 4
	};
	static char GetRandomChar(enChar type)
	{
		if (type == enChar::capitalLitter)
		{
			return char(GenerateRandomNum('A', 'Z'));
		}
		else if (type == enChar::smallLitter)
		{
			return char(GenerateRandomNum('a', 'z'));
		}
		else if (type == enChar::digit)
		{
			return char(GenerateRandomNum(48, 57));
		}
		else
		{
			int randNum = GenerateRandomNum(1, 3);
			return GetRandomChar((enChar)randNum);
		}
	}
	static string GenerateWord(enChar type, int length)
	{
		string word;
		for (int i = 0; i < length; i++)
		{
			word += GetRandomChar(type);
		}
		return word;
	}
	static string GenerateKey(enChar type)
	{
		string wordKey;
		for (int j = 0; j < 4; j++)
		{
			wordKey += GenerateWord(type, 4);
			if (j != 3)
				wordKey += "-";
		}
		return wordKey;
	}
	static void PrintKeys(int number, enChar type)
	{
		for (int i = 1; i <= number; i++)
		{
			cout << "key [" << i << "] " << GenerateKey(type) << endl;
		}
	}

	static void Swap(int& X1, int& X2)
	{
		int temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(double& X1, double& X2)
	{
		double temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(float& X1, float& X2)
	{
		float temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(string& X1, string& X2)
	{
		string temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(vector<string>& X1, vector<string>& X2)
	{
		vector<string> temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(vector<int>& X1, vector<int>& X2)
	{
		vector<int> temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(vector<double>& X1, vector<double>& X2)
	{
		vector<double> temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(vector<float>& X1, vector<float>& X2)
	{
		vector<float> temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(vector<clsDate>& X1, vector<clsDate>& X2)
	{
		vector<clsDate> temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(vector<clsString>& X1, vector<clsString>& X2)
	{
		vector<clsString> temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(clsDate& X1, clsDate& X2)
	{
		clsDate temp = X1;
		X1 = X2;
		X2 = temp;
	}
	static void Swap(clsString& X1, clsString& X2)
	{
		clsString temp = X1;
		X1 = X2;
		X2 = temp;
	}

	static int GetMax(int arr[], int length)
	{
		int max = arr[0];
		for (int i = 0; i < length; i++)
		{
			if (max < arr[i])
			{
				max = arr[i];
			}
		}
		return max;
	}
	static int GetMax(vector<int>& arr)
	{
		int max = arr[0];
		for (int i = 0; i < arr.size(); i++)
		{
			if (max < arr[i])
			{
				max = arr[i];
			}
		}
		return max;
	}

	static int GetMin(int arr[], int length)
	{
		int min = arr[0];
		for (int i = 0; i < length; i++)
		{
			if (min > arr[i])
			{
				min = arr[i];
			}
		}
		return min;
	}
	static int GetMin(vector<int>& arr)
	{
		int min = arr[0];
		for (int i = 0; i < arr.size(); i++)
		{
			if (min > arr[i])
			{
				min = arr[i];
			}
		}
		return min;
	}


	static void FillArrayWithRandomNums(int arr[], int length, int from = 1, int to = 10)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = GenerateRandomNum(from, to);
		}
	}
	static void FillArrayWithRandomNums(vector<int>& arr, int from = 1, int to = 10)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			arr[i] = GenerateRandomNum(from, to);
		}
	}

	static int SumOfNumsInArr(int arr[], int length)
	{
		int sum = 0;
		for (int i = 0; i < length; i++)
		{
			sum += arr[i];
		}
		return sum;
	}
	static int SumOfNumsInArr(vector<int> arr)
	{
		int sum = 0;
		for (int i = 0; i < arr.size(); i++)
		{
			sum += arr[i];
		}
		return sum;
	}
	static double SumOfNumsInArr(double arr[], int length)
	{
		double sum = 0;
		for (int i = 0; i < length; i++)
		{
			sum += arr[i];
		}
		return sum;
	}
	static double SumOfNumsInArr(vector<double> arr)
	{
		double sum = 0;
		for (int i = 0; i < arr.size(); i++)
		{
			sum += arr[i];
		}
		return sum;
	}

	static int GetAvarage(int arr[], int length)
	{
		return SumOfNumsInArr(arr, length) / length;
	}
	static double GetAvarage(double arr[], int length)
	{
		return SumOfNumsInArr(arr, length) / double(length);
	}

	static int GetAvarage(vector<int> arr)
	{
		return SumOfNumsInArr(arr) / static_cast<int>(arr.size());
	}
	static double GetAvarage(vector<double> arr)
	{
		return SumOfNumsInArr(arr) / double(arr.size());
	}

	static bool IsPrime(int number)
	{
		for (int i = 2; i < number / 2; i++)
		{
			if (number % i == 0 && number != i)
			{
				return false;
			}
		}
		return true;
	}

	static void ShuffleArr(int arr[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}
	static void ShuffleArr(vector<int>& arr)
	{
		int length = static_cast<int>(arr.size());
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}

	static void ShuffleArr(string arr[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}
	static void ShuffleArr(vector<string>& arr)
	{
		int length = static_cast<int>(arr.size());
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}

	static void ShuffleArr(clsString arr[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}
	static void ShuffleArr(vector<clsString>& arr)
	{
		int length = static_cast<int>(arr.size());
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}


	static void ShuffleArr(double arr[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}
	static void ShuffleArr(vector<double>& arr)
	{
		int length = static_cast<int>(arr.size());
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GenerateRandomNum(0, length - 1)], arr[GenerateRandomNum(0, length - 1)]);
		}
	}

	static string Tab(int length)
	{
		string str;
		for (int i = 0; i < length; i++)
			str += "\t";
		return str;
	}

	static bool IsPalindromeArr(int arr[], int length)
	{
		for (int i = 0; i < length; i++)
			if (arr[i] != arr[length - 1 - i])
				return false;
		return true;
	}
	static bool IsPalindromeArr(vector<int> arr)
	{
		int length = static_cast<int>(arr.size());
		for (int i = 0; i < length; i++)
			if (arr[i] != arr[length - 1 - i])
				return false;
		return true;
	}

	static string EncryptText(string text, int key)
	{
		for (char& c : text)
		{
			c = char(c + key);
		}
		return text;
	}
	static string DecryptText(string text, int key)
	{
		for (char& c : text)
		{
			c = char(c - key);
		}
		return text;
	}

	static string MakeLineOf(int number, char symbol = '_')
	{
		string str;
		for (int i = 0; i < number; i++)
			str += symbol;
		return str;
	}

	static string ConvertNumberToText(int number)
	{
		vector<string> singleNums{ "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve" };

		vector<string> lantenNums{ "Twen", "Thir", "Four", "Fif", "Six", "Seven", "Eigh", "Nine" };

		if (number >= 0 && number < 13)
		{
			return singleNums[number];
		}
		else if (number >= 13 && number <= 19)
		{
			return lantenNums[number - 12] + "teen";
		}
		else if (size(to_string(number)) == 2 && number % 10 == 0)
		{
			return lantenNums[number / 10 - 2] + "ty";
		}
		else if (size(to_string(number)) == 2 && number % 10 != 0)
		{
			return lantenNums[(number / 10 - 2)] + "ty-" + singleNums[_GetSecondNumber(number)];
		}
		else if (size(to_string(number)) == 3)
		{
			return _MakeNums(number, singleNums, "Hundred");
		}
		else if (size(to_string(number)) > 3 && size(to_string(number)) < 7)
		{
			return _MakeNums(number, singleNums, "Thousand,");
		}
		else if (size(to_string(number)) >= 7 && size(to_string(number)) < 10)
		{
			return _MakeNums(number, singleNums, "Million,");
		}
		else if (size(to_string(number)) >= 10 && size(to_string(number)) < 13)
		{
			return _MakeNums(number, singleNums, "Billion,");
		}
		else if (size(to_string(number)) >= 13 && size(to_string(number)) < 16)
		{
			return _MakeNums(number, singleNums, "Trillion,");
		}
		return "";
	}
};

