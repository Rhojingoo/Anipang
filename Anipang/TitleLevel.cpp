#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "Title_BackGround.h"
#include "Animal_Block.h"
#include "ACursor_Pointe.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	SpawnActor<ATitle_BackGround>();
	//SpawnActor<ATitle_Moon>();	
	SpawnActor<ACursor_Pointe>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('N'))
	{
		GEngine->ChangeLevel("Play");
	}
}

void UTitleLevel::LevelStart(ULevel* _Level)
{
}

void UTitleLevel::LevelEnd(ULevel* _Level)
{
}
