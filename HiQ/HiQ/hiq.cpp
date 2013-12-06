// 15Pegs.cpp   (Uses Depth-First Search)
/*
	This program finds solutions to the triangle puzzle found at Cracker Barrel restaurants.  The input file
	should specify the location of the initial hole by specifying the hole number according to the arrangement
	shown below:
	        1 2 3
			4 5 6
	    7 8 9 A B C D
	    E F G H I J K
		L M N P Q R S
			T U V
			W X Y
*/
#undef debug true

#define NUMHOLES 33

#include <iostream>
#include <fstream>
#include <bitset>
#include <set>
#include <stack>
#include <iomanip>
#include <map>
using namespace std;

typedef bitset<NUMHOLES+1> ConfigType;
ConfigType SolutionConfig;

short  between[NUMHOLES+1][NUMHOLES+1];
set< long long > MarkedSet;
map<char, int> charToInt;
map<int, char> intToChar;

struct JumpType
{
	short from;
	short to;
};
stack< JumpType > JumpStack;

void Initialize()
{
	//initialize int to char/char to int key/value maps
	int asciiValue = 65;
	for(int i = 1; i < 34; i ++)
	{
		if(asciiValue == 79)
			asciiValue++;
		if(i < 10)
		{	
			char character[1];
			itoa(i,character,10);
			intToChar[i] = character[0];
			charToInt[character[0]] = i;
		}
		else
		{
			intToChar[i] = (char)asciiValue;
			charToInt[(char)asciiValue] = i;
		}
		asciiValue++;
	}
	for (int i=0; i<=NUMHOLES; i++)
		for (int j=0; j<=NUMHOLES; j++)
			 between[i][j] = 0;			// Initialize between[][] array

	// 67 potential jumps determined by triangle board
	between[1][3] = between[3][1] = 2;
	between[1][11] = between[11][1] = 5;
	between[1][9] = between[9][1] = 4;
	between[2][10] = between[10][2] = 5;
	between[2][8] = between[8][2] = 4;
	between[2][12] = between[12][2] = 6;
	between[3][9] = between[9][3] = 5;
	between[3][11] = between[11][3] = 6;
	between[4][16] = between[16][4] = 9;
	between[4][14] = between[14][4] = 8;
	between[4][6] = between[6][4] = 5;
	between[4][18] = between[18][4] = 10;
	between[5][15] = between[15][5] = 9;
	between[5][17] = between[17][5] = 10;
	between[5][19] = between[19][5] = 11;
	between[6][16] = between[16][6] = 10;
	between[6][18] = between[18][6] = 11;
	between[6][20] = between[20][6] = 12;
	between[7][21] = between[21][7] = 14;
	between[7][23] = between[23][7] = 15;
	between[7][9] = between[9][7] = 8;
	between[8][10] = between[10][8] = 9;
	between[8][22] = between[22][8] = 15;
	between[8][24] = between[24][8] = 16;
	between[9][21] = between[21][9] = 15;
	between[9][23] = between[23][9] = 16;
	between[9][25] = between[25][9] = 17;
	between[9][11] = between[11][9] = 10;
	between[10][22] = between[22][10] = 16;
	between[10][24] = between[24][10] = 17;
	between[10][26] = between[26][10] = 18;
	between[10][12] = between[12][10] = 11;
	between[11][13] = between[13][11] = 12;
	between[11][27] = between[27][11] = 19;
	between[11][25] = between[25][11] = 18;
	between[11][23] = between[23][11] = 17;
	between[12][26] = between[26][12] = 19;
	between[12][24] = between[24][12] = 18;
	between[13][27] = between[27][13] = 20;
	between[13][25] = between[25][13] = 19;
	between[14][16] = between[16][14] = 15;
	between[14][28] = between[28][14] = 22;
	between[15][17] = between[17][15] = 16;
	between[15][29] = between[29][15] = 23;
	between[16][18] = between[18][16] = 17;
	between[16][30] = between[30][16] = 24;
	between[16][28] = between[28][16] = 23;
	between[17][29] = between[29][17] = 24;
	between[17][19] = between[19][17] = 18;
	between[18][20] = between[20][18] = 19;
	between[18][30] = between[30][18] = 25;
	between[18][28] = between[28][18] = 24;
	between[19][29] = between[29][19] = 25;
	between[20][30] = between[30][20] = 26;
	between[21][23] = between[23][21] = 22;
	between[22][24] = between[24][22] = 23;
	between[22][32] = between[32][22] = 28;
	between[23][25] = between[25][23] = 24;
	between[23][33] = between[33][23] = 29;
	between[23][31] = between[31][23] = 28;
	between[24][26] = between[26][24] = 25;
	between[24][32] = between[32][24] = 29;
	between[25][27] = between[27][25] = 26;
	between[25][33] = between[33][25] = 30;
	between[26][32] = between[32][26] = 30;
	between[28][30] = between[30][28] = 29;
	between[31][33] = between[33][31] = 32;
}

