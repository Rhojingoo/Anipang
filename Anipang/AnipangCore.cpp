#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "PlayLevel.h"

UAnipangCore::UAnipangCore()
: UEngineCore()
{
}

UAnipangCore::~UAnipangCore()
{
}

void UAnipangCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 1280, 720 });	

	SetFrame(60);

	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("Score");
	CreateLevel<UPlayLevel>("Play");

	ChangeLevel("Title");
}

void UAnipangCore::Tick(float _DeltaTime)
{

}

void UAnipangCore::End()
{
}
