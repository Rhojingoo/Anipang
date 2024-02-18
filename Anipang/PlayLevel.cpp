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

            if (ClickChangeCheck == true)
            {
                ////Ŭ������ �̵��� �� 3Match�� �Ǵ��� �Ǵ��ϴ� �˻����
                XlineBlock_Swap_Check(_DeltaTime);
                XlineBlock_Swap_Move(_DeltaTime);
                ////�˻�� ���� return �Ǵ� stay�� ��Ÿ���� �������
                YlineBlock_Swap_Check(_DeltaTime);
                YlineBlock_Swap_Move(_DeltaTime);
            }





            BlockDestroyCheck();
            BlockMove();
            GenerateNewBlocks();
        }





        // �˻� ������ �Ǵ°��� Ȯ���ʿ�.
        //{
        //}
        // ���� �˻簡 ������ߴٸ� [bool Blockreturn false���� �־ �̿��Ұ�]
        // {
        // }  
        // ���� �˻翡 ������ߴٸ� [bool Blockreturn false���϶� ����̺κ�����]              
        // Ŭ���Ѱ� �̵��ѵ� match�� �ȵǸ� �ǵ��ư��� ���� ¥��  
        // {
        // }
        // ���� �˻簡 ����ߴٸ� [bool Blockreturn true���϶� ����̺κ�����]              

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
            // ������ ���� ����� ���� ����
            Block_Manager::eBlock blockType;
            if (col >= MapSize - 7 && row >= MapSize - 7) // ������ �Ʒ� 7x7 ����
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
                NewBlock->SetCursor(Cursor);
                NewBlock->SetActive(true);
                // ���� ��� ����
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
            // ���� ��� ����
            int random = 0;
            random = UHelper::Random(0, 6);
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

            FVector BlockLocation;     // ���� ��� ��ġ ����
            BlockLocation.X = StartLocation.X + (CellSize * col);  // ���� ��ġ���� CellSize��ŭ �̵�
            BlockLocation.Y = StartLocation.Y + (CellSize * row);
            Blocks[col][row]->SetActorLocation(BlockLocation);
            Blocks[col][row]->SetCursor(Cursor);
            Blocks[col][row]->SetColumn(col);
            Blocks[col][row]->SetRow(row);
        }
    }
}



