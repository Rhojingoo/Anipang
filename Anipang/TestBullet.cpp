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
			//UImageRenderer* Renderer = CreateImageRenderer(-10);
			//Renderer->SetImageToScale("Mouse00.png");
		}

		{
			UImageRenderer* Renderer = CreateImageRenderer(-10);
			Renderer->SetImageToScale("boom.png");
		}
		//SetActorScale({ 100, 100 });
		Destroy(2.0f);
	#pragma endregion
}

void ATestBullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);	
	AActor::Tick(_DeltaTime);
}

