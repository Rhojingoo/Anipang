#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "PlayLevel.h"

AnipangCore::AnipangCore()
{
}

AnipangCore::~AnipangCore()
{
}

void AnipangCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("Score");
	CreateLevel<UPlayLevel>("Play");

	ChangeLevel("Title");
}

void AnipangCore::Tick(float _DeltaTime)
{
	//플레이어가 움직일 수 있도로고 구현하면되는 곳
}

void AnipangCore::End()
{
}
