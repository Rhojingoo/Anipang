#include "Helper.h"

UHelper::UHelper()
{
}

UHelper::~UHelper()
{
}

FVector UHelper::GetMousePos()
{
    return GEngine->MainWindow.GetMousePosition();
}

int UHelper::Random(int _min, int _max)
{
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(_min, _max);
		return dis(gen);
	}
}
