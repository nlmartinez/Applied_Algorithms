#include<fstream>
#include<iostream>
#include<string>
#include<queue>
#include<math.h>

using std::ifstream;
using std::ofstream;
using std::string;
using std::queue;
using std::endl;
using std::sqrtf;

#define PI 3.14159265

int main()
{		
	ifstream inFile;
	ofstream outFile;

	inFile.open("firefly.in");

	if(inFile)
	{
		int numFirefly;	
		float catcher_x, catcher_y;
		
		
		int maxJump;
		numFirefly = 1;
		outFile.open("firefly.out");
		inFile >> maxJump >> catcher_x >>  catcher_y;
		while(maxJump != 0)
		{
			queue<int> rightMoves;
			queue<int> leftMoves;
			int firefly_x, firefly_y;
			
			inFile >> firefly_x >> firefly_y;
			//Check for end of chase
			while(firefly_x != -1)
			{
				rightMoves.push(firefly_x);
				leftMoves.push(firefly_y);

				inFile >> firefly_x >> firefly_y;
			}

			bool isCaught = false;
			while(!isCaught && !rightMoves.empty())
			{
				//prep firefly's next move
				firefly_x = rightMoves.front();
				rightMoves.pop();

				firefly_y = leftMoves.front();
				leftMoves.pop();
				
				double diffX = catcher_x - firefly_x;
				if(diffX < 0)
					diffX *= -1;
				
				double diffY = catcher_y - firefly_y;
				if(diffY < 0)
					diffY *= -1;
			
				//calculate new distance between catcher and firefly
				double distance = sqrtf(diffX*diffX + diffY*diffY);
				//find angle of trajectory
				double angleOfTrajectory = atan(diffX/diffY)*180 / PI;
				//check to see if firefly is caught
				if(distance - maxJump <= 1)
					isCaught = true;
				else 
				{
					//make a jump
					distance -= maxJump;
					//adjust catcher coordinates
					if(catcher_x < firefly_x)
						catcher_x = firefly_x - (distance*sinf(angleOfTrajectory*PI/180));
					else
						catcher_x = firefly_x + (distance*sinf(angleOfTrajectory*PI/180));
					if(catcher_y < firefly_y)
						catcher_y = firefly_y - (distance*cosf(angleOfTrajectory*PI/180));
					else
						catcher_y = firefly_y + (distance*cosf(angleOfTrajectory*PI/180));
				}
				
			}

			if(isCaught)
			{
				//output capture location, empty move queues
				outFile << "Firefly " << numFirefly << " caught at (" << firefly_x << "," << firefly_y << ")" << endl;
				queue<int> empty;
				queue<int> empty2;
				rightMoves.swap(empty);
				leftMoves.swap(empty2);
			}
			else
			{
				//output 
				outFile << "Firefly " << numFirefly << " was not caught" << endl;
			}

			numFirefly++;
			inFile >> maxJump  >> catcher_x >> catcher_y;
		}

		outFile.close();
	}

	inFile.close();
}