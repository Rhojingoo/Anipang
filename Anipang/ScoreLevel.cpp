#include "ScoreLevel.h"
#include <EngineCore\EngineCore.h>
#include "FadeIN_OUT.h"
#include "Score_BackGround.h"
#include "ScoreBoard.h"
#include "Cursor.h"


UScoreLevel::UScoreLevel()
{
}

UScoreLevel::~UScoreLevel()
{
}

void UScoreLevel::BeginPlay()
{
	ULevel::BeginPlay();
	SpawnActor<AScore_BackGround>();
	SpawnActor<AScoreBoard>();
	Cursoor = SpawnActor<ACursor>();
}

void UScoreLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('N'))
	{
		GEngine->ChangeLevel("Ending");
	}
}

void UScoreLevel::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
}

void UScoreLevel::LevelEnd(ULevel* _Level)
{
}
