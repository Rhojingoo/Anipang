#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "Title_BackGround.h"
#include "Cursor.h"
#include "Title_Logo.h"
#include "Title_LogoChick.h"
#include "Title_PointAnimation.h"
#include "GameStart_UI.h"
#include "CheckScore_UI.h"
#include "GameEnd_UI.h"


#include "Game_Start.h"
#include "Game_End.h"

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
	Cursor = SpawnActor<ACursor>();
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
			AGameStart_UI* GameStartUI = SpawnActor<AGameStart_UI>();
			GameStartUI->SetActorLocation({ 240,440 });
			GameStartUI->SetCursor(Cursor);		

			//48
			ACheckScore_UI* ScoreUI = SpawnActor<ACheckScore_UI>();
			ScoreUI->SetActorLocation({ 240,488 });
			ScoreUI->SetCursor(Cursor);
			

			AGameEnd_UI* GameendUI = SpawnActor<AGameEnd_UI>();
			GameendUI->SetActorLocation({ 240,536 });
			GameendUI->SetCursor(Cursor);

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
