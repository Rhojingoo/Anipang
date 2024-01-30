#include "TestBullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

TestBullet::TestBullet()
{
}

TestBullet::~TestBullet()
{
}

void TestBullet::BeginPlay()
{
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImageToScale("CB.png");
	}

	SetActorScale({ 50, 50 });
	Destroy(2.0f);
}

void TestBullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);	
}