bool ValidJump(JumpType jump, ConfigType PuzzleConfig)
{
	bool fromPeg = PuzzleConfig.test(jump.from);
	bool toPeg   = PuzzleConfig.test(jump.to);
	bool overPeg = PuzzleConfig.test(between[jump.from][jump.to]);
	return ( fromPeg && overPeg && !toPeg );
}

ConfigType FindNewConfig(JumpType jump, ConfigType OldConfig)
{
	ConfigType NewConfig=OldConfig;

	if ( ValidJump(jump,OldConfig) )
	{
		NewConfig.flip(jump.from);
		NewConfig.flip(jump.to);
		NewConfig.flip(between[jump.from][jump.to]);
	}
	return NewConfig;
}

void Mark(ConfigType PuzzleConfig)
{
	MarkedSet.insert( PuzzleConfig.to_ullong() );
}

bool Marked(ConfigType PuzzleConfig)
{
	return MarkedSet.find( PuzzleConfig.to_ullong() ) != MarkedSet.end();
}

bool FindSolution(ConfigType PuzzleConfig )		// Depth-First Search for solution to puzzle
{
//	if (PuzzleConfig.count() == 1) return true;			// Alternative solution: 1 peg 'anywhere'
	if (PuzzleConfig == SolutionConfig) return true;	// Solution: 1 peg left in initial hole

	bool SolutionFound = false;

	Mark(PuzzleConfig);

	// For all configurations adjacent to current Puzzle Configuration (uses brute-force)
	for (short from=1; !SolutionFound && from<=NUMHOLES; from++)
	{
		for (short to=1; !SolutionFound && to<=NUMHOLES; to++)
		{
			JumpType jump = {from,to};
			if ( ValidJump(jump, PuzzleConfig) )
			{
				ConfigType NewConfig = FindNewConfig(jump, PuzzleConfig);
				if ( !Marked(NewConfig) )
				{
					#ifdef debug
						cout << "(" << setw(2) << jump.from << "," << setw(2) << jump.to 
							 << ")-> " << NewConfig << "  " << NewConfig.count() << endl;
					#endif
					SolutionFound = FindSolution( NewConfig );	// Recursive call for Depth-First Search
					if (SolutionFound)
						JumpStack.push(jump);
					else {
						#ifdef debug
							cout << "Backup -> " << PuzzleConfig << endl;
						#endif
					}
				}
			}
		}
	}

	return SolutionFound;
}

void PrintSolution(ofstream &fout, stack< JumpType > &JumpStack)
{
	while (!JumpStack.empty())
	{
		JumpType jump = JumpStack.top(); JumpStack.pop();
		fout << intToChar[jump.from] << "->" << intToChar[jump.to] << " ";
	}
}

int main ()
{
	ifstream fin ("hiq.in");
	if (fin)
	{
		ofstream fout ("hiq.out");
		Initialize();
		int hole;
		char input;
		ConfigType PuzzleConfig;

		fin >> input;
		hole = charToInt[input];
		while (hole > 0)
		{
			fout << "Hole at #" << hole << ": ";

			MarkedSet.clear();
			// Initialize Puzzle & Solution Configs
			PuzzleConfig.set();     PuzzleConfig.flip(0);       PuzzleConfig.flip(hole);
			SolutionConfig.reset(); SolutionConfig.flip(hole);
			#ifdef debug
				cout << "Initial-> " << PuzzleConfig << endl;
			#endif

			if ( FindSolution(PuzzleConfig) )
			{
				cout << "Solution found for hole at position #" << hole << endl;
				PrintSolution(fout, JumpStack);
				fout << endl;
			}
			else
			{
				cout << "No solution found for hole at position #" << hole << endl;
				fout << "No solution found!" << endl;
			}

			fin >> input;
			hole = charToInt[input];
		}

		fin.close();
		fout.close();
	}
}