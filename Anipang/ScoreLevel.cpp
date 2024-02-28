#include "ScoreLevel.h"
#include <EngineCore\EngineCore.h>
#include "FadeIN_OUT.h"
#include "Score_BackGround.h"
#include "ScoreBoard.h"
#include "Cursor.h"
#include "ScoreManager.h"

#include "ReStart_UI.h"
#include "GameEnd_UI.h"
#include "MainScreen_UI.h"

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
	Cursor = SpawnActor<ACursor>();
	bool Scoreset = true;

	ScoreMN = SpawnActor<ScoreManager>();
	ScoreMN->ScoreLevelON();

	AReStart_UI* GameStartUI = SpawnActor<AReStart_UI>();
	GameStartUI->SetActorLocation({ 240,540 });
	GameStartUI->SetCursor(Cursor);

	AMainScreen_UI* ScoreUI = SpawnActor<AMainScreen_UI>();
	ScoreUI->SetActorLocation({ 240,588 });
	ScoreUI->SetCursor(Cursor);

	AGameEnd_UI* GameendUI = SpawnActor<AGameEnd_UI>();
	GameendUI->SetActorLocation({ 240,636 });
	GameendUI->SetCursor(Cursor);
}

void UScoreLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	//if (UEngineInput::IsDown('N'))
	//{
	//	GEngine->ChangeLevel("Ending");
	//}
}

void UScoreLevel::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
}

void UScoreLevel::LevelEnd(ULevel* _Level)
{
}
