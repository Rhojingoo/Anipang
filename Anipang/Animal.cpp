#include "Animal.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "TestBullet.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>

AAnimal::AAnimal()
{
}

AAnimal::~AAnimal()
{
}

void AAnimal::BeginPlay()
{
	AActor::BeginPlay();

	{
		BodyRenderer = CreateImageRenderer(0);
		BodyRenderer->SetPosition({ 0, 30 });
		BodyRenderer->SetImageToScale("CB2.bmp");
		// BodyRenderer->SetScale({ 80, 80 });
	}


	{
		HeadRenderer = CreateImageRenderer(0);
		HeadRenderer->SetPosition({ 0, -25 });
		HeadRenderer->SetImageToScale("CB2.bmp");
	}

	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void AAnimal::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsDown('Q'))
	{
		TestBullet* NewBullet = GetWorld()->SpawnActor<TestBullet>();
		NewBullet->SetActorLocation(GetActorLocation());
		NewBullet->SetDir(FVector::Right);
	}
}
