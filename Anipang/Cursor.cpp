#include "Cursor.h"
#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>
#include <EngineCore\EngineDebug.h>
#include "Helper.h"

ACursor::ACursor()
{
}

ACursor::~ACursor()
{
}

void ACursor::BeginPlay()
{
	AActor::BeginPlay();
	{
		// 이미지 한장 랜더
		Renderer = CreateImageRenderer(100);
		Renderer->SetImage("Cursor.png");
		SetActorLocation({ 50, 50 });
		Renderer->SetTransform({ {15,20}, {50, 50} });
		Renderer->SetImageCuttingTransform({ {0,0}, {213, 216} });
	}
}

void ACursor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineDebug::OutPutDebugText(UHelper::GetMousePos().ToString());
	SetActorLocation(UHelper::GetMousePos());
	Pos = GetTransform().GetPosition();

	if (EnterUI == true)
	{
		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
			GEngine->ChangeLevel("Play");
		}
	}


	UEngineDebug::DebugTextPrint("PlayerPos : " + GetTransform().GetPosition().ToString(), 15.0f);
	UEngineDebug::DebugTextPrint("PlayerScale : " + GetTransform().GetPosition().ToString(), 20.0f);
	UEngineDebug::DebugTextPrint("한글 나오나", 20.0f);
	UEngineDebug::DebugTextPrint("오호", 20.0f);

	int a = 0;
}
