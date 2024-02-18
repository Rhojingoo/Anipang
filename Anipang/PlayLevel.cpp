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
#include "Game_End.h"
#include "Game_Start.h"
#include "Time_Gauge.h"
#include "Number.h"
#include "ScoreManager.h"


#include "Boomb_Block_Effect.h"

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
	Cursor = SpawnActor<ACursor>();
    Start_Rabbit = SpawnActor<AGame_Start>();
    Start_Rabbit->SetActorLocation({ 235,400 });

    //ABoomb_Block_Effect* aTEST = SpawnActor<ABoomb_Block_Effect>();
    //aTEST->SetActorLocation({ 235,400 });

    Timer = SpawnActor<ATime_Gauge>();
    Timer->SetActorLocation({ 231,705 });

    ScoreMN = SpawnActor<ScoreManager>();
}

void UPlayLevel::Tick(float _DeltaTime)
{
    ULevel::Tick(_DeltaTime);


    if (GameStart == false)
    {
        GameStart = Start_Rabbit->IsStart();
    }
    else
    {
        Timer->TimerStart();
        if (Timer->IsFinish() == true)
        {
            if (GameEnd == false)
            {
                End_Rabbit = SpawnActor<AGame_End>();
                End_Rabbit->SetActorLocation({ 250,400 });
                GameEnd = true;
            }
        }
        else
        {
            if (AAnimal_Block::GetFirstClick() == true && AAnimal_Block::GetSecondClick() == true)
            {
                BlockClickUpdate(_DeltaTime);
            }

            //클릭으로 이동된 블럭 3Match가 되는지 판단하는 검사로직
            XlineBlock_Swap_Check(_DeltaTime);
            YlineBlock_Swap_Check(_DeltaTime);


            //검사된 블럭의 return 또는 stay를 나타내는 실행로직
            XlineBlock_Swap_Move(_DeltaTime);
            YlineBlock_Swap_Move(_DeltaTime);          


            BlockDestroyCheck();
            BlockMove();
            GenerateNewBlocks();
        }





        // 검사 로직이 되는것을 확인필요.
        //{
        //}
        // 만약 검사가 통과못했다면 [bool Blockreturn false값을 주어서 이용할것]
        // {
        // }  
        // 만약 검사에 통과못했다면 [bool Blockreturn false값일때 사용이부분진행]              
        // 클릭한거 이동한뒤 match가 안되면 되돌아가는 로직 짜기  
        // {
        // }
        // 만약 검사가 통과했다면 [bool Blockreturn true값일때 사용이부분진행]              

    }




    ScoreMN->SetScore(Score);

    if (UEngineInput::IsDown('N'))
    {
        GEngine->ChangeLevel("GetScore");
    }
}

void UPlayLevel::LevelStart(ULevel* _Level)
{
    Score = ScoreManager::GetScore();
    SpawnActor<AFadeIN_OUT>();
    //OBJPOOLTEST();
    CreateBlock();
    Start_Rabbit = SpawnActor<AGame_Start>();
    Start_Rabbit->SetActorLocation({ 235,400 });

}

void UPlayLevel::LevelEnd(ULevel* _Level)
{
    for (int row = 0; row < MapSize; ++row)
    {
        for (int col = 0; col < MapSize; ++col)
        {         
            if (Blocks[col][row] == nullptr)
            {
                continue;
            }

            Blocks[col][row]->Destroy(0.f);
            Blocks[col][row] = nullptr;
        }
    }
    Timer->Finishreturn();
    GameEnd = false;
    GameStart = false;
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
                NewBlock->SetCursor(Cursor);
                NewBlock->SetActive(true);
                // 동물 블록 스폰
                //SpawnActor<AAnimal_Block>(NewBlock);
            }
        }
    }
}

void UPlayLevel::CreateBlock()
{
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
            Blocks[col][row]->SetCursor(Cursor);
            Blocks[col][row]->SetColumn(col);
            Blocks[col][row]->SetRow(row);
        }
    }
}

