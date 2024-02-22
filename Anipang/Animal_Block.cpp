#include "Animal_Block.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "BoombBlock_Effect.h"
#include "BlockBoomb_Effect.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>



bool AAnimal_Block::FirstClick = false;
bool AAnimal_Block::SecondClick = false;
bool AAnimal_Block::SwapREADY = false;
bool AAnimal_Block::ClickChange = false;
bool AAnimal_Block::SwapChange = false;

ABoombBlock_Effect* AAnimal_Block::BoombBlock_First_Effect = nullptr;
ABoombBlock_Effect* AAnimal_Block::BoombBlock_Left_Effect = nullptr;
ABoombBlock_Effect* AAnimal_Block::BoombBlock_Right_Effect = nullptr;
ABoombBlock_Effect* AAnimal_Block::BoombBlock_Down_Effect = nullptr;


bool AAnimal_Block::BoombBlock_FirstEffect_Create = false;
bool AAnimal_Block::BoombBlock_SecondEffect_Create = false;
FVector AAnimal_Block::BoombBlock_First_Effect_Pos = {};
FVector AAnimal_Block::BoombBlock_Right_Effect_Pos = {};
FVector AAnimal_Block::BoombBlock_Left_Effect_Pos = {};
FVector AAnimal_Block::BoombBlock_Down_Effect_Pos = {};



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
	CheckBoombBlockEffect();
}

void AAnimal_Block::CreateBlockEffect()
{	
	Block_Destroy_Effect = GetWorld()->SpawnActor<ABlockBoomb_Effect>();
	Block_Destroy_Effect->SetActorLocation(GetActorLocation());
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
		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
			if (Blocktype == Block_Type::Boomb)
			{
				if (BlockClick == false)
				{
					BlockClick = true;
				}				
				return;
			}

			if (FirstClick == false && FirstPick == false)
			{
				if (SecondPick == true)
				{
					return;
				}		
				BlockClick = true;
				FirstClick = true;
				FirstPick = true;				
			}
			else if (SecondClick == false && SecondPick == false)
			{
				if (FirstPick == true)
				{
					return;
				}		
				BlockClick = true;
				SecondClick = true;
				SecondPick = true;
			}
			//else if (FirstClick == true && SecondClick == true)
			//{
			//	if (FirstPick == true)
			//	{
			//		BlockClick = false;
			//		FirstClick = false;
			//		FirstPick = false;
			//	}
			//	else if (SecondPick == true)
			//	{
			//		BlockClick = false;
			//		SecondClick = false;
			//		SecondPick = false;
			//	}
			//}

			else if (FirstClick == true && FirstPick == true)
			{				
				if (SecondPick == true)
				{
					return;
				}
				BlockClick = false;
				FirstClick = false;
				FirstPick = false;
				
			}
			else if (SecondClick == true && SecondPick == true)
			{
				if (FirstPick == true)
				{
					return;
				}
				BlockClick = false;
				SecondClick = false;
				SecondPick = false;
				
			}
		}
	}
	else
	{
		int a = 0;
	}
}

void AAnimal_Block::CheckBoombBlockEffect()
{
	if (BoombBlock_FirstEffect_Create == true)
	{
		BoombBlock_First_Effect_Pos = BoombBlock_First_Effect->GetActorLocation();

		float MinX = Pos.X - Size.X / 2;
		float MinY = Pos.Y - Size.Y / 2;
		float MaxX = Pos.X + Size.X / 2;
		float MaxY = Pos.Y + Size.Y / 2;
		int a = 0;
		if (BoombBlock_First_Effect_Pos.X >= MinX && BoombBlock_First_Effect_Pos.X <= MaxX && BoombBlock_First_Effect_Pos.Y - 75.f >= MinY && BoombBlock_First_Effect_Pos.Y - 75.f <= MaxY)
		{
			// 콜리전 체크 하면서 현재블럭의 row와 col을 받아서 조건을 달것.
			// row와 col의 위치에따라 left인지 right인지, down인지 정해서 만들어 보내줄것.

			int Row = GetBlockLocationRow();
			int Col = GetBlockLocationCol();

			int a = 0;		

			BoombBlock_First_Effect_Toutch = true;
		}
	}
	else if (BoombBlock_SecondEffect_Create == true)
	{
		float MinX = Pos.X - Size.X / 2;
		float MinY = Pos.Y - Size.Y / 2;
		float MaxX = Pos.X + Size.X / 2;
		float MaxY = Pos.Y + Size.Y / 2;

		if (BoombBlock_Right_Effect == nullptr && BoombBlock_Left_Effect == nullptr && BoombBlock_Down_Effect == nullptr)
		{
			BoombBlock_SecondEffect_Create = false;
		}
		if (BoombBlock_Right_Effect != nullptr)
		{
			BoombBlock_Right_Effect_Pos = BoombBlock_Right_Effect->GetActorLocation();
			if (BoombBlock_Right_Effect_Pos.X >= MinX && BoombBlock_Right_Effect_Pos.X <= MaxX && BoombBlock_Right_Effect_Pos.Y >= MinY && BoombBlock_Right_Effect_Pos.Y <= MaxY)
			{
				BoombBlock_First_Effect_Toutch = true;
			}
		}
		if (BoombBlock_Left_Effect != nullptr)
		{
			BoombBlock_Left_Effect_Pos = BoombBlock_Left_Effect->GetActorLocation();
			if (BoombBlock_Left_Effect_Pos.X >= MinX && BoombBlock_Left_Effect_Pos.X <= MaxX && BoombBlock_Left_Effect_Pos.Y >= MinY && BoombBlock_Left_Effect_Pos.Y <= MaxY)
			{
				BoombBlock_First_Effect_Toutch = true;
			}
		}
		if (BoombBlock_Down_Effect != nullptr)
		{
			BoombBlock_Down_Effect_Pos = BoombBlock_Down_Effect->GetActorLocation();
			if (BoombBlock_Down_Effect_Pos.X >= MinX && BoombBlock_Down_Effect_Pos.X <= MaxX && BoombBlock_Down_Effect_Pos.Y - 75.f >= MinY && BoombBlock_Down_Effect_Pos.Y - 75.f <= MaxY)
			{
				BoombBlock_First_Effect_Toutch = true;
			}
		}

	}
}
