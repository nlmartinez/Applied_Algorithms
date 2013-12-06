/**************************************************************************************************
Program:The Penny Game
Author: Nathan Martinez
**************************************************************************************************/

#include<iostream>
#include<fstream>
#include<string>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;


int main(){
	int numberOfCases;
	string input;
	string combination;
	ifstream inFile;
	ofstream outFile;
	

	inFile.open("penny.in");
	if(inFile){
		outFile.open("penny.out");

		inFile >> numberOfCases;
		while(numberOfCases > 0){
			int combinationCount[8] = {0};
			std::getline (inFile, input);

			combination = input.substr(0,3);

			int inputCount = 1;
			for(int i = 0; i < 37; i++){
				int newCount = 0;

				if(combination == "TTT"){
					newCount = combinationCount[0]++;
					combination[0] = newCount;
				}
				else if(combination == "TTH"){
					newCount = combinationCount[1]++;
					combination[1] = newCount;
				}
				else if(combination == "THT"){
					newCount = combinationCount[2]++;
					combination[2] = newCount;
				}
				else if(combination == "THH"){
					newCount = combinationCount[3]++;
					combination[3] = newCount;
				}
				else if(combination == "HTT"){
					newCount = combinationCount[4]++;
					combination[4] = newCount;
				}
				else if(combination == "HTH"){
					newCount = combinationCount[5]++;
					combination[5] = newCount;
				}
				else if(combination == "HHT"){
					newCount = combinationCount[6]++;
					combination[6] = newCount;
				}
				else if(combination == "HHH"){
					newCount = combinationCount[7]++;
					combination[7] = newCount;
				}

				combination = input.substr(inputCount, 3);
				inputCount++;
			}
			for(int i = 0; i < 8; i++){
				outFile << combination[i] << " ";
			}
			outFile << "\n";
			numberOfCases--;
		}

		inFile.close();
		outFile.close();
	}
	else{
		cout << "File not found.\n";
	}
	return 0;
}