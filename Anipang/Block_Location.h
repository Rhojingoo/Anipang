#pragma once
#include <EngineBase\EngineMath.h>

class Block_Location
{
public:
	Block_Location();
	~Block_Location();

	Block_Location(const Block_Location& _Other)					= delete;
	Block_Location(Block_Location& _Other) noexcept					= delete;
	Block_Location& operator =(const 	Block_Location& _Other)		= delete;
	Block_Location& operator =(Block_Location& _Other)noexcept		= delete;

	const FVector GetBlockFVector(int _XLocation,int _YLocation);


protected:


private:
	const FVector StartLocation = { 32, 214 };
	const int CellSize = 67;


	const FVector Zero_Zero = { StartLocation.X, StartLocation.Y };
	const FVector Zero_One = { StartLocation.X + CellSize * 1, StartLocation.Y };
	const FVector Zero_Two = { StartLocation.X + CellSize * 2, StartLocation.Y };
	const FVector Zero_Three = { StartLocation.X + CellSize * 3, StartLocation.Y };
	const FVector Zero_Four = { StartLocation.X + CellSize * 4, StartLocation.Y };
	const FVector Zero_Five = { StartLocation.X + CellSize * 5, StartLocation.Y };
	const FVector Zero_Six = { StartLocation.X + CellSize * 6, StartLocation.Y };

	const FVector One_Zero = { StartLocation.X, StartLocation.Y + CellSize * 1 };
	const FVector One_One = { StartLocation.X + CellSize * 1, StartLocation.Y + CellSize * 1 };
	const FVector One_Two = { StartLocation.X + CellSize * 2, StartLocation.Y + CellSize * 1 };
	const FVector One_Three = { StartLocation.X + CellSize * 3, StartLocation.Y + CellSize * 1 };
	const FVector One_Four = { StartLocation.X + CellSize * 4, StartLocation.Y + CellSize * 1 };
	const FVector One_Five = { StartLocation.X + CellSize * 5, StartLocation.Y + CellSize * 1 };
	const FVector One_Six = { StartLocation.X + CellSize * 6, StartLocation.Y + CellSize * 1 };

	const FVector Two_Zero = { StartLocation.X, StartLocation.Y + CellSize * 2 };
	const FVector Two_One = { StartLocation.X + CellSize * 1, StartLocation.Y + CellSize * 2 };
	const FVector Two_Two = { StartLocation.X + CellSize * 2, StartLocation.Y + CellSize * 2 };
	const FVector Two_Three = { StartLocation.X + CellSize * 3, StartLocation.Y + CellSize * 2 };
	const FVector Two_Four = { StartLocation.X + CellSize * 4, StartLocation.Y + CellSize * 2 };
	const FVector Two_Five = { StartLocation.X + CellSize * 5, StartLocation.Y + CellSize * 2 };
	const FVector Two_Six = { StartLocation.X + CellSize * 6, StartLocation.Y + CellSize * 2 };

	const FVector Three_Zero = { StartLocation.X, StartLocation.Y + CellSize * 3 };
	const FVector Three_One = { StartLocation.X + CellSize * 1, StartLocation.Y + CellSize * 3 };
	const FVector Three_Two = { StartLocation.X + CellSize * 2, StartLocation.Y + CellSize * 3 };
	const FVector Three_Three = { StartLocation.X + CellSize * 3, StartLocation.Y + CellSize * 3 };
	const FVector Three_Four = { StartLocation.X + CellSize * 4, StartLocation.Y + CellSize * 3 };
	const FVector Three_Five = { StartLocation.X + CellSize * 5, StartLocation.Y + CellSize * 3 };
	const FVector Three_Six = { StartLocation.X + CellSize * 6, StartLocation.Y + CellSize * 3 };

	const FVector Four_Zero = { StartLocation.X, StartLocation.Y + CellSize * 4 };
	const FVector Four_One = { StartLocation.X + CellSize * 1, StartLocation.Y + CellSize * 4 };
	const FVector Four_Two = { StartLocation.X + CellSize * 2, StartLocation.Y + CellSize * 4 };
	const FVector Four_Three = { StartLocation.X + CellSize * 3, StartLocation.Y + CellSize * 4 };
	const FVector Four_Four = { StartLocation.X + CellSize * 4, StartLocation.Y + CellSize * 4 };
	const FVector Four_Five = { StartLocation.X + CellSize * 5, StartLocation.Y + CellSize * 4 };
	const FVector Four_Six = { StartLocation.X + CellSize * 6, StartLocation.Y + CellSize * 4 };

	const FVector Five_Zero = { StartLocation.X, StartLocation.Y + CellSize * 5 };
	const FVector Five_One = { StartLocation.X + CellSize * 1, StartLocation.Y + CellSize * 5 };
	const FVector Five_Two = { StartLocation.X + CellSize * 2, StartLocation.Y + CellSize * 5 };
	const FVector Five_Three = { StartLocation.X + CellSize * 3, StartLocation.Y + CellSize * 5 };
	const FVector Five_Four = { StartLocation.X + CellSize * 4, StartLocation.Y + CellSize * 5 };
	const FVector Five_Five = { StartLocation.X + CellSize * 5, StartLocation.Y + CellSize * 5 };
	const FVector Five_Six = { StartLocation.X + CellSize * 6, StartLocation.Y + CellSize * 5 };

	const FVector Six_Zero = { StartLocation.X, StartLocation.Y + CellSize * 6 };
	const FVector Six_One = { StartLocation.X + CellSize * 1, StartLocation.Y + CellSize * 6 };
	const FVector Six_Two = { StartLocation.X + CellSize * 2, StartLocation.Y + CellSize * 6 };
	const FVector Six_Three = { StartLocation.X + CellSize * 3, StartLocation.Y + CellSize * 6 };
	const FVector Six_Four = { StartLocation.X + CellSize * 4, StartLocation.Y + CellSize * 6 };
	const FVector Six_Five = { StartLocation.X + CellSize * 5, StartLocation.Y + CellSize * 6 };
	const FVector Six_Six = { StartLocation.X + CellSize * 6, StartLocation.Y + CellSize * 6 };
};

