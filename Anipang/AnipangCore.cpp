#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
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
	//MainWindow.SetWindowPosition({500, 100});
	MainWindow.SetWindowScale({ 480, 800 });	

	SetFrame(60);

	UEngineDirectory NewDir;
	NewDir.MoveParent();

	NewDir.Move("ContentsResources");
	NewDir.Move("Texture");

	// resource Image의 전체적인 순회
	std::list<UEngineFile> AllFileList = NewDir.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("TestSpriteAni.png", 13, 8);
	
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Cat"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Checkin"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Monkey"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Mouse"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Pig"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Rabbit"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Block_Effect"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Boomb_Effect"));
	

	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Title_Level\\Intro_BG"));
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Title_Level\\Intro_OBJ"));

	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("Score");
	CreateLevel<UPlayLevel>("Play");
	CreateLevel<UEndingLevel>("Ending");

	ChangeLevel("Title");
}

void UAnipangCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}