void UPlayLevel::XlineBlock_Swap_Check(float _DeltaTime)
{
    if (XSWAPMOVE == true && XCLICKMOVE == true)
    {
        int clickRow = click_block->GetBlockLocation().Row;
        for (int col = 1; col < MapSize - 1; col++)
        {
            AAnimal_Block* CheckBlock = Blocks[col][clickRow];
            FVector CheckBlockpos = CheckBlock->GetActorLocation();
            AAnimal_Block* XLine_Check_Before = Blocks[col - 1][clickRow];
            AAnimal_Block* XLine_Check_After = Blocks[col + 1][clickRow];

            if (Blocks[col][clickRow] == nullptr || Blocks[col - 1][clickRow] == nullptr || Blocks[col + 1][clickRow] == nullptr)
            {
                continue;
            }

            if (XLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (col >= 5)
                {
                    XLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            if (XLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (col >= 5)
                {
                    XLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            XLINE_ChageCheck = BlockChangeSuccess;
            return;
        }

        int clickCol = click_block->GetBlockLocation().Column;
        for (int Row = 1; Row < MapSize - 1; Row++)
        {
            AAnimal_Block* CheckBlock = Blocks[clickCol][Row];
            FVector CheckBlockpos = CheckBlock->GetActorLocation();
            AAnimal_Block* YLine_Check_Before = Blocks[clickCol][Row - 1];
            AAnimal_Block* YLine_Check_After = Blocks[clickCol][Row + 1];

            if (Blocks[clickCol][Row] == nullptr || Blocks[clickCol][Row - 1] == nullptr || Blocks[clickCol][Row + 1] == nullptr)
            {
                continue;
            }

            if (YLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (Row >= 5)
                {
                    XLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            if (YLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (Row >= 5)
                {
                    XLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            XLINE_ChageCheck = BlockChangeSuccess;
            return;
        }

        int swapCol = swap_block->GetBlockLocation().Column;
        for (int Row = 1; Row < MapSize - 1; Row++)
        {
            AAnimal_Block* CheckBlock = Blocks[swapCol][Row];
            FVector CheckBlockpos = CheckBlock->GetActorLocation();
            AAnimal_Block* YLine_Check_Before = Blocks[swapCol][Row - 1];
            AAnimal_Block* YLine_Check_After = Blocks[swapCol][Row + 1];

            if (Blocks[swapCol][Row] == nullptr || Blocks[swapCol][Row - 1] == nullptr || Blocks[swapCol][Row + 1] == nullptr)
            {
                continue;
            }

            if (YLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (Row >= 5)
                {
                    XLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            if (YLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (Row >= 5)
                {
                    XLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            XLINE_ChageCheck = BlockChangeSuccess;
            return;
        }
    }
}

void UPlayLevel::XlineBlock_Swap_Move(float _DeltaTime)
{
    if (XLINE_ChageCheck == BlockChangeFail)     // 검사 실패라면
    {
        Clickpos = click_block->GetActorLocation();
        Swappos = swap_block->GetActorLocation();
        static bool LeftMoveBl = false;
        static bool RightMoveBl = false;

        if (LeftMoveBl == false && RightMoveBl == false)
        {
            float VSX = Clickpos.X - TempClick.X;
            if (VSX >= 0.f)
            {
                LeftMoveBl = true;
            }
            else
            {
                RightMoveBl = true;
            }
        }

        if (RightMoveBl == true)
        {
            if (Clickpos.X <= TempClick.X)
            {
                click_block->AddActorLocation({ FVector::Right * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });
            }

            if (Swappos.X >= TempSwap.X)
            {
                swap_block->AddActorLocation(FVector::Left * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempSwap });
                XlinemoveCheck = true;
            }
        }
        else if (LeftMoveBl == true)
        {
            if (Clickpos.X >= TempClick.X)
            {
                click_block->AddActorLocation({ FVector::Left * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });

            }

            if (Swappos.X <= TempSwap.X)
            {
                swap_block->AddActorLocation(FVector::Right * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempSwap });
                XlinemoveCheck = true;
            }
        }

        if (XlinemoveCheck == true)
        {
            LeftMoveBl = false;
            RightMoveBl = false;
            XCLICKMOVE = false;
            XSWAPMOVE = false;
            XLINE_ChageCheck = BlockChangeDefault;


            int clickRow = click_block->GetBlockLocation().Row;
            int clickCol = click_block->GetBlockLocation().Column;
            int swapkRow = swap_block->GetBlockLocation().Row;
            int swapCol = swap_block->GetBlockLocation().Column;

            bool _set = false;
            click_block->SetBlockstate(_set, 1);
            swap_block->SetBlockstate(_set, 2);
            click_block->SetColumn(swapCol);
            click_block->SetRow(swapkRow);
            swap_block->SetColumn(clickCol);
            swap_block->SetRow(clickRow);

            AAnimal_Block* XLine_Temp = Blocks[clickCol][clickRow];
            Blocks[clickCol][clickRow] = Blocks[swapCol][swapkRow];
            Blocks[swapCol][swapkRow] = XLine_Temp;
            XlinemoveCheck = false;
        }
    }
    else if (XLINE_ChageCheck == BlockChangeSuccess)   // 검사 성공
    {
        XLINE_ChageCheck = BlockChangeDefault;
        XCLICKMOVE = false;
        XSWAPMOVE = false;
    }
}

void UPlayLevel::YlineBlock_Swap_Check(float _DeltaTime)
{
    if (YSWAPMOVE == true && YCLICKMOVE == true)
    {
        int clickCol = click_block->GetBlockLocation().Column;
        for (int row = 1; row < MapSize - 1; row++)
        {
            AAnimal_Block* CheckBlock = Blocks[clickCol][row];
            FVector CheckBlockpos = CheckBlock->GetActorLocation();
            AAnimal_Block* YLine_Check_Before = Blocks[clickCol][row-1];
            AAnimal_Block* YLine_Check_After = Blocks[clickCol][row+1];


            if (Blocks[clickCol][row] == nullptr || Blocks[clickCol][row-1] == nullptr || Blocks[clickCol][row+1] == nullptr)
            {
                continue;
            }

            if (YLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (row >= 5)
                {
                    YLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            if (YLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (row >= 5)
                {
                    YLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            YLINE_ChageCheck = BlockChangeSuccess;
            return;
        }


        int SwapRow = swap_block->GetBlockLocation().Row;
        for (int col = 1; col < MapSize - 1; col++)
        {
            AAnimal_Block* CheckBlock = Blocks[col][SwapRow];
            FVector CheckBlockpos = CheckBlock->GetActorLocation();
            AAnimal_Block* XLine_Check_Before = Blocks[col - 1][SwapRow];
            AAnimal_Block* XLine_Check_After = Blocks[col + 1][SwapRow];

            if (Blocks[col][SwapRow] == nullptr || Blocks[col - 1][SwapRow] == nullptr || Blocks[col + 1][SwapRow] == nullptr)
            {
                continue;
            }

            if (XLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (col >= 5)
                {
                    YLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            if (XLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (col >= 5)
                {
                    YLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            YLINE_ChageCheck = BlockChangeSuccess;
            return;
        }



        int ClickRow = click_block->GetBlockLocation().Column;
        for (int col = 1; col < MapSize - 1; col++)
        {
            AAnimal_Block* CheckBlock = Blocks[col][ClickRow];
            FVector CheckBlockpos = CheckBlock->GetActorLocation();
            AAnimal_Block* XLine_Check_Before = Blocks[col-1][ClickRow];
            AAnimal_Block* XLine_Check_After = Blocks[col+1][ClickRow];

            if (Blocks[col][ClickRow] == nullptr || Blocks[col-1][ClickRow] == nullptr || Blocks[col+1][ClickRow] == nullptr)
            {
                continue;
            }

            if (XLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (col >= 5)
                {
                    YLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            if (XLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            {
                if (col >= 5)
                {
                    YLINE_ChageCheck = BlockChangeFail;
                }
                continue;
            }
            YLINE_ChageCheck = BlockChangeSuccess;
            return;
        }
    }
}

void UPlayLevel::YlineBlock_Swap_Move(float _DeltaTime)
{
    if (YLINE_ChageCheck == BlockChangeFail)     // 검사 실패라면
    {
        Clickpos = click_block->GetActorLocation();
        Swappos = swap_block->GetActorLocation();
        static bool UpMoveBl = false;
        static bool DownMoveBl = false;

        if (UpMoveBl == false && DownMoveBl == false)
        {
            float VSX = Clickpos.Y - TempClick.Y;
            if (VSX >= 0.f)
            {
                DownMoveBl = true; 
            }
            else
            {
                UpMoveBl = true;
            }
        }

        if (UpMoveBl == true)
        {
            if (Clickpos.Y <= TempClick.Y)
            {
                click_block->AddActorLocation({ FVector::Down * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });
            }

            if (Swappos.Y >= TempSwap.Y)
            {
                swap_block->AddActorLocation(FVector::Up * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempSwap });
                YlinemoveCheck = true;
            }
        }
        else if (DownMoveBl == true)
        {
            if (Clickpos.Y >= TempClick.Y)
            {
                click_block->AddActorLocation({ FVector::Up * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });

            }

            if (Swappos.Y <= TempSwap.Y)
            {
                swap_block->AddActorLocation(FVector::Down * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempSwap });
                YlinemoveCheck = true;
            }
        }

        if (YlinemoveCheck == true)
        {
            UpMoveBl = false;
            DownMoveBl = false;
            YCLICKMOVE = false;
            YSWAPMOVE = false;
            YLINE_ChageCheck = BlockChangeDefault;


            int clickRow = click_block->GetBlockLocation().Row;
            int clickCol = click_block->GetBlockLocation().Column;
            int swapkRow = swap_block->GetBlockLocation().Row;
            int swapCol = swap_block->GetBlockLocation().Column;

            bool _set = false;
            click_block->SetBlockstate(_set, 1);
            swap_block->SetBlockstate(_set, 2);
            click_block->SetColumn(swapCol);
            click_block->SetRow(swapkRow);
            swap_block->SetColumn(clickCol);
            swap_block->SetRow(clickRow);

            AAnimal_Block* XLine_Temp = Blocks[clickCol][clickRow];
            Blocks[clickCol][clickRow] = Blocks[swapCol][swapkRow];
            Blocks[swapCol][swapkRow] = XLine_Temp;
            YlinemoveCheck = false;
        }
    }
    else if (YLINE_ChageCheck == BlockChangeSuccess)   // 검사 성공
    {
        YLINE_ChageCheck = BlockChangeDefault;
        YCLICKMOVE = false;
        YSWAPMOVE = false;
    }
}

void UPlayLevel::BlockClickUpdate(float _DeltaTime)
{
 /*   static FVector Clickpos;
    static FVector Swappos;
    static FVector TempClick;
    static FVector TempSwap;*/

    if (AAnimal_Block::SwapREADY == false)
    {
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {                
                if (Blocks[col][row] == nullptr )
                {
                    continue;
                }

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

        int clickRow = click_block->GetBlockLocation().Row;
        int clickCol = click_block->GetBlockLocation().Column;
        int swapkRow = swap_block->GetBlockLocation().Row;
        int swapCol = swap_block->GetBlockLocation().Column;


        int checkRowCick = clickRow - swapkRow;
        int checkRowSwap = swapkRow - clickRow;
        int checkColClick = clickCol - swapCol;
        int checkColSwap = swapCol - clickCol;

        // 블럭의 거리가 체크된 블럭끼리의 거리가 멀때 블럭들위치를 바꾸지않고 리턴
        {
            if (checkRowCick > CheckBlock || checkRowSwap > CheckBlock || checkColClick > CheckBlock || checkColSwap > CheckBlock)
            {
                Blockreturn(clickRow, clickCol, swapkRow, swapCol);
                return;
            }
            else if (checkRowCick == CheckBlock && checkColClick == CheckBlock)
            {
                Blockreturn(clickRow, clickCol, swapkRow, swapCol);
                return;
            }
            else if (checkRowCick == CheckBlock && checkColSwap == CheckBlock)
            {
                Blockreturn(clickRow, clickCol, swapkRow, swapCol);
                return;
            }
            else if (checkRowSwap == CheckBlock && checkColClick == CheckBlock)
            {
                Blockreturn(clickRow, clickCol, swapkRow, swapCol);
                return;
            }
            else if (checkRowSwap == CheckBlock && checkColSwap == CheckBlock)
            {
                Blockreturn(clickRow, clickCol, swapkRow, swapCol);
                return;
            }
        }


        if (clickRow > swapkRow)
        {
            if (Clickpos.Y >= TempSwap.Y)
            {
                click_block->AddActorLocation({ FVector::Up * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                YCLICKMOVE = true;
            }

            if (Swappos.Y <= TempClick.Y)
            {
                swap_block->AddActorLocation(FVector::Down * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempClick });
                AAnimal_Block::SwapChange = true;
                YSWAPMOVE = true;
            }

        }
        else if (clickRow < swapkRow)
        {
            if (Clickpos.Y <= TempSwap.Y)
            {
                click_block->AddActorLocation({ FVector::Down * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                YCLICKMOVE = true;
            }

            if (Swappos.Y >= TempClick.Y)
            {
                swap_block->AddActorLocation(FVector::Up * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempClick });
                AAnimal_Block::SwapChange = true;
                YSWAPMOVE = true;
            }
        }

        else if (clickCol > swapCol)
        {

            if (Clickpos.X >= TempSwap.X)
            {
                click_block->AddActorLocation({ FVector::Left * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                XCLICKMOVE = true;
            }

            if (Swappos.X <= TempClick.X)
            {
                swap_block->AddActorLocation(FVector::Right * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempClick });
                AAnimal_Block::SwapChange = true;
                XSWAPMOVE = true;
            }
        }
        else if (clickCol < swapCol)
        {

            if (Clickpos.X <= TempSwap.X)
            {
                click_block->AddActorLocation({ FVector::Right * 150.0f * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                XCLICKMOVE = true;
            }

            if (Swappos.X >= TempClick.X)
            {
                swap_block->AddActorLocation(FVector::Left * 150.0f * _DeltaTime);
            }
            else
            {
                swap_block->SetActorLocation({ TempClick });
                AAnimal_Block::SwapChange = true;
                XSWAPMOVE = true;
            }
        }


        if (AAnimal_Block::SwapChange == true && AAnimal_Block::ClickChange == true)
        {
            bool _set = false;
            click_block->SetBlockstate(_set, 1);
            swap_block->SetBlockstate(_set, 2);
            click_block->SetColumn(swapCol);
            click_block->SetRow(swapkRow);
            swap_block->SetColumn(clickCol);
            swap_block->SetRow(clickRow);

            AAnimal_Block* XLine_Check_Before = Blocks[clickCol][clickRow];
            Blocks[clickCol][clickRow] = Blocks[swapCol][swapkRow];
            Blocks[swapCol][swapkRow] = XLine_Check_Before;


            AAnimal_Block::SwapREADY = false;
            AAnimal_Block::SwapChange = false;
            AAnimal_Block::ClickChange = false;
        }        
    }
}

void UPlayLevel::Blockreturn(int _clickRow, int _clickCol, int _swapkRow, int _swapCol)
{
    if (AAnimal_Block::SwapChange == false && AAnimal_Block::ClickChange == false)
    {
        bool _set = false;
        click_block->SetBlockstate(_set, 1);
        swap_block->SetBlockstate(_set, 2);

        // ================ Test Move Block Begin ================
        //click_block->SetColumn(_swapCol);
        //click_block->SetRow(_swapkRow);
        //swap_block->SetColumn(_clickCol);
        //swap_block->SetRow(_clickRow);

        //AAnimal_Block* XLine_Check_Before = Blocks[_clickCol][_clickRow];
        //Blocks[_clickCol][_clickRow] = Blocks[_swapCol][_swapkRow];
        //Blocks[_swapCol][_swapkRow] = XLine_Check_Before;
        //  ================ Test Move Block End ================



        AAnimal_Block::SwapREADY = false;
        AAnimal_Block::SwapChange = false;
        AAnimal_Block::ClickChange = false;
    }
}

void UPlayLevel::BlockDestroyCheck()
{
	for (int row = 0; row < MapSize; row++)
	{
		for (int col = 1; col < MapSize - 1; col++)
		{
			if (Blocks[col][row] == nullptr || Blocks[col - 1][row] == nullptr || Blocks[col + 1][row] == nullptr)
			{
				continue;
			}

			AAnimal_Block* CheckBlock = Blocks[col][row];
			FVector CheckBlockpos = CheckBlock->GetActorLocation();

			AAnimal_Block* XLine_Check_Before = Blocks[col - 1][row];
			AAnimal_Block* XLine_Check_After = Blocks[col + 1][row];

			// 1. x축 기준으로 검사진행
			// 0번째 와 마지막인 6번째는 제외 시키고 검사
			{
				if (XLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
				{
					continue;
				}
				if (XLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
				{
					continue;
				}

				XLine_Check_Before->SetBoomb(true);
				XLine_Check_After->SetBoomb(true);
				CheckBlock->SetBoomb(true);

				Blocks[col + 1][row] = nullptr;
				Blocks[col - 1][row] = nullptr;
				Blocks[col][row] = nullptr;
                Score += 10;
			}
		}
	}

        
	for (int row = 1; row < MapSize - 1; row++)
	{
		for (int col = 0; col < MapSize; col++)
		{
			// test 없애고 있는중
			if (Blocks[col][row] == nullptr || Blocks[col][row - 1] == nullptr || Blocks[col][row + 1] == nullptr)
			{
				continue;
			}


			AAnimal_Block* CheckBlock = Blocks[col][row];
			FVector CheckBlockpos = CheckBlock->GetActorLocation();

			AAnimal_Block* YLine_Check_Before = Blocks[col][row - 1];
			AAnimal_Block* YLine_Check_After = Blocks[col][row + 1];

			// 2. y축 기준으로 검사진행
			 // 0번째 와 마지막인 6번째는 제외 시키고 검사
			{
				if (YLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
				{
					continue;
				}
				if (YLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
				{
					continue;
				}

				YLine_Check_Before->SetBoomb(true);
				YLine_Check_After->SetBoomb(true);
				CheckBlock->SetBoomb(true);


				Blocks[col][row - 1] = nullptr;
				Blocks[col][row + 1] = nullptr;
				Blocks[col][row] = nullptr;
                Score += 10;
			}
		}
	}
}

void UPlayLevel::BlockMove()
{
    for (int row = 0; row < MapSize - 1; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {            
            if (Blocks[col][row] == nullptr)
            {
                continue;
            }

            if (Blocks[col][row + 1] == nullptr)
            {
                if (Blocks[col][row]->GetUnderBoomb() == false)
                {
                    swap_block = Blocks[col][row];
                    FVector BeenBlockpos = FVector(swap_block->GetActorLocation().X, swap_block->GetActorLocation().Y + CellSize, swap_block->GetActorLocation().Z, swap_block->GetActorLocation().W);
                    Blocks[col][row]->SetUnderPos(BeenBlockpos);
                    Blocks[col][row]->SetUnderBoomb(true);
                    Blocks[col][row + 1] = Blocks[col][row];
                    Blocks[col][row]->SetRow(row + 1);
                    Blocks[col][row] = nullptr;
                }
            }
        }
    }
}

void UPlayLevel::GenerateNewBlocks()
{
    for (int col = 0; col < MapSize; col++)
    {
        if (Blocks[col][0] == nullptr)
        {
            int random = 0;
            random = UHelper::Random(0, 6);
            if (random == 0)
            {
                Blocks[col][0] = SpawnActor<ACat_Block>();
            }
            else if (random == 1)
            {
                Blocks[col][0] = SpawnActor<ACheckin_Block>();
            }
            else if (random == 2)
            {
                Blocks[col][0] = SpawnActor<ADog_Block>();
            }
            else if (random == 3)
            {
                Blocks[col][0] = SpawnActor<AMonkey_Block>();
            }
            else if (random == 4)
            {
                Blocks[col][0] = SpawnActor<AMouse_Block>();
            }
            else if (random == 5)
            {
                Blocks[col][0] = SpawnActor<APig_Block>();
            }
            else if (random == 6)
            {
                Blocks[col][0] = SpawnActor<ARabbit_Block>();
            }

            FVector BlockLocation;     // 동물 블록 위치 설정
            BlockLocation.X = StartLocation.X + (CellSize * col);  // 시작 위치에서 CellSize만큼 이동
            BlockLocation.Y = StartLocation.Y + (CellSize * 0);
            Blocks[col][0]->SetActorLocation(BlockLocation);
            Blocks[col][0]->SetCursor(Cursor);
            Blocks[col][0]->SetColumn(col);
            Blocks[col][0]->SetRow(0);
            continue;
        }
    }
}
