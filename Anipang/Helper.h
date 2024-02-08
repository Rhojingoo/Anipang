#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <random>

class UHelper
{
public:
	static FVector GetMousePos();
	static int Random(int _min, int _max);



private:
	// constrcuter destructer
	UHelper();
	~UHelper();
};