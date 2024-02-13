#include "Checkin_Block.h"

ACheckin_Block::ACheckin_Block()
{
}

ACheckin_Block::~ACheckin_Block()
{
}

void ACheckin_Block::BeginPlay()
{
	AAnimal_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Checkin");
	Renderer->SetTransform({ {0,0}, {75, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Checkin", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("Click", "Checkin", 1, 1, 1.1f, true);
	Renderer->CreateAnimation("Boomb", "Checkin", 0, 2, 0.1f, false);
	Renderer->ChangeAnimation("Idle");
	Blocktype = Block_Type::Checkin;

}

void ACheckin_Block::Tick(float _DeltaTime)
{
	AAnimal_Block::Tick(_DeltaTime);
	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();

	switch (Blockstatus)
	{
	case AAnimal_Block::Block_Status::Idle:
	{
		if (BlockClick == true)
		{
			Renderer->ChangeAnimation("Click");
			Blockstatus = Block_Status::Click;
			int RenderNumber = 2;
			Renderer->SetOrder(RenderNumber);
			return;
		}

		if (BoombBlock == true)
		{
			Renderer->ChangeAnimation("Boomb");
			Blockstatus = Block_Status::Boomb;
			return;
		}

		if (UnderBlockBoomb == true)
		{
			Blockstatus = Block_Status::Move;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Move:
	{
		AddActorLocation({ FVector::Down * 150.0f * _DeltaTime });
		if (Pos.Y > UnderPos.Y)
		{
			SetUnderBoomb(false);
			Pos.Y = UnderPos.Y;
			Blockstatus = Block_Status::Idle;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Click:
	{
		if (BlockClick == false)
		{
			Renderer->ChangeAnimation("Idle");
			Blockstatus = Block_Status::Idle;
			int RenderNumber = 1;
			Renderer->SetOrder(RenderNumber);
			return;
		}

		if (BoombBlock == true)
		{
			Renderer->ChangeAnimation("Boomb");
			Blockstatus = Block_Status::Boomb;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Boomb:
	{
		bool AnimationEnd = Renderer->IsCurAnimationEnd();
		if (AnimationEnd == true)
		{
			CreateBlockEffect();
			Destroy(0.f);
		}
	}
	break;
	case AAnimal_Block::Block_Status::End:
		break;
	default:
		break;
	}
}
