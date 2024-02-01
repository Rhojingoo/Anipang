#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "PlayLevel.h"
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>

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

	UEngineDirectory NewPath;
	NewPath.MoveParent();

	NewPath.Move("ContentsResources");
	NewPath.Move("Texture");

	// resource Image의 전체적인 순회
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}


	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("Score");
	CreateLevel<UPlayLevel>("Play");

	ChangeLevel("Title");
}

void UAnipangCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}