void UPlayLevel::BlockClickUpdate(float _DeltaTime)
{
    if (AAnimal_Block::SwapREADY == false)
    {
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {
                if (Blocks[col][row] == nullptr)
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

        // ���� �Ÿ��� üũ�� �������� �Ÿ��� �ֶ� ������ġ�� �ٲ����ʰ� ����
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
            ClickChangeCheck = true;
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


bool UPlayLevel::CheckMatchAroundBlock(int col, int row)
{
    // ���� ����� Ÿ�� ��������
    if (Blocks[col][row] == nullptr) // ���� ��ġ�� ����� ���ٸ� �˻����� ����
        return false;
    AAnimal_Block::Block_Type currentType = Blocks[col][row]->GetBlockType();

    // ���� ���� ��ġ �˻�
    int horizontalMatchCount = 1; // ���� ��� ����
    // �������� �˻�
    for (int i = col - 1; i >= 0 && i >= col - 2; --i) {
        if (Blocks[i][row] != nullptr && Blocks[i][row]->GetBlockType() == currentType)
        {
            horizontalMatchCount++;
        }
        else {
            break; // ���ӵ��� ������ �ߴ�
        }
    }
    // ���������� �˻�
    for (int i = col + 1; i < MapSize && i <= col + 2; ++i) {
        if (Blocks[i][row] != nullptr && Blocks[i][row]->GetBlockType() == currentType) {
            horizontalMatchCount++;
        }
        else {
            break; // ���ӵ��� ������ �ߴ�
        }
    }
    if (horizontalMatchCount >= 3) return true; // 3�� �̻� ���ӵǸ� true ��ȯ

    // ���� ���� ��ġ �˻�
    int verticalMatchCount = 1; // ���� ��� ����
    // ���� �˻�
    for (int i = row - 1; i >= 0 && i >= row - 2; --i) {
        if (Blocks[col][i] != nullptr && Blocks[col][i]->GetBlockType() == currentType) {
            verticalMatchCount++;
        }
        else {
            break; // ���ӵ��� ������ �ߴ�
        }
    }
    // �Ʒ��� �˻�
    for (int i = row + 1; i < MapSize && i <= row + 2; ++i) {
        if (Blocks[col][i] != nullptr && Blocks[col][i]->GetBlockType() == currentType) {
            verticalMatchCount++;
        }
        else {
            break; // ���ӵ��� ������ �ߴ�
        }
    }
    if (verticalMatchCount >= 3) return true; // 3�� �̻� ���ӵǸ� true ��ȯ

    // ���� �� ���� ��ġ ��� ������ false ��ȯ
    return false;
}


void UPlayLevel::XlineBlock_Swap_Check(float _DeltaTime)
{
    if (XSWAPMOVE && XCLICKMOVE)
    {
        // Ŭ���� ��ϰ� ��ȯ�� ����� ��ġ�� Ȯ��
        int clickRow = click_block->GetBlockLocation().Row;
        int clickCol = click_block->GetBlockLocation().Column;
        int swapCol = swap_block->GetBlockLocation().Column;

        // Ŭ���� ��ϰ� ��ȯ�� ��� ������ 3-match �˻�
        bool clickMatchFound = CheckMatchAroundBlock(clickCol, clickRow);
        bool swapMatchFound = CheckMatchAroundBlock(swapCol, clickRow);

        // ����� ���� ���� ������Ʈ
        XLINE_ChageCheck = (clickMatchFound || swapMatchFound) ? BlockChangeSuccess : BlockChangeFail;
    }
}

void UPlayLevel::XlineBlock_Swap_Move(float _DeltaTime)
{
    if (XLINE_ChageCheck == BlockChangeFail)     // �˻� ���ж��
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
            click_block = nullptr;
            swap_block = nullptr;
            ClickChangeCheck = false;
        }
    }
    else if (XLINE_ChageCheck == BlockChangeSuccess)   // �˻� ����
    {
        XLINE_ChageCheck = BlockChangeDefault;
        XCLICKMOVE = false;
        XSWAPMOVE = false;
        click_block = nullptr;
        swap_block = nullptr;
        ClickChangeCheck = false;
    }
}

void UPlayLevel::YlineBlock_Swap_Check(float _DeltaTime)
{
    if (YSWAPMOVE && YCLICKMOVE)
    {
        // Ŭ���� ��ϰ� ��ȯ�� ����� ��ġ�� Ȯ��
        int clickRow = click_block->GetBlockLocation().Row;
        int clickCol = click_block->GetBlockLocation().Column;
        int swapRow = swap_block->GetBlockLocation().Row;

        // Ŭ���� ��ϰ� ��ȯ�� ��� ������ 3-match �˻�
        bool clickMatchFound = CheckMatchAroundBlock(clickCol, clickRow);
        bool swapMatchFound = CheckMatchAroundBlock(clickCol, swapRow);

        // ����� ���� ���� ������Ʈ
        YLINE_ChageCheck = (clickMatchFound || swapMatchFound) ? BlockChangeSuccess : BlockChangeFail;
    }
}

void UPlayLevel::YlineBlock_Swap_Move(float _DeltaTime)
{
    if (YLINE_ChageCheck == BlockChangeFail)     // �˻� ���ж��
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

            click_block = nullptr;
            swap_block = nullptr;
            ClickChangeCheck = false;
        }
    }
    else if (YLINE_ChageCheck == BlockChangeSuccess)   // �˻� ����
    {
        YLINE_ChageCheck = BlockChangeDefault;
        YCLICKMOVE = false;
        YSWAPMOVE = false;
        click_block = nullptr;
        swap_block = nullptr;
        ClickChangeCheck = false;
    }
}



