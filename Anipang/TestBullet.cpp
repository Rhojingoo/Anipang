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
		UImageRenderer* Renderer = CreateImageRenderer(20);	
		Renderer->SetImage("Boomb_Effect");
		Renderer->SetTransform({ {0,-175}, {135, 350} });
		Renderer->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
		Renderer->ChangeAnimation("Idle");

	}
		/*Destroy(2.0f);*/
	#pragma endregion
}

void ATestBullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(Dir * Speed * _DeltaTime);	
}

