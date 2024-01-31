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
		Renderer = CreateImageRenderer(0);
		Renderer->SetImageToScale("Cat00.png");
	}


	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void AAnimal::Tick(float _DeltaTime)
{
#pragma region 테스트 코드
	if (true == UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsDown('Q'))
	{
		ATestBullet* NewBullet = GetWorld()->SpawnActor<ATestBullet>();
		NewBullet->SetActorLocation(GetActorLocation());
		NewBullet->SetDir(FVector::Right);
	}

	AActor::Tick(_DeltaTime);
#pragma endregion
}
