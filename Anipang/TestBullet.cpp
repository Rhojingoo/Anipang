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
	SetActorScale({ 50, 50 });
}

void TestBullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

