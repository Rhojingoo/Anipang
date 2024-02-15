#include "ScreenScore_Level.h"
#include <EngineCore\EngineCore.h>
#include "FadeIN_OUT.h"
#include "Score_BackGround.h"
#include "ScoreBoard.h"
#include "Cursor.h"
#include "ScoreManager.h"

#include "GameStart_UI.h"
#include "CheckScore_UI.h"
#include "GameEnd_UI.h"
#include "MainScreen_UI.h"

UScreenScore_Level::UScreenScore_Level()
{
}

UScreenScore_Level::~UScreenScore_Level()
{
}

void UScreenScore_Level::BeginPlay()
{
	ULevel::BeginPlay();
	SpawnActor<AScore_BackGround>();
	//SpawnActor<AScoreBoard>();
	Cursor = SpawnActor<ACursor>();

	AGameStart_UI* GameStartUI = SpawnActor<AGameStart_UI>();
	GameStartUI->SetActorLocation({ 240,590 });
	GameStartUI->SetCursor(Cursor);

	//48
	AMainScreen_UI* ScoreUI = SpawnActor<AMainScreen_UI>();
	ScoreUI->SetActorLocation({ 240,638 });
	ScoreUI->SetCursor(Cursor);


	AGameEnd_UI* GameendUI = SpawnActor<AGameEnd_UI>();
	GameendUI->SetActorLocation({ 240,686 });
	GameendUI->SetCursor(Cursor);

}

void UScreenScore_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UScreenScore_Level::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
}

void UScreenScore_Level::LevelEnd(ULevel* _Level)
{
}
