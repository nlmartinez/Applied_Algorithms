#include<fstream>
#include<iostream>
#include<math.h>
#include<vector>
#include<set>
#include<math.h>

#define PI 3.14159265

using std::ifstream;
using std::ofstream;
using std::vector;
using std::cout;
using std::acosf;

struct Coordinate
{
	float x;
	float y;
};

int main()
{
	ifstream inFile("convex.in");

	if(inFile)
	{
		ofstream outFile("convex.out");
		int numOfCoordinates; float x; float y;

		inFile >> numOfCoordinates;
		int currentSet = 1;
		while(numOfCoordinates > 0)
		{
			Coordinate coordinates[10000];
			for(int i = 0; i < numOfCoordinates; i++)
			{
				Coordinate newCoordinate;
				inFile >> x; inFile >> y;
				newCoordinate.x = x;
				newCoordinate.y = y;
				coordinates[i]= newCoordinate;
			}

			Coordinate firstNode = coordinates[0];
			vector<Coordinate> markedNodes;
			for(int i = 0; i < numOfCoordinates; i++)
			{
				if(firstNode.x == coordinates[i].x)
					if(firstNode.y > coordinates[i].y)
						firstNode = coordinates[i];
				else if(firstNode.x > coordinates[i].x)
					firstNode = coordinates[i];
			}
			markedNodes.push_back(firstNode);
			Coordinate hullNode;
			bool secondNodeFound = false;
			for(int i = 0; i < numOfCoordinates; i++)
			{
				if(coordinates[i].x == firstNode.x)
					if(coordinates[i].y > firstNode.y){
						hullNode = coordinates[i];
						secondNodeFound = true;
					}
			}

			if(secondNodeFound)
				markedNodes.push_back(hullNode);
			if(markedNodes.size() == 1)
			{
				float greatestSlope = 0;
				for(int i = 0; i < numOfCoordinates; i++)
				{
					if(coordinates[i].x != firstNode.y){
						float slope = (coordinates[i].y - firstNode.y)/(coordinates[i].x - firstNode.x);
						if(slope > greatestSlope)
							hullNode = coordinates[i];
					}
				}
				markedNodes.push_back(hullNode);
			}
			//find rest of the hull
			bool hullComplete = false;
			while(!hullComplete)
			{
				int lastNode = markedNodes.size() - 1;
				Coordinate nextNode = coordinates[0];
				//find initial relative angle
				float sideA = sqrtf((markedNodes[lastNode].x - markedNodes[lastNode -1].x)*(markedNodes[lastNode].x - markedNodes[lastNode -1].x)
								+ (markedNodes[lastNode].y - markedNodes[lastNode-1].y)* (markedNodes[lastNode].y - markedNodes[lastNode-1].y));
				float sideB = sqrtf((coordinates[0].x - markedNodes[lastNode].x)*(coordinates[0].x - markedNodes[lastNode].x)
								+ (coordinates[0].y - markedNodes[lastNode].y)* (coordinates[0].y - markedNodes[lastNode].y));
				float sideC = sqrtf((markedNodes[lastNode - 1].x - coordinates[0].x)*(markedNodes[lastNode - 1].x - coordinates[0].x)
								+ (markedNodes[lastNode - 1].y - coordinates[0].y)* (markedNodes[lastNode - 1].y - coordinates[0].y));
				float greatestRelativeAngle = acosf((sideB*sideB) + (sideC*sideC) - (sideA*sideA))
											/(2*sideB*sideC);
				for(int i = 1; i < numOfCoordinates; i++)
				{	
					sideB = sqrtf((coordinates[i].x - markedNodes[lastNode].x)*(coordinates[i].x - markedNodes[lastNode].x)
								+ (coordinates[i].y - markedNodes[lastNode].y)* (coordinates[i].y - markedNodes[lastNode].y));
					sideC = sqrtf((markedNodes[lastNode - 1].x - coordinates[i].x)*(markedNodes[lastNode - 1].x - coordinates[i].x)
								+ (markedNodes[lastNode - 1].y - coordinates[i].y)* (markedNodes[lastNode - 1].y - coordinates[i].y));
					float relativeAngle = acosf(((sideB*sideB) + (sideC*sideC) - (sideA*sideA))
											/(2*sideB*sideC))*PI/180;
					if(greatestRelativeAngle < relativeAngle){
						nextNode = coordinates[i];
						greatestRelativeAngle = relativeAngle;
					}
				}

				if(nextNode.x == coordinates[0].x && nextNode.y == coordinates[0].y)
					hullComplete = true;
				else{
					markedNodes.push_back(nextNode);
				}

			}

			//Print results
			cout << "Set #" << currentSet << ": ";
			for(int i = 0; i < markedNodes.size(); i++)
				cout << "(" << markedNodes[i].x << "," << markedNodes[i].y << ") ";
			cout << std::endl;

			inFile >> numOfCoordinates;
		}
		
	}
	else
	{
		cout << "Could not find convex.in." << std::endl;
	}
}