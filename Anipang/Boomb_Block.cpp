#include "Boomb_Block.h"
#include "BoombBlock_Effect.h"


ABoomb_Block::ABoomb_Block()
{
}

ABoomb_Block::~ABoomb_Block()
{
}

void ABoomb_Block::BeginPlay()
{
	AAnimal_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("boom.png");
	Renderer->SetTransform({ {0,0}, {55, 55} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	//Renderer->CreateAnimation("Idle", "Cat", 0, 0, 1.1f, true);
	//Renderer->CreateAnimation("Click", "Cat", 1, 1, 1.1f, true);
	//Renderer->CreateAnimation("Boomb", "Cat", 0, 2, 0.1f, false);
	//Renderer->ChangeAnimation("Idle");
	Blocktype = Block_Type::Boomb;
}

void ABoomb_Block::Tick(float _DeltaTime)
{
	AAnimal_Block::Tick(_DeltaTime);
	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();

	CollCheck_First_Effect();

	Check_Second_Destroy();

	switch (Blockstatus)
	{
	case AAnimal_Block::Block_Status::Idle:
	{
		if (BlockClick == true)
		{
			Blockstatus = Block_Status::Click;
			Create_First_Effect();
			// ������Ʈ ����� Ŭ������ ����������.
			BlockClick = false;

			return;
			// �غ�����Ʈ ������ ����(�������)
			// ������Ʈ�� ���� ����� ��ġ���� ���������� ó���ϸ�.
			// ���� �������� �� �ٸ� ����Ʈ�� �����Ѵ�.
			// 
			// => ����1. ��ź���� Ŭ���ϸ� ��ź���� ������X�� ��ǥ�� ���ʿ��� ù ����Ʈ�� ���������̴�.
			// => ����2. ù ����Ʈ�� ��ź���� ������������ �ٸ����� �����ٸ� �ٸ������� �������̴�.
			// => ����3. ��ź���� ù ����Ʈ�� �����ٸ� �ι�° ����Ʈ���� �����ϰ� �Ǹ� ��ź�� ��ġ������ 3����, 2����, 1���� ���� �����Ǿ� �߻�ɰ��̴�.
			// => ����4. ��ź���� ������ �ִٸ� ���� �������� �� �ݴ� �������θ� ����Ʈ ���� �� �߻��Ѵ�.
			// => ����5. ��ź���� ���� �پ����� �ʴٸ� ���� �������� �������� �߻� �����ϴ�.
			// => ����6. ��ź���� �߾ӿ� �ִٸ� �Ʒ�����, �翷�������� ����Ʈ�� ���� �� �߻��Ѵ�.
			// => ����7. �ι�° ����Ʈ�鵵 �ٸ����� ������ �Ǹ� �ٸ������� �������̴�.		}
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
	case AAnimal_Block::Block_Status::Click:
	{
		if (BoombBlock == true)
		{
			Blockstatus = Block_Status::Boomb;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Boomb:
	{
		// �պ��� �������� ����Ʈ �������븸�̴�.
		// �պ��� �÷��̷������� Destroycheck�� ������ ��Ȳ�� ������ ���� ó�� �Ұ�!
		CreateBlockEffect();
		Destroy(0.f);
		return;
	}
	break;
	case AAnimal_Block::Block_Status::End:
		break;
	default:
		break;
	}


	
}

void ABoomb_Block::Create_First_Effect()
{
	BoombBlock_First_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
	int col = GetBlockLocationCol();
	int row = 0;
	FVector SetPos = GetBlockFVector(col, row);

	int a = 0;
	BoombBlock_First_Effect->SetActorLocation(SetPos);
	BoombBlock_First_Effect->SetDir(FVector::Down);
	BoombBlock_FirstEffect_Create = true;
	FirstEffect_Create = true;
}


void ABoomb_Block::CollCheck_First_Effect()
{
	if (BoombBlock_FirstEffect_Create == true)
	{
		if (FirstEffect_Create == true)
		{
			BoombBlock_First_Effect_Pos = BoombBlock_First_Effect->GetActorLocation();

			float MinX = Pos.X - Size.X / 2;
			float MinY = Pos.Y - Size.Y / 2;
			float MaxX = Pos.X + Size.X / 2;
			float MaxY = Pos.Y + Size.Y / 2;
			int a = 0;
			if (BoombBlock_First_Effect_Pos.X >= MinX && BoombBlock_First_Effect_Pos.X <= MaxX && BoombBlock_First_Effect_Pos.Y - 75.f >= MinY && BoombBlock_First_Effect_Pos.Y - 75.f <= MaxY)
			{
				// �ݸ��� üũ �ϸ鼭 ������� row�� col�� �޾Ƽ� ������ �ް�.
				// row�� col�� ��ġ������ left���� right����, down���� ���ؼ� ����� �����ٰ�.
				
				int Row = GetBlockLocationRow();
				int Col = GetBlockLocationCol();

				int a = 0;


				if (Col == 0 && Row == 6)
				{
					BoombBlock_Right_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
					BoombBlock_Right_Effect_Pos = GetActorLocation();
					BoombBlock_Right_Effect->SetActorLocation(BoombBlock_Right_Effect_Pos);
					BoombBlock_Right_Effect->SetDir(FVector::Right);
					BoombBlock_Right_Effect->SetSideReder();
					BoombBlock_SecondEffect_Create = true;
				}
				else if (Row == 6 && Col == 6)
				{
					BoombBlock_Left_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
					BoombBlock_Left_Effect_Pos = GetActorLocation();
					BoombBlock_Left_Effect->SetActorLocation(BoombBlock_Left_Effect_Pos);
					BoombBlock_Left_Effect->SetDir(FVector::Left);
					BoombBlock_Left_Effect->SetSideReder();
					BoombBlock_SecondEffect_Create = true;
				}
				else if (Col == 0)
				{
					{
						BoombBlock_Right_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Right_Effect_Pos = GetActorLocation();
						BoombBlock_Right_Effect->SetActorLocation(BoombBlock_Right_Effect_Pos);
						BoombBlock_Right_Effect->SetDir(FVector::Right);
						BoombBlock_Right_Effect->SetSideReder();
					}

					{
						BoombBlock_Down_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Down_Effect_Pos = GetActorLocation();
						BoombBlock_Down_Effect->SetActorLocation(BoombBlock_Down_Effect_Pos);
						BoombBlock_Down_Effect->SetDir(FVector::Down);
					}
					BoombBlock_SecondEffect_Create = true;
				}
				else if (Col == 6)
				{
					{
						BoombBlock_Left_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Left_Effect_Pos = GetActorLocation();
						BoombBlock_Left_Effect->SetActorLocation(BoombBlock_Left_Effect_Pos);
						BoombBlock_Left_Effect->SetDir(FVector::Left);
						BoombBlock_Left_Effect->SetSideReder();
					}
					{
						BoombBlock_Down_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Down_Effect_Pos = GetActorLocation();
						BoombBlock_Down_Effect->SetActorLocation(BoombBlock_Down_Effect_Pos);
						BoombBlock_Down_Effect->SetDir(FVector::Down);
					}
					BoombBlock_SecondEffect_Create = true;
				}
				else if (Row == 6)
				{
					{
						BoombBlock_Left_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Left_Effect_Pos = GetActorLocation();
						BoombBlock_Left_Effect->SetActorLocation(BoombBlock_Left_Effect_Pos);
						BoombBlock_Left_Effect->SetDir(FVector::Left);
						BoombBlock_Left_Effect->SetSideReder();
					}

					{
						BoombBlock_Right_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Right_Effect_Pos = GetActorLocation();
						BoombBlock_Right_Effect->SetActorLocation(BoombBlock_Right_Effect_Pos);
						BoombBlock_Right_Effect->SetDir(FVector::Right);
						BoombBlock_Right_Effect->SetSideReder();
					}
					BoombBlock_SecondEffect_Create = true;
				}

				else
				{
					{
						BoombBlock_Right_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Right_Effect_Pos = GetActorLocation();
						BoombBlock_Right_Effect->SetActorLocation(BoombBlock_Right_Effect_Pos);
						BoombBlock_Right_Effect->SetDir(FVector::Right);
						BoombBlock_Right_Effect->SetSideReder();
					}

					{
						BoombBlock_Left_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Left_Effect_Pos = GetActorLocation();
						BoombBlock_Left_Effect->SetActorLocation(BoombBlock_Left_Effect_Pos);
						BoombBlock_Left_Effect->SetDir(FVector::Left);
						BoombBlock_Left_Effect->SetSideReder();
					}

					{
						BoombBlock_Down_Effect = GetWorld()->SpawnActor<ABoombBlock_Effect>();
						BoombBlock_Down_Effect_Pos = GetActorLocation();
						BoombBlock_Down_Effect->SetActorLocation(BoombBlock_Down_Effect_Pos);
						BoombBlock_Down_Effect->SetDir(FVector::Down);
					}
					BoombBlock_SecondEffect_Create = true;
				}

				BoombBlock_First_Effect->Destroy(0.0f);
				BoombBlock_First_Effect = nullptr;
				BoombBlock_FirstEffect_Create = false;
				BoombBlock_First_Toutch = true;
			}
		}
	}
}

void ABoomb_Block::Check_Second_Destroy()
{
	if (BoombBlock_Left_Effect != nullptr)
	{
		if (BoombBlock_Left_Effect->IsSecondEffectDEATH() == true)
		{
			BoombBlock_Left_Effect->Destroy(0.f);
			BoombBlock_Left_Effect = nullptr;
		}
	}
	if (BoombBlock_Right_Effect != nullptr)
	{
		if (BoombBlock_Right_Effect->IsSecondEffectDEATH() == true)
		{
			BoombBlock_Right_Effect->Destroy(0.f);
			BoombBlock_Right_Effect = nullptr;
		}
	}
	if (BoombBlock_Down_Effect != nullptr)
	{
		if (BoombBlock_Down_Effect_Pos.Y >=685.f)
		{
			BoombBlock_Down_Effect->Destroy(0.f);
			BoombBlock_Down_Effect = nullptr;
		}
	}
}

