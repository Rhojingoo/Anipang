#include "TestBullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

ATestBullet::ATestBullet()
{
}

ATestBullet::~ATestBullet()
{
}

void ATestBullet::BeginPlay()
{
	#pragma region 테스트 코드
	{
		AActor::BeginPlay();
		UImageRenderer* Renderer = CreateImageRenderer(-10);	
		Renderer->SetImage("boom.png");
		//SetActorLocation({ 50, 50 });
		Renderer->SetTransform({ {50,50}, {35, 35} });
		Renderer->SetImageCuttingTransform({ {0,0}, {35, 35} });
	}
		Destroy(2.0f);
	#pragma endregion
}

void ATestBullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(Dir * Speed * _DeltaTime);	
}

