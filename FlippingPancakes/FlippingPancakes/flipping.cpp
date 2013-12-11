#include<fstream>
#include<string>
#include<queue>
#include<set>
#include<iostream>
#include<algorithm>
#include<cctype>

using std::string;
using std::queue;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::getline;
using std::set;

struct Stack
{
	string config;
	int flip;
};
queue<Stack> currentOptions;
set<string> usedCombinations;
set<string>::iterator it;

string orderPancakes(string config)
{
	int stackSize = config.length();

	switch (stackSize)
	{
	case 1:
		return config;
	case 2: 
		if(config.at(0) < config.at(1)){
			return config;
		}
		else
		{
			string temp = config.substr(1);
			temp += config.substr(0,1);
			return temp;
		}
	default:		
			string idealConfig;
			
			while(config.length() > 0)
			{
				string temp = config.substr(0,1);
				int position = 0;
				for(int i = 0; i < config.length(); i ++)
				{
					if(temp > config.substr(i,1))
					{
						temp = config.substr(i,1);
						position = i;
					}
				}
				
				idealConfig += temp;
				if(position == 0)
					config = config.substr(1);
				else if(position == config.length() - 1)
					config = config.substr(0, config.length() - 1);					
				else
				{
					config = config.substr(0, position) + config.substr(position + 1);
				}
			}

			return idealConfig;
	}
}

string findIdealConfig(string initialConfig)
{
	string result = initialConfig;
	
	std::transform(result.begin(), result.end(), result.begin(), toupper);
	result = orderPancakes(result);

	return result;
}

//Make a flip utility function
string ChangeCase(string temp)
{
	for(int i = 0; i < temp.length(); i++)
	{
		if(std::isupper(temp.at(i)))
			temp.at(i) = std::tolower(temp.at(i));
		else
			temp.at(i) = std::toupper(temp.at(i));
	}

	return temp;
}

void Flip(Stack initialConfig)
{
	int currentFlip = initialConfig.flip + 1;
	Stack pancakes;

	for(int i = 0; i < initialConfig.config.length(); i++)
	{
		string temp = initialConfig.config.substr(i);
		string newConfig = initialConfig.config.substr(0,i);

		temp = string (temp.rbegin(), temp.rend());
		temp = ChangeCase(temp);

		newConfig.append(temp);

		if(usedCombinations.find(newConfig) == usedCombinations.end())
		{
			usedCombinations.insert(newConfig);
			pancakes.config = newConfig;
			pancakes.flip = currentFlip;
			currentOptions.push(pancakes);
		}
	}
}



int main()
{
	ifstream inFile("pancakes.in");
	
	if(inFile)
	{
		ofstream outFile("pancakes.out");
		Stack pancakes;
		getline(inFile, pancakes.config);
		pancakes.flip = 0;
		while(pancakes.config != "0")
		{
			usedCombinations.insert(pancakes.config);
			currentOptions.push(pancakes);
			string idealConfig = findIdealConfig(pancakes.config);
			
			while(!currentOptions.empty())
			{
				Stack nextStack = currentOptions.front(); currentOptions.pop();

				if(nextStack.config.compare(idealConfig) == 0)
				{
					outFile << nextStack.flip << endl;
					while(!currentOptions.empty())
						currentOptions.pop();
					usedCombinations.clear();
				}
				else
				{
					Flip(nextStack);
				}

			}
			getline(inFile, pancakes.config);
			pancakes.flip = 0;
		}
		
		outFile.close();
	}
	else
	{
		cout << "Could not find pancakes.in file." << endl;
	}
	
	inFile.close();
}