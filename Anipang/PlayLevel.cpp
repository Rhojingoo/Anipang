#include "PlayLevel.h"
#include <EngineCore\EngineCore.h>
#include "Cursor.h"
#include "FadeIN_OUT.h"
#include "Play_Frame.h"
#include "Cat_Block.h"
#include "Checkin_Block.h"
#include "Dog_Block.h"
#include "Mouse_Block.h"
#include "Monkey_Block.h"
#include "Pig_Block.h"
#include "Rabbit_Block.h"
#include "Helper.h"


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


    if (AAnimal_Block::GetFirstClick() == true && AAnimal_Block::GetSecondClick() == true)
    {
        static FVector Clickpos;
        static FVector Swappos;
       static FVector TempClick;
       static FVector TempSwap;

        if (AAnimal_Block::SwapREADY == false)
        {
            const int MapSize = 7;
            for (int row = 0; row < MapSize; row++)
            {
                for (int col = 0; col < MapSize; col++)
                {
                    if (Blocks[col][row]->GetFirstPick() == true)
                    {
                        click_block = Blocks[col][row];
                        Clickpos = click_block->GetActorLocation();                        
                    }

                    if (Blocks[col][row]->GetSecondPick() == true)
                    {
                        swap_block = Blocks[col][row];
                        Swappos = swap_block->GetActorLocation();                        
                    }
                }               
            }
            TempClick = Clickpos;
            TempSwap = Swappos;
            AAnimal_Block::SwapREADY = true;
        }
        else
        {
            Clickpos = click_block->GetActorLocation();
            Swappos = swap_block->GetActorLocation();
            if (Clickpos.X <= TempSwap.X)
            {
                click_block->AddActorLocation({ FVector::Right * 150.0f * _DeltaTime });
            }
            else
            {
                AAnimal_Block::ClickChange = true;
            }

            if (Swappos.X >= TempClick.X)
            {
                swap_block->AddActorLocation(FVector::Left * 150.0f * _DeltaTime);
            }
            else
            {
                AAnimal_Block::SwapChange = true;
            }


            if (AAnimal_Block::SwapChange == true && AAnimal_Block::ClickChange == true)
            {
                bool _set = false;
                click_block->SetBlockstate(_set, 1);
                swap_block->SetBlockstate(_set, 2);
                AAnimal_Block::SwapREADY = false;
                AAnimal_Block::SwapChange = false;
                AAnimal_Block::ClickChange = false;
            }
       
        }
    }


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

    const int MapSize = 7;
    const int TotalBlocks = MapSize * MapSize;
    const int CellSize = 67;
    const FVector StartLocation({ 32, 214 });

    for (int row = 0; row < MapSize; ++row)
    {
        for (int col = 0; col < MapSize; ++col)
        {
            // 생성할 동물 블록의 유형 결정
            Block_Manager::eBlock blockType;
            if (col >= MapSize - 7 && row >= MapSize - 7) // 오른쪽 아래 7x7 영역
            {
                blockType = Block_Manager::eBlock::Cat_Block;
            }
            else
            {
                // 다른 동물 블록 유형 결정
                // 예를 들어 Dog_Block, Checkin_Block 등
                // 필요에 따라 로직 추가
            }

            // 동물 블록 생성
            AAnimal_Block* NewBlock = Block_Manager::GetInstance().GetNextAnimalBlock(blockType);


            if (NewBlock != nullptr)
            {
                // 동물 블록 위치 설정
                FVector BlockLocation;
                BlockLocation.X = StartLocation.X + (CellSize * col);  // 시작 위치에서 CellSize만큼 이동
                BlockLocation.Y = StartLocation.Y + (CellSize * row);
                NewBlock->SetActorLocation(BlockLocation);
                NewBlock->SetCursor(Cursoor);
                NewBlock->SetActive(true);
                // 동물 블록 스폰
                //SpawnActor<AAnimal_Block>(NewBlock);
            }
        }
    }
}

void UPlayLevel::CreateBlock()
{
    const int MapSize = 7;
    const int TotalBlocks = MapSize * MapSize;
    const int CellSize = 67;
    const FVector StartLocation({ 32, 214 });

    for (int row = 0; row < MapSize; ++row)
    {
        for (int col = 0; col < MapSize; ++col)
        {
            // 동물 블록 생성
            int random = 0;
            random = UHelper::Random(0,6);     
            if (random == 0)
            {
                Blocks[col][row] = SpawnActor<ACat_Block>();
            }
            else if (random == 1)
            {
                Blocks[col][row] = SpawnActor<ACheckin_Block>();
            }
            else if (random == 2)
            {
               Blocks[col][row] = SpawnActor<ADog_Block>();
            }
            else if (random == 3)
            {
                Blocks[col][row] = SpawnActor<AMonkey_Block>();
            }
            else if (random == 4)
            {
                Blocks[col][row] = SpawnActor<AMouse_Block>();
            }
            else if (random == 5)
            {
                Blocks[col][row] = SpawnActor<APig_Block>();
            }
            else if (random == 6)
            {
                Blocks[col][row] = SpawnActor<ARabbit_Block>();
            }          

            FVector BlockLocation;     // 동물 블록 위치 설정
            BlockLocation.X = StartLocation.X + (CellSize * col);  // 시작 위치에서 CellSize만큼 이동
            BlockLocation.Y = StartLocation.Y + (CellSize * row);
            Blocks[col][row]->SetActorLocation(BlockLocation);
            Blocks[col][row]->SetCursor(Cursoor);
            Blocks[col][row] ->SetColumn(col);
            Blocks[col][row]->SetRow(row);
        }
    }
}
