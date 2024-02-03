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

	{
		//FVector WindowScale = GEngine->MainWindow.GetWindowScale();

		//// 여기서 위치가 안정해졌다고 이녀석위치가 0,0인건 아니죠
		//AActor* Back = SpawnActor<AActor>();
		//UImageRenderer* Renderer = Back->CreateImageRenderer();
		//Renderer->SetOrder(-10);
		//// 
		//Renderer->SetTransColor(Color8Bit::Magenta.ZeroAlphaColor());
		//Renderer->SetImage("Title.png");
		//Renderer->SetPosition(WindowScale.Half2D());
		//Renderer->SetScale(WindowScale);
		//Renderer->SetImageCuttingTransform({ { 0, 0 }, {100, 100} });
	}

	SpawnActor<ATitle_BackGround>();
	SpawnActor<ACursor_Pointe>();

}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
