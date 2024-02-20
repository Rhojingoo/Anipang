#include "Block_Location.h"

UBlock_Location::UBlock_Location()
{
}

UBlock_Location::~UBlock_Location()
{
}

const FVector UBlock_Location::GetBlockFVector(int _XLocation, int _YLocation)
{
	if (_XLocation == 0 && _YLocation == 0)
	{
		return Zero_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 0)
	{
		return Zero_One;
	}
	else if (_XLocation == 2 && _YLocation == 0)
	{
		return Zero_Two;
	}
	else if (_XLocation == 3 && _YLocation == 0)
	{
		return Zero_Three;
	}
	else if (_XLocation == 4 && _YLocation == 0)
	{
		return Zero_Four;
	}
	else if (_XLocation == 5 && _YLocation == 0)
	{
		return Zero_Five;
	}
	else if (_XLocation == 6 && _YLocation == 0)
	{
		return Zero_Six;
	}


		
	else if (_XLocation == 0 && _YLocation == 1)
	{
		return One_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 1)
	{
		return One_One;
	}
	else if (_XLocation == 2 && _YLocation == 1)
	{
		return One_Two;
	}
	else if (_XLocation == 3 && _YLocation == 1)
	{
		return One_Three;
	}
	else if (_XLocation == 4 && _YLocation == 1)
	{
		return One_Four;
	}
	else if (_XLocation == 5 && _YLocation == 1)
	{
		return One_Five;
	}
	else if (_XLocation == 6 && _YLocation == 1)
	{
		return One_Six;
	}


	
		

	else if (_XLocation == 0 && _YLocation == 2)
	{
		return Two_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 2)
	{
		return Two_One;
	}
	else if (_XLocation == 2 && _YLocation == 2)
	{
		return Two_Two;
	}
	else if (_XLocation == 3 && _YLocation == 2)
	{
		return Two_Three;
	}
	else if (_XLocation == 4 && _YLocation == 2)
	{
		return Two_Four;
	}
	else if (_XLocation == 5 && _YLocation == 2)
	{
		return Two_Five;
	}
	else if (_XLocation == 6 && _YLocation == 2)
	{
		return Two_Six;
	}

					
		
	else if (_XLocation == 0 && _YLocation == 3)
	{
		return Three_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 3)
	{
		return Three_One;
	}
	else if (_XLocation == 2 && _YLocation == 3)
	{
		return Three_Two;
	}
	else if (_XLocation == 3 && _YLocation == 3)
	{
		return Three_Three;
	}
	else if (_XLocation == 4 && _YLocation == 3)
	{
		return Three_Four;
	}
	else if (_XLocation == 5 && _YLocation == 3)
	{
		return Three_Five;
	}
	else if (_XLocation == 6 && _YLocation == 3)
	{
		return Three_Six;
	}

			
	
	else if (_XLocation == 0 && _YLocation == 4)
	{
		return Four_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 4)
	{
		return Four_One;
	}
	else if (_XLocation == 2 && _YLocation == 4)
	{
		return Four_Two;
	}
	else if (_XLocation == 3 && _YLocation == 4)
	{
		return Four_Three;
	}
	else if (_XLocation == 4 && _YLocation == 4)
	{
		return Four_Four;
	}
	else if (_XLocation == 5 && _YLocation == 4)
	{
		return Four_Five;
	}
	else if (_XLocation == 6 && _YLocation == 4)
	{
		return Four_Six;
	}




	else if (_XLocation == 0 && _YLocation == 5)
	{
		return Five_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 5)
	{
		return Five_One;
	}
	else if (_XLocation == 2 && _YLocation == 5)
	{
		return Five_Two;
	}
	else if (_XLocation == 3 && _YLocation == 5)
	{
		return Five_Three;
	}
	else if (_XLocation == 4 && _YLocation == 5)
	{
		return Five_Four;
	}
	else if (_XLocation == 5 && _YLocation == 5)
	{
		return Five_Five;
	}
	else if (_XLocation == 6 && _YLocation == 5)
	{
		return Five_Six;
	}



	else if (_XLocation == 0 && _YLocation == 6)
	{
		return Six_Zero;
	}
	else if (_XLocation == 1 && _YLocation == 6)
	{
		return Six_One;
	}
	else if (_XLocation == 2 && _YLocation == 6)
	{
		return Six_Two;
	}
	else if (_XLocation == 3 && _YLocation == 6)
	{
		return Six_Three;
	}
	else if (_XLocation == 4 && _YLocation == 6)
	{
		return Six_Four;
	}
	else if (_XLocation == 5 && _YLocation == 6)
	{
		return Six_Five;
	}
	else if (_XLocation == 6 && _YLocation == 6)
	{
		return Six_Six;
	}

}
