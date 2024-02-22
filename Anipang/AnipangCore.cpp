#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "ScreenScore_Level.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include <EnginePlatform\EngineInput.h>
#include <EnginePlatform\WindowImage.h>


#include "Block_Manager.h"

#include "TestLevel.h"


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
	//MainWindow.SetWindowScale({ 1024, 570 });	
	MainWindow.SetWindowScale({ 480,800 });

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

	//스프라이트
	{
		UEngineResourcesManager::GetInst().CuttingImage("Amber.png", 20, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Amethyst.png", 20, 3); // 문양이상
		UEngineResourcesManager::GetInst().CuttingImage("Diamond.png", 20, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Emerald.png", 20, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Ruby.png", 20, 3);//이상
		UEngineResourcesManager::GetInst().CuttingImage("Sapphire.png", 20, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Topaz.png", 20, 3);
	}
	
	//폴더 애니메이션
	{
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Cat"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Checkin"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Monkey"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Dog"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Mouse"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Pig"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Animal\\Rabbit"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Block_Effect"));
		//UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Boomb_Effect"));
		//UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Boomb_Effect_Dir"));
	

		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("World_On_Fire_Projectile"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Phoenix Landing"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("GameStart"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("GameEnd"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Time\\Big_Number"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Time\\Small_Number"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Time\\TimeGauge"));


		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Title_Level\\Intro_BG"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Title_Level\\Intro_OBJ"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Title_Level\\Intro_Chick"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Title_Level\\Intro_Loading"));


		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("UI_Image\\GameStart_UI"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("UI_Image\\CheckScore_UI"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("UI_Image\\GameEnd_UI"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("UI_Image\\ReStart_UI"));
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("UI_Image\\MainScreen_UI"));
	}

	{
		UWindowImage* Rot = UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Boomb_Effect"));
		UWindowImage* Mask = UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("Boomb_Effect_Dir"));
		Rot->SetRotationMaskImageFolder(Mask);	
	}

	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("GetScore");
	CreateLevel<UScreenScore_Level>("ScreenScore");
	CreateLevel<UPlayLevel>("Play");
	CreateLevel<UEndingLevel>("Ending");
	CreateLevel<TestLevel>("TestLevel");
	
	//ChangeLevel("Title");
	ChangeLevel("TestLevel");
	//Block_Manager::OBJPOOL = &Block_Manager::GetInstance();

}

void UAnipangCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}


