#include "Base_Block.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "BombBlock_Effect.h"
#include "BlockBoomb_Effect.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>



bool ABase_Block::FirstClick = false;
bool ABase_Block::SecondClick = false;
bool ABase_Block::SwapREADY = false;
bool ABase_Block::ClickChange = false;
bool ABase_Block::SwapChange = false;

ABombBlock_Effect* ABase_Block::BoombBlock_First_Effect = nullptr;
ABombBlock_Effect* ABase_Block::BoombBlock_Left_Effect = nullptr;
ABombBlock_Effect* ABase_Block::BoombBlock_Right_Effect = nullptr;
ABombBlock_Effect* ABase_Block::BoombBlock_Down_Effect = nullptr;


bool ABase_Block::BoombBlock_FirstEffect_Create = false;
bool ABase_Block::BoombBlock_SecondEffect_Create = false;
FVector ABase_Block::BoombBlock_First_Effect_Pos = {};
FVector ABase_Block::BoombBlock_Right_Effect_Pos = {};
FVector ABase_Block::BoombBlock_Left_Effect_Pos = {};
FVector ABase_Block::BoombBlock_Down_Effect_Pos = {};



ABase_Block::ABase_Block()
{
}

ABase_Block::~ABase_Block()
{
}

void ABase_Block::SetBlockType(int _Set)
{
	if (_Set == 0)
	{
		Blocktype = Block_Type::Cat;
	}
	else if (_Set == 1)
	{
		Blocktype = Block_Type::Checkin;
	}
	else if (_Set == 2)
	{
		Blocktype = Block_Type::Dog;
	}
	else if (_Set == 3)
	{
		Blocktype = Block_Type::Monkey;
	}
	else if (_Set == 4)
	{
		Blocktype = Block_Type::Mouse;
	}
	else if (_Set == 5)
	{
		Blocktype = Block_Type::Pig;
	}
	else if (_Set == 6)
	{
		Blocktype = Block_Type::Rabbit;
	}	
}

void ABase_Block::BeginPlay()
{
	AActor::BeginPlay();
}

void ABase_Block::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	PickingCheck();
	CheckBoombBlockEffect();
}

void ABase_Block::CreateBlockEffect()
{	
	Block_Destroy_Effect = GetWorld()->SpawnActor<ABlockBoomb_Effect>();
	Block_Destroy_Effect->SetActorLocation(GetActorLocation());
}

void ABase_Block::PickingCheck()
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
			if (Blocktype == Block_Type::Bomb)
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

void ABase_Block::CheckBoombBlockEffect()
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
