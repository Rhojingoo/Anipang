#include "Animal_Block.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "TestBullet.h"
#include "BlockBoomb_Effect.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>

bool AAnimal_Block::FirstClick = false;
bool AAnimal_Block::SecondClick = false;
bool AAnimal_Block::SwapREADY = false;
bool AAnimal_Block::ClickChange = false;
bool AAnimal_Block::SwapChange = false;

AAnimal_Block::AAnimal_Block()
{
}

AAnimal_Block::~AAnimal_Block()
{
}

void AAnimal_Block::BeginPlay()
{
	AActor::BeginPlay();
}

void AAnimal_Block::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	PickingCheck();
}

void AAnimal_Block::CreateBlockEffect()
{	
	ABlockBoomb_Effect* BoomEffect = GetWorld()->SpawnActor<ABlockBoomb_Effect>();
	BoomEffect->SetActorLocation(GetActorLocation());
}

void AAnimal_Block::PickingCheck()
{
	FVector Curpos = Cursor->GetPos();
	
	float MinX = Pos.X - Size.X / 2;
	float MinY = Pos.Y - Size.Y / 2;
	float MaxX = Pos.X + Size.X / 2;
	float MaxY = Pos.Y + Size.Y / 2;

	if (Curpos.X >= MinX && Curpos.X <= MaxX && Curpos.Y >= MinY && Curpos.Y <= MaxY)
	{
		int a = 0;
		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
			if (FirstClick == false)
			{
				if (FirstPick == false && SecondPick == false)
				{
					BlockClick = true;
					FirstClick = true;
					FirstPick = true;
				}
			}
			else if (SecondClick == false)
			{
				if (FirstPick == false && SecondPick == false)
				{
					BlockClick = true;
					SecondClick = true;
					SecondPick = true;
				}
			}
			else if (FirstClick == true)
			{
				if (FirstPick == true && BlockClick == true)
				{
					BlockClick = false;
					FirstClick = false;
					FirstPick = false;
				}
			}
		}
	}
	else
	{
		int a = 0;
	}
}