void UPlayLevel::BlockDestroyCheck()
{
    for (int row = 0; row < MapSize; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {

            if (Blocks[col][row] == nullptr)
                continue;

            AAnimal_Block* StartBlock = Blocks[col][row];
            int matchCount = 1;

            // ������ ����� Ȯ���Ͽ� ���� Ÿ���� ����� �� �� �ִ��� ����
            for (int checkCol = col + 1; checkCol < MapSize; checkCol++) {
                if (Blocks[checkCol][row] != nullptr && Blocks[checkCol][row]->GetBlockType() == StartBlock->GetBlockType())
                {
                    matchCount++;
                }
                else
                {
                    break;
                }
            }

            // 3�� �̻� ������ ��� ��� ���� ��� ����
            if (matchCount >= 3)
            {
                for (int i = 0; i < matchCount; i++)
                {
                    Blocks[col + i][row]->SetBoomb(true);
                    Blocks[col + i][row] = nullptr;
                }
                Score += 10 * matchCount; // ���� ����
                col += matchCount - 1; // �̹� �˻��� ����� �ǳʶٱ�
            }


            //if (Blocks[col][row] == nullptr || Blocks[col - 1][row] == nullptr || Blocks[col + 1][row] == nullptr)
            //{
            //	continue;
            //}

            //AAnimal_Block* CheckBlock = Blocks[col][row];
            //FVector CheckBlockpos = CheckBlock->GetActorLocation();

            //AAnimal_Block* XLine_Check_Before = Blocks[col - 1][row];
            //AAnimal_Block* XLine_Check_After = Blocks[col + 1][row];

            //// 1. x�� �������� �˻�����
            //// 0��° �� �������� 6��°�� ���� ��Ű�� �˻�
            //{
            //	if (XLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            //	{
            //		continue;
            //	}
            //	if (XLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            //	{
            //		continue;
            //	}

            //	XLine_Check_Before->SetBoomb(true);
            //	XLine_Check_After->SetBoomb(true);
            //	CheckBlock->SetBoomb(true);

            //	Blocks[col + 1][row] = nullptr;
            //	Blocks[col - 1][row] = nullptr;
            //	Blocks[col][row] = nullptr;
   //             Score += 10;
            //}
        }
    }


    for (int row = 0; row < MapSize; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            if (Blocks[col][row] == nullptr) continue;

            AAnimal_Block* StartBlock = Blocks[col][row];
            int matchCount = 1;

            // �Ʒ��� ����� Ȯ���Ͽ� ���� Ÿ���� ����� �� �� �ִ��� ����
            for (int checkRow = row + 1; checkRow < MapSize; checkRow++) {
                if (Blocks[col][checkRow] != nullptr && Blocks[col][checkRow]->GetBlockType() == StartBlock->GetBlockType())
                {
                    matchCount++;
                }
                else {
                    break;
                }
            }

            // 3�� �̻� ������ ��� ��� ���� ��� ����
            if (matchCount >= 3) {
                for (int i = 0; i < matchCount; i++)
                {
                    Blocks[col][row + i]->SetBoomb(true);
                    Blocks[col][row + i] = nullptr;
                }
                Score += 10 * matchCount; // ���� ����
                row += matchCount - 1; // �̹� �˻��� ����� �ǳʶٱ�
            }



            // test ���ְ� �ִ���
            //if (Blocks[col][row] == nullptr || Blocks[col][row - 1] == nullptr || Blocks[col][row + 1] == nullptr)
            //{
            //	continue;
            //}


            //AAnimal_Block* CheckBlock = Blocks[col][row];
            //FVector CheckBlockpos = CheckBlock->GetActorLocation();

            //AAnimal_Block* YLine_Check_Before = Blocks[col][row - 1];
            //AAnimal_Block* YLine_Check_After = Blocks[col][row + 1];

            //// 2. y�� �������� �˻�����
            // // 0��° �� �������� 6��°�� ���� ��Ű�� �˻�
            //{
            //	if (YLine_Check_Before->GetBlockType() != CheckBlock->GetBlockType())
            //	{
            //		continue;
            //	}
            //	if (YLine_Check_After->GetBlockType() != CheckBlock->GetBlockType())
            //	{
            //		continue;
            //	}

            //	YLine_Check_Before->SetBoomb(true);
            //	YLine_Check_After->SetBoomb(true);
            //	CheckBlock->SetBoomb(true);


            //	Blocks[col][row - 1] = nullptr;
            //	Blocks[col][row + 1] = nullptr;
            //	Blocks[col][row] = nullptr;
   //             Score += 10;
            //}
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

            FVector BlockLocation;     // ���� ��� ��ġ ����
            BlockLocation.X = StartLocation.X + (CellSize * col);  // ���� ��ġ���� CellSize��ŭ �̵�
            BlockLocation.Y = StartLocation.Y + (CellSize * 0);
            Blocks[col][0]->SetActorLocation(BlockLocation);
            Blocks[col][0]->SetCursor(Cursor);
            Blocks[col][0]->SetColumn(col);
            Blocks[col][0]->SetRow(0);
            continue;
        }
    }
}
