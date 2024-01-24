#include "AnipangCore.h"
#include "TitleLevel.h"

AnipangCore::AnipangCore()
{
}

AnipangCore::~AnipangCore()
{
}

void AnipangCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("Title");
	//CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("Title");
	int a = 0;
}

void AnipangCore::Tick(float _DeltaTime)
{
	//플레이어가 움직일 수 있도로고 구현하면되는 곳
}

void AnipangCore::End()
{
}
