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
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetScale({ 10, 50 });
	}

	{
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetScale({ 50, 10 });
	}

	SetActorScale({ 50, 50 });
	Destroy(2.0f);
}

void TestBullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

