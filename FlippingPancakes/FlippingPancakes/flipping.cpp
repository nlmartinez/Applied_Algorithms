#include<fstream>
#include<string>
#include<queue>
#include<iostream>

using std::string;
using std::queue;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::getline;

struct Stack
{
	string config;
	int position;
};

Stack FlipStack (Stack pancakes)
{

}

int main()
{
	ifstream inFile("pancakes.in");
	
	if(inFile)
	{
		ofstream outFile("pancakes.out");
		string initialConfig;
		getline(inFile, initialConfig);
		while(initialConfig == "0")
		{

		}
	}
	else
	{
		cout << "Could not find pancakes.in file." << endl;
	}
}