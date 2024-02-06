#include "ACursor_Point.h"
#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>
#include "Helper.h"


ACursor_Pointe::ACursor_Pointe()
{
}

ACursor_Pointe::~ACursor_Pointe()
{
}

void ACursor_Pointe::BeginPlay()
{
	AActor::BeginPlay();
	{
		// 이미지 한장 랜더
		Renderer = CreateImageRenderer(100);
		Renderer->SetImage("Cursor.png");
		SetActorLocation({ 50, 50 });
		Renderer->SetTransform({ {0,0}, {50, 50} });
		Renderer->SetImageCuttingTransform({ {0,0}, {213, 216} });
	}
}

void ACursor_Pointe::Tick(float _DeltaTime)
{
	UEngineDebug::OutPutDebugText(UHelper::GetMousePos().ToString());
	SetActorLocation(UHelper::GetMousePos());
	AActor::Tick(_DeltaTime);
}
