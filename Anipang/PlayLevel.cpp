#include "PlayLevel.h"
#include <EngineCore\EngineCore.h>
#include "Cursor.h"
#include "FadeIN_OUT.h"
#include "Play_Frame.h"
#include "Cat_Block.h"

#include "Block_Manager.h"

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();
	SpawnActor<APlay_Frame>();	
	Cursoor = SpawnActor<ACursor>();
}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('N'))
	{
		GEngine->ChangeLevel("Ending");
	}
}

void UPlayLevel::LevelStart(ULevel* _Level)
{
    SpawnActor<AFadeIN_OUT>();
    //OBJPOOLTEST();
    CreateBlock();
    

}

void UPlayLevel::LevelEnd(ULevel* _Level)
{
}

void UPlayLevel::OBJPOOLTEST()
{
    Block_Manager::OBJPOOL->BeginPlay();

    const int GridSize = 7;
    const int TotalBlocks = GridSize * GridSize;
    const int CellSize = 67;
    const FVector StartLocation({ 32, 214 });

    for (int row = 0; row < GridSize; ++row)
    {
        for (int col = 0; col < GridSize; ++col)
        {
            // ������ ���� ����� ���� ����
            Block_Manager::eBlock blockType;
            if (col >= GridSize - 7 && row >= GridSize - 7) // ������ �Ʒ� 7x7 ����
            {
                blockType = Block_Manager::eBlock::Cat_Block;
            }
            else
            {
                // �ٸ� ���� ��� ���� ����
                // ���� ��� Dog_Block, Checkin_Block ��
                // �ʿ信 ���� ���� �߰�
            }

            // ���� ��� ����
            AAnimal_Block* NewBlock = Block_Manager::GetInstance().GetNextAnimalBlock(blockType);


            if (NewBlock != nullptr)
            {
                // ���� ��� ��ġ ����
                FVector BlockLocation;
                BlockLocation.X = StartLocation.X + (CellSize * col);  // ���� ��ġ���� CellSize��ŭ �̵�
                BlockLocation.Y = StartLocation.Y + (CellSize * row);
                NewBlock->SetActorLocation(BlockLocation);
                NewBlock->SetCursor(Cursoor);
                NewBlock->SetActive(true);
                // ���� ��� ����
                //SpawnActor<AAnimal_Block>(NewBlock);
            }
        }
    }
}

void UPlayLevel::CreateBlock()
{
    const int GridSize = 7;
    const int TotalBlocks = GridSize * GridSize;
    const int CellSize = 67;
    const FVector StartLocation({ 32, 214 });

    for (int row = 0; row < GridSize; ++row)
    {
        for (int col = 0; col < GridSize; ++col)
        {
            // ���� ��� ����
            AAnimal_Block* NewBlock = SpawnActor<ACat_Block>();
            FVector BlockLocation;     // ���� ��� ��ġ ����
            BlockLocation.X = StartLocation.X + (CellSize * col);  // ���� ��ġ���� CellSize��ŭ �̵�
            BlockLocation.Y = StartLocation.Y + (CellSize * row);
            NewBlock->SetActorLocation(BlockLocation);
            NewBlock->SetCursor(Cursoor);                          
        }
    }
}
