#include "Monkey_Block.h"


AMonkey_Block::AMonkey_Block()
{
}

AMonkey_Block::~AMonkey_Block()
{
}

void AMonkey_Block::BeginPlay()
{
	ABase_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Monkey");
	Renderer->SetTransform({ {0,0}, {75, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Monkey", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("Click", "Monkey", 1, 1, 1.1f, true);
	Renderer->CreateAnimation("Bomb", "Monkey", 0, 2, 0.1f, false);
	Renderer->ChangeAnimation("Idle");
	Blocktype = Block_Type::Monkey;
}

void AMonkey_Block::Tick(float _DeltaTime)

{
	ABase_Block::Tick(_DeltaTime);
	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();

	switch (Blockstatus)
	{
	case ABase_Block::Block_Status::Idle:
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
			CreateBlockEffect();
			UEngineSound::SoundPlay("Block_BOOM.mp3");
			Renderer->ChangeAnimation("Bomb");
			Blockstatus = Block_Status::Bomb;
			FindEnd = true;
			return;
		}

		if (UnderBlockBoomb == true)
		{
			Blockstatus = Block_Status::Move;
			return;
		}

		if (LetsFind == true)
		{
			Blockstatus = Block_Status::Find;
			return;
		}
	}
	break;
	case ABase_Block::Block_Status::Move:
	{
		if (Pos.Y >= UnderPos.Y)
		{
			SetUnderBoomb(false);
			Pos.Y = UnderPos.Y;
			Blockstatus = Block_Status::Idle;
			return;
		}
		AddActorLocation({ FVector::Down * DownSpeed * _DeltaTime });
	}
	break;
	case ABase_Block::Block_Status::Click:
	{

		if (BlockClick == false)
		{
			Renderer->ChangeAnimation("Idle");
			Blockstatus = Block_Status::Idle;
			int RenderNumber = 1;
			Renderer->SetOrder(RenderNumber);

			if (SecondPick == true)
			{
				SecondClick = false;
				SecondPick = false;
			}
			if (FirstPick == true)
			{
				FirstClick = false;
				FirstPick = false;
			}

			return;
		}

		if (BoombBlock == true)
		{
			CreateBlockEffect();
			UEngineSound::SoundPlay("Block_BOOM.mp3");
			Renderer->ChangeAnimation("Bomb");
			Blockstatus = Block_Status::Bomb;
			FindEnd = true;
			return;
		}
	}
	break;
	case ABase_Block::Block_Status::Bomb:
	{

		bool AnimationEnd = Renderer->IsCurAnimationEnd();
		if (AnimationEnd == true)
		{
			/*CreateBlockEffect();*/
			FindEnd = true;
			Destroy(0.f);
		}
	}
	break;

	case ABase_Block::Block_Status::Find:
	{
		FindTime += _DeltaTime;
		if (1.f <= FindTime)
		{
			AlphaBlend = !AlphaBlend;
			FindTime = 0.0f;
		}
		if (true == AlphaBlend)
		{
			Renderer->SetAlpha(FindTime * 0.45f);
		}
		else
		{
			Renderer->SetAlpha(1.0f - FindTime);
		}

		if (LetsFind == false)
		{
			Blockstatus = Block_Status::Idle;
			Renderer->SetAlpha(1.0f);
			return;
		}

		if (BlockClick == true)
		{
			Renderer->ChangeAnimation("Click");
			Blockstatus = Block_Status::Click;
			int RenderNumber = 2;
			Renderer->SetOrder(RenderNumber);
			Renderer->SetAlpha(1.0f);
			FindEnd = true;
			LetsFind = false;
			return;
		}

		if (BoombBlock == true)
		{
			CreateBlockEffect();
			UEngineSound::SoundPlay("Block_BOOM.mp3");
			Renderer->ChangeAnimation("Bomb");
			Blockstatus = Block_Status::Bomb;
			Renderer->SetAlpha(1.0f);
			FindEnd = true;
			return;
		}

		if (UnderBlockBoomb == true)
		{
			Blockstatus = Block_Status::Move;
			Renderer->SetAlpha(1.0f);
			FindEnd = true;
			LetsFind = false;
			return;
		}
	}
	break;

	case ABase_Block::Block_Status::End:
		break;
	default:
		break;
	}
}
