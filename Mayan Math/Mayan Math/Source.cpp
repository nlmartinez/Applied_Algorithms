#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<xtgmath.h>

using std::cout;
using std::string;
using std::stack;
using std::ifstream;
using std:: ofstream;

int convertToDigit(stack<string>& glyph){
	string line;
	int glyphNumber = 0;	
	int result = 0;

	while(!glyph.empty()){
		int number = 0;
		line = glyph.top();
		glyph.pop();

		while(line != "$"){
			if(line == "-----")
				number += 5;
			else if(line == "*")
				number++;
			else if(line == "**")
				number += 2;
			else if (line == "***")
				number += 3;
			else if (line == "****")
				number += 4;
			
			line = glyph.top();
			glyph.pop();
		}

		result += number * std::pow(20, glyphNumber);
		glyphNumber++;
	}
	return result;
}
stack<string> convertToGlyph(int digit){
	stack<int> baseTwenty;
	stack<string> result;
	for(int i = 0; digit > 0; i++){
		baseTwenty.push(digit % 20);
		digit = digit/20;
	}

	while(!baseTwenty.empty()){
		string line;
		int digit = baseTwenty.top();
		baseTwenty.pop();

		for(int i = digit/5; i > 0; i--){
			result.push("-----");
		}
		for(int i = digit % 5; i > 0; i--){
			line += "*";
		}
		result.push(line);
		result.push("");

	}



	return result;
}

int main(){
	stack<string> firstGlyph;
	stack<string> secondGlyph;
	string lineReader;
	char op;
	int firstNumber;
	int secondNumber;

	ifstream inFile("mayan.in");

	if (inFile){
		ofstream outFile ("mayan.out");

		getline (inFile, lineReader);
		while(lineReader != "0"){
			while(lineReader != "#"){
				if(lineReader == "")
					firstGlyph.push("$");
				else{
					firstGlyph.push(lineReader);
				}
				getline (inFile, lineReader);
			}
			
			inFile >> op;
			getline(inFile, lineReader);
			
			while(lineReader != "#"){
			if(lineReader == "")
					secondGlyph.push("$");
				else{
					secondGlyph.push(lineReader);
				}
				getline (inFile, lineReader);
			}

			firstNumber = convertToDigit(firstGlyph);
			secondNumber = convertToDigit(secondGlyph);

			int result;
			if(op == '+')
				result = firstNumber + secondNumber;
			else
				result = firstNumber - secondNumber;
			stack<string>resultGlyph;

			resultGlyph = convertToGlyph(result);

			while(!resultGlyph.empty()){
				outFile << resultGlyph.top() << std::endl;
			}

			getline (inFile, lineReader);
		}

		

		outFile.close();
	}
	else
		cout << "File not found\n";

	inFile.close();
}