#include<fstream>
#include<vector>
#include<string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::getline;


struct Slot
{
	bool isFilled;
	string color;
};

struct Column
{
	vector<Slot> slots;
	int numberOfPieces;
};

vector<Column> createGameBoard(int rows, int columns)
{
	vector<Column> board;
	Column newColumn;
	newColumn.numberOfPieces = 0;
	Slot emptySlot;
	emptySlot.isFilled = false;
	for(int j = 0; j < rows; j++)
		newColumn.slots.push_back(emptySlot);
	
	for(int i = 0; i < columns; i++)
		board.push_back(newColumn);
		
	return board;
}

bool checkGame(string &gameState, vector<Column>board)
{
	int columnCount = board.size();
	int rowCount = board[0].slots.size();

	for(int i = 0; i < columnCount; i++){
		if(board[i].slots[0].isFilled)
			for(int j = 0; j < rowCount; j++)
		{
			if(board[i].slots[j].isFilled)
			{
				//check up
				if(j < rowCount - 3)
				{					
					if((board[i].slots[j+1].isFilled && board[i].slots[j].color == board[i].slots[j+1].color) 
						&& (board[i].slots[j+2].isFilled && board[i].slots[j].color == board[i].slots[j+2].color) 
						&&(board[i].slots[j+3].isFilled && board[i].slots[j].color == board[i].slots[j+3].color))
					{
						gameState = board[i].slots[j].color + " won";
						return true;
					}
				}
				
				//check horizontal
				if(i < columnCount - 3)
				{
					if((board[i+1].slots[j].isFilled && board[i].slots[j].color == board[i+1].slots[j].color) 
						&& (board[i+2].slots[j].isFilled && board[i].slots[j].color == board[i+2].slots[j].color) 
						&&(board[i+3].slots[j].isFilled && board[i].slots[j].color == board[i+3].slots[j].color))
					{
						gameState = board[i].slots[j].color + " won";
						return true;
					}
				}

				//check diagonally up forward
				if(j < rowCount - 3 && i < columnCount - 3)
				{
					if((board[i+1].slots[j+1].isFilled && board[i].slots[j].color == board[i+1].slots[j+1].color) 
						&& (board[i+2].slots[j+2].isFilled && board[i].slots[j].color == board[i+2].slots[j+2].color) 
						&&(board[i+3].slots[j+3].isFilled && board[i].slots[j].color == board[i+3].slots[j+3].color))
					{
						gameState = board[i].slots[j].color + " won";
						return true;
					}
				}

				//check diagonally up backward
				if(j < rowCount - 3 && i - 2 > 0)
				{
					if((board[i-1].slots[j+1].isFilled && board[i].slots[j].color == board[i-1].slots[j+1].color) 
						&& (board[i-2].slots[j+2].isFilled && board[i].slots[j].color == board[i-2].slots[j+2].color) 
						&&(board[i-3].slots[j+3].isFilled && board[i].slots[j].color == board[i-3].slots[j+3].color))
					{
						gameState = board[i].slots[j].color + " won";
						return true;
					}
				}

				//check diagonally down and forward
				if(j < rowCount - 3 && i < columnCount - 3)
				{
					if((board[i+1].slots[j-1].isFilled && board[i].slots[j].color == board[i+1].slots[j-1].color) 
						&& (board[i+2].slots[j-2].isFilled && board[i].slots[j].color == board[i+2].slots[j-2].color) 
						&&(board[i+3].slots[j-3].isFilled && board[i].slots[j].color == board[i+3].slots[j-3].color))
					{
						gameState = board[i].slots[j].color + " won";
						return true;
					}
				}

				//check diagonally down and backward
				if(j - 2 > 0 && i < columnCount - 3)
				{
					if((board[i-1].slots[j-1].isFilled && board[i].slots[j].color == board[i-1].slots[j-1].color) 
						&& (board[i-2].slots[j-2].isFilled && board[i].slots[j].color == board[i-2].slots[j-2].color) 
						&& (board[i-3].slots[j-3].isFilled && board[i].slots[j].color == board[i-3].slots[j-3].color))							
					{
						gameState = board[i].slots[j].color + " won";
						return true;
					}
				}
			}
			
		}
	}
		

		return false;
}

int main()
{
	ifstream inFile("connect.in");
	ofstream outFile("connect.out");
	int rowCount;
	int columnCount;
	int gameCount;
	string moveString;

	inFile >> gameCount;

	for(int i = 0; i < gameCount; i++)
	{
		
		inFile >> rowCount;
		inFile >> columnCount;
		getline(inFile, moveString);
		moveString = moveString.substr(1, moveString.length()-1);
		vector<Column> board = createGameBoard(rowCount, columnCount);
		string gameState = "unfinished";
		bool gameOver = false;

		for(int j = 0; j < moveString.length(); j++)
		{
			char movechar[1];
			movechar[0] = moveString[j];
			int move = atoi(movechar);
			board[move].slots[board[j].numberOfPieces].isFilled = true;

			if(j % 2 == 0)
				board[move].slots[board[j].numberOfPieces].color = "red";
			else
				board[move].slots[board[j].numberOfPieces].color = "Yellow";

			//Checking for winner
			if(j > 2)
			{
				gameOver = checkGame(gameState, board);
			}

			if(gameOver)
			{
				outFile << gameState << std::endl;
			}
		}

		if (!gameOver && moveString.length() == (rowCount*columnCount))
		{
			gameState = "tied";
			outFile << gameState << std::endl;
		}
		else
		{
			outFile << gameState << std::endl;
		}

		
	}
	


	inFile.close();
	outFile.close();
}

