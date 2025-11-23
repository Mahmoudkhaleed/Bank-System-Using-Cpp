#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class clsString
{
private:
	string _Value;
	static bool _isVowel(char c)
	{
		switch (tolower(c))
		{
		case 'a':
		case 'u':
		case 'i':
		case 'e':
		case 'o':
			return true;
		default:
			return false;
		}
	}

	static char _invertCase(char c)
	{
		return isupper(c) ? tolower(c) : toupper(c);
	}
public:
	clsString()
	{
		_Value = "";
	}

	clsString(string value)
	{
		_Value = value;
	}

	string getValue()
	{
		return _Value;
	}

	void setValue(string newVal)
	{
		_Value = newVal;
	}

	__declspec(property(get = getValue, put = setValue)) string Value;

	// Return an array of strings
	static vector<string> Split(string str, string delim)
	{
		vector<string> arr;
		string word;
		int pos;

		while ((pos = static_cast<int>(str.find(delim))) != string::npos)
		{
			word = str.substr(0, pos);
			if (!empty(word))
				arr.push_back(word);
			str.erase(0, pos + delim.size());
		}
		if (!empty(str))
			arr.push_back(str);
		return arr;
	}

	vector<string> Split(string delim)
	{
		return Split(_Value, delim);
	}

	// count words in the string
	static short CountWords(string word)
	{
		return static_cast<short>(Split(word, " ").size());
	}

	short CountWords()
	{
		return CountWords(_Value);
	}

	// change the sentence case
	static string ToLowerCase(string str)
	{
		string s;
		for (int i = 0; i < str.size(); i++)
		{
			s += tolower(str.at(i));
		}

		return s;
	}

	string ToLowerCase()
	{
		return ToLowerCase(_Value);
	}

	static string ToUpperCase(string str)
	{
		string s;
		for (int i = 0; i < str.size(); i++)
		{
			s += toupper(str.at(i));
		}

		return s;
	}

	string ToUpperCase()
	{
		return ToUpperCase(_Value);
	}

	static string Capitalize(string str)
	{
		bool fLetter = true;
		for (char& c : str)
		{
			if (c != ' ' && fLetter)
				c = toupper(c);
			fLetter = (c == ' ');
		}

		return str;
	}

	string Capitalize()
	{
		return Capitalize(_Value);
	}

	// remove all punctures
	static string RemoveAllPuncs(string str)
	{
		for (int i = 0; i < str.size(); i++)
		{
			if (ispunct(str[i]))
			{
				str.erase(i, 1);
			}
		}
		return str;
	}

	string RemoveAllPuncs()
	{
		return RemoveAllPuncs(_Value);
	}

	// replace word in the string with another word
	static string ReplaceWord(string str, string wordToReplace, string toWord, bool caseSensitive = false)
	{
		if (caseSensitive)
		{
			str = ToLowerCase(str);
			wordToReplace = ToLowerCase(wordToReplace);
		}

		int pos = static_cast<int>(str.find(wordToReplace));
		while (pos != string::npos)
		{
			str.replace(pos, wordToReplace.size(), toWord);
			pos = static_cast<int>(str.find(wordToReplace));
		}
		return str;
	}

	string ReplaceWord(string wordToReplace, string toWord, bool caseSensitive = false)
	{
		return ReplaceWord(_Value, wordToReplace, toWord, caseSensitive);
	}


	// reverse the sentence direction
	static string ReverseWords(string str)
	{
		vector<string> arr = Split(str, " ");
		string st;
		for (string& s : arr)
		{
			st = s + " " + st;
		}
		return st;
	}

	string ReverseWords()
	{
		return ReverseWords(_Value);
	}


	// Trim extra spaces and symbols
	static string TrimRight(string str)
	{
		for (int i = 0; i < str.size(); i++)
		{
			if (str.at(i) != ' ')
			{
				str.erase(0, i);
				break;
			}
		}
		return str;
	}

	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string TrimLeft(string str)
	{
		for (int i = static_cast<int>(str.size()) - 1; i >= 0; i--)
		{
			if (str.at(i) != ' ')
			{
				str.erase(i + 1);
				break;
			}
		}
		return str;
	}

	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string Trim(string str)
	{
		return TrimLeft(TrimRight(str));
	}

	string Trim()
	{
		return Trim(_Value);
	}

	// count vawols
	static int CountVowels(string str)
	{
		int count = 0;
		for (char c : str)
		{
			if (_isVowel(c))
				count++;
		}
		return count;
	}
	int CountVowels()
	{
		return CountVowels(_Value);
	}

	// Case invert

	static string InvertCase(string str)
	{
		string sentence;
		for (char c : str)
		{
			sentence += _invertCase(c);
		}
		return sentence;
	}

	string InvertCase()
	{
		return InvertCase(_Value);
	}


};

