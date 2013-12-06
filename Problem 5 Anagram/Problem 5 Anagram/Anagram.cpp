/****************************************************************************************
Progam: Problem 5: Anagram
Des:	Determines whether two lines read from the input file are anagrams or not and
		writes the result to the output file.
Author: Nathan Martinez
****************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

int main()
{
	string inputFileName;
	ifstream inFile;
	ofstream outFile;

	cout << "Please type in the name of the input file: ";
	cin >> inputFileName;

	inFile.open(inputFileName);
	outFile.open("anagrams.out");

	while(!inFile.eof())
	{
		string firstLine;
		string secondLine;
		int lettersOfFirstLine[26] = {0};
		int lettersOfSecondLine[26] = {0};
		int charValue;

		std::getline (inFile, firstLine);
		if(firstLine.compare("<end>") == 0)
		{
				exit(1);
		}
		std::getline (inFile, secondLine);

		std::transform(firstLine.begin(), firstLine.end(), firstLine.begin(), ::tolower);
		std::transform(secondLine.begin(), secondLine.end(), secondLine.begin(), ::tolower);

		for(int i = 0; i < firstLine.length(); i++)
		{
			charValue = firstLine.at(i);
			charValue -= 97;
		
			if((charValue >= 0) &&(charValue <= 25))
			{
				lettersOfFirstLine[charValue]++;
			}
				
		}

		for(int i = 0; i < secondLine.length(); i++)
		{
			charValue = secondLine.at(i);
			charValue -= 97;

			if((charValue >= 0) && (charValue <= 25))
			{
				lettersOfSecondLine[charValue]++;
			}
		}

		bool isEqual = true;
		for(int i = 0; i < 26; i++)
		{
			if(lettersOfFirstLine[i] != lettersOfSecondLine[i])
			{
				isEqual = false;
			}			
		}

		if(isEqual)
		{
			outFile << "YES\n";
		}
		else
		{
			outFile << "NO\n";
		}
	}

	inFile.close();
	outFile.close();
}	
