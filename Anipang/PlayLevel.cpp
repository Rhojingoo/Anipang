#include "PlayLevel.h"
#include <EngineCore\EngineCore.h>
#include "PadeIN_OUT.h"
#include "Play_Frame.h"

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();
	SpawnActor<APlay_Frame>();

}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('N'))
	{
		GEngine->ChangeLevel("Ending");
	}
}

void UPlayLevel::LevelStart(ULevel* _Level)
{
	SpawnActor<APadeIN_OUT>();
}

void UPlayLevel::LevelEnd(ULevel* _Level)
{
}
