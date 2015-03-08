#include "stringutility.h"

// Is the given string a number?
bool IsNumber(std::string str)
{
	return !str.empty() && std::all_of(str.begin(), str.end(), [](char c){return isdigit(c); });
}

// Splits a string along a delimiter
std::vector<std::string> SplitString(std::string toSplit, char delimiter)
{
	std::vector<std::string> toReturn;
	std::string temp = "";
	for (unsigned int i = 0; i < toSplit.length(); i++)
	{
		if (toSplit[i] != delimiter)
		{
			temp += toSplit[i];
		}
		else if (temp.length() > 0)
		{
			toReturn.push_back(temp);
			temp = "";
		}
	}
	if (temp.length() > 0)
		toReturn.push_back(temp);
	return toReturn;
}