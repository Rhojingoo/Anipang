#include "EndingLevel.h"
#include "Ending_BackGround.h"
#include "FadeIN_OUT.h"
#include <EngineCore\EngineCore.h>

UEndingLevel::UEndingLevel()
{
}

UEndingLevel::~UEndingLevel()
{
}

void UEndingLevel::BeginPlay()
{
	ULevel::BeginPlay();


	SpawnActor<AEnding_BackGround>();

}

void UEndingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UEndingLevel::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
}

void UEndingLevel::LevelEnd(ULevel* _Level)
{
}
