#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "PlayLevel.h"

AnipangCore::AnipangCore()
: EngineCore()
{
}

AnipangCore::~AnipangCore()
{
}

void AnipangCore::BeginPlay()
{
	SetFrame(60);

	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("Score");
	CreateLevel<UPlayLevel>("Play");

	ChangeLevel("Title");
}

void AnipangCore::Tick(float _DeltaTime)
{

}

void AnipangCore::End()
{
}
