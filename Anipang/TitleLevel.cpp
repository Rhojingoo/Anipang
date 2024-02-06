#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "Title_BackGround.h"
#include "Animal_Block.h"
#include "ACursor_Point.h"
#include "Title_Logo.h"
#include "Title_Button.h"
#include "Title_LogoChick.h"
#include "Title_PointAnimation.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	Title_BG = SpawnActor<ATitle_BackGround>();
	SpawnActor<ACursor_Pointe>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (Title_BG->Isfinish() == true)
	{
		if (LogoMake == false)
		{
			SpawnActor<ATitle_Logo>();		
			SpawnActor<ATitle_LogoChick>();			
			SpawnActor<ATitle_PointAnimation>();
			SpawnActor<ATitle_Button>();
			LogoMake = true;
		}
	}

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
