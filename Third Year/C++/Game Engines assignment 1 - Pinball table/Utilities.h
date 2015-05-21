#ifndef Utilities_H
#define Utilities_H
#include <vector>
#include <iostream>
#include "PhysicsEngine.h"
//Helper function for converting to radians
inline PhysicsEngine::PxReal ToRadians(PhysicsEngine::PxReal degreesIn)
{
	return 0.0174532925f*degreesIn;
}

//table transform
const PhysicsEngine::PxTransform tableTransform = PhysicsEngine::PxTransform(PhysicsEngine::PxVec3(0.f,10.f,0.f),
																	   PhysicsEngine::PxQuat(ToRadians(7),PhysicsEngine::PxVec3(1.0f,0.0f,0.0f)));
using namespace PhysicsEngine;

/*Struct for storing colours for compound actors
and an index array linking each shape to its particular colour*/
struct shapeColours
{
	unsigned int numShapes;
	unsigned int *colourIndices;
	std::vector<PxVec3> colours;

	shapeColours(int _numShapes)
		:numShapes(_numShapes)
	{
		colourIndices = new unsigned int[numShapes];
		colours = std::vector<PxVec3>(0);
	}
	~shapeColours()
	{
		delete[] colourIndices;
	}
	//indexed from zero
	void SetShapeColour(int shapeNum, int colourNum)
	{
 		colourIndices[shapeNum] = colourNum;
	}

	void addColour(PxVec3 &shapeColour)
	{
		colours.push_back(shapeColour);
	}
	//indexed from zero
	PxVec3& GetColour(unsigned int shapeNum)
	{
		if(shapeNum < numShapes && (colourIndices[shapeNum] < colours.size()))
		return colours.at(colourIndices[shapeNum]);
		else
		{
			std::cout << "Error overan array bounds";
			return colours.at(colourIndices[0]) ;
		}
	}

	PxVec3& GetColourAtIndex(unsigned int index)
	{
		if(index < colours.size())
		{
			return colours.at(index);
		}
		else
		{
			std::cout << "Error overan array bounds";
			return colours.at(0);
		}
	}

	
};

//enumeration used for index colour array in the table object
 enum tableShapes
		{
			BOTTOM,
			RIGHTWALL,
			LEFTWALL,
			TOPWALL,
			BOTTOMWALL,
			CONTAINMENTWALL,
			TOPRIGHTDIAG,
			TOPLEFTDIAG,
			RIGHTINNER,
			LEFTINNER,
			RIGHTINNERDIAG,
			LEFTINNERDIAG,
			MIDDLEBUMPER,
			LEFTBUMPER,
			RIGHTBUMPER,
			LEFTBLOCKER,
			RIGHTBLOCKER,
			BOTTOMRIGHTBUMPER,
			BOTTOMLEFTBUMPER
		};
#endif // !Utilities_H
