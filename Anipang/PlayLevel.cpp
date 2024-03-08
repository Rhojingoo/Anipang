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
#include "Boomb_Block.h"
#include "Helper.h"
#include "Combo_OBJ.h"
#include "NumberFont.h"
#include "Manual.h"

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

    Timer = SpawnActor<ATime_Gauge>();
    Timer->SetActorLocation({ 231,705 });
    Combo_OBJ = SpawnActor<ACombo_OBJ>();
    Combo_OBJ->SetActorLocation({ 240,150 });

    ScoreMN = SpawnActor<ScoreManager>();
}

void UPlayLevel::Tick(float _DeltaTime)
{
    ULevel::Tick(_DeltaTime);
    Manual_Switch();
    Test_TimeStop_Mode();
 
    if (GameStart == false)
    {
        GameStart = Start_Rabbit->IsStart();    
    }
    else
    {
        if (BackGroundSound == false)
        {
            Play_Game_Sound = UEngineSound::SoundPlay("Anipang_Playgame.mp3");
            Play_Game_Sound.Loop();
            BackGroundSound = true;
        }

        Timer->TimerStart();
        if (Timer->IsFinish() == true)
        {
            if (GameEnd == false)
            {
                End_Rabbit = SpawnActor<AGame_End>();
                End_Rabbit->SetActorLocation({ 250,400 });
                Play_Game_Sound.Off();
                UEngineSound::SoundPlay("TimeOver.mp3");
                GameEnd = true;
            }
        }
        else
        {
            if (Test_BlockMove_Mode == false)
            {
                if (UEngineInput::IsDown(VK_F9))
                {
                    Test_BlockMove_Mode = true;
                    Test_BlockMoveMode();
                    return;
                }

                ComboCheck(_DeltaTime);

                // Before GameStart CanMake3match Checks Logics;
                if (CheckMatch == true)
                {
                    CanAMatch = CanMakeAMatch();
                }

                if (HintBlock == false && ComboTime >= 3.0f)
                {
                    if (Hint_block == nullptr)
                        return;
                    Hint_block->FindBlock();
                    HintBlock = true;
                }


                if (CanAMatch == true)
                {
                    if (AAnimal_Block::GetFirstClick() == true && AAnimal_Block::GetSecondClick() == true)
                    {
                        BlockClickUpdate(_DeltaTime);
                    }

                    if (ClickChangeCheck == true)
                    {
                        //Ŭ������ �̵��� �� 3Match�� �Ǵ��� �Ǵ��ϴ� �˻����
                        XlineBlock_Swap_Check(_DeltaTime);
                        XlineBlock_Swap_Move(_DeltaTime);
                        ////�˻�� ���� return �Ǵ� stay�� ��Ÿ���� �������
                        YlineBlock_Swap_Check(_DeltaTime);
                        YlineBlock_Swap_Move(_DeltaTime);

                        //�������̵�
                        BlockDestroyAllow = true;
                    }

                    if (BlockDestroyAllow == true)
                    {
                        BlockDestroyCheck();
                        BlockDestroyAllow = false;
                    }

                    BoombBlock_Destrot_Check();
                    BlockMove(_DeltaTime);
                    GenerateNewBlocks();
                    BlockMoveCheck();
                }
                else
                {
                    AllDestroyCheck();
                    if (AllDestroy == true)
                    {
                        CreateBlock();
                        AllDestroy = false;
                    }
                }
            }
            else
            {
                if (UEngineInput::IsDown(VK_F9))
                {
                    Test_BlockMove_Mode = false;
                    Test_BlockMoveMode();
                    return;
                }

                if (AAnimal_Block::GetFirstClick() == true && AAnimal_Block::GetSecondClick() == true)
                {
                    TestClick();
                }
            }
        }
    }

    ScoreMN->SetScore(Score);

    if (Hint_block != nullptr)
    {
        if (Hint_block->ISFind() == true)
        {
            Hint_block = nullptr;
            HintBlock = false;
            ClearCombotime();
        }  
    }

    InputKey_DestroyBlock();


    if (UEngineInput::IsDown('N'))
    {
        GEngine->ChangeLevel("GetScore");
    }
}

void UPlayLevel::LevelStart(ULevel* _Level)
{
    Score = ScoreManager::GetScore();
    SpawnActor<AFadeIN_OUT>();
    CreateBlock();
    Start_Rabbit = SpawnActor<AGame_Start>();
    Start_Rabbit->SetActorLocation({ 235,400 });
    UEngineSound::SoundPlay("Ready_Go.mp3");

    Combo_OBJ->ClearCombo();
    Combo = 0;
    PreveCombo = 0;
    Hint_block = nullptr;
    BackGroundSound = false;
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
    Combo = 0;
    PreveCombo = 0;
    Combo_OBJ->ClearCombo();
    Hint_block = nullptr;
    BackGroundSound = false;
    HintBlock = false;
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

void UPlayLevel::ComboCheck(float _DeltaTime)
{
    Combo_OBJ->SetCombo(Combo);
    int CheckCombo = Combo - PreveCombo;
    if (CheckCombo >= 1)
    {
        Combo_OBJ->SetFont();
        PreveCombo = Combo;
    }
    if (ComboTimeCheck == false)
    {
        ClearCombotime();
    }

    {
        ComboTimeCheck = true;
        if (ComboTimeCheck == true)
        {
            ComboTime += _DeltaTime;

            if (ComboTime >= 5.0f)
            {
                ClearCombotime();
                Combo = 0;
                PreveCombo = 0;
            }
        }
    }
}

bool UPlayLevel::CanMakeAMatch()
{
    for (int row = 0; row < MapSize; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            if (Blocks[col][row] == nullptr)
            {
                continue;
            }

            // ������ �� �ִ� �� ����: �����ʰ� �Ʒ�
            int directions[2][2] = { {0, 1}, {1, 0} };

            for (auto& dir : directions)
            {
                int newRow = row + dir[1];
                int newCol = col + dir[0];

                // �� ��ġ�� ���� ���� �ִ��� Ȯ��
                if (newRow < MapSize && newCol < MapSize && Blocks[newCol][newRow] != nullptr)
                {
                    // ����� ����
                    AAnimal_Block* temp = Blocks[col][row];
                    Blocks[col][row] = Blocks[newCol][newRow];
                    Blocks[newCol][newRow] = temp;

                    // ���� �� ��ġ�� �ִ��� Ȯ��
                    if (CheckForMatch(col, row) == true || CheckForMatch(newCol, newRow) == true)
                    {
                        // �����·� ����
                        Blocks[newCol][newRow] = Blocks[col][row];
                        Blocks[col][row] = temp;
                        return true; // �� ���� ���������� ��ġ ����
                    }

                    // �����·� ����
                    Blocks[newCol][newRow] = Blocks[col][row];
                    Blocks[col][row] = temp;
                }
            }
        }
    }
    return false; // � ���������ε� 3�� �̻��� ��ġ�� ���� �� ����
}

bool UPlayLevel::CheckForMatch(int _col, int _row)
{
    if(HintBlock == false)
    {
        if (Blocks[_col][_row] == nullptr)
            return false;

        AAnimal_Block::Block_Type CheckBL = Blocks[_col][_row]->GetBlockType();
        int matchCount = 1; // ���� ����� �����Ͽ� ī��Ʈ ����

        // ���� ���� �˻� (����)
        for (int i = _col - 1; i >= 0 && Blocks[i][_row] != nullptr && Blocks[i][_row]->GetBlockType() == CheckBL; i--)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3��ġ �߻� �� ���� ��� ����
                }
            }
        }
        // ���� ���� �˻� (������)
        for (int i = _col + 1; i < MapSize && Blocks[i][_row] != nullptr && Blocks[i][_row]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3��ġ �߻� �� ���� ��� ����
                }
            }
        }
        if (matchCount >= 3)
        {
            return true; // ���� �������� 3�� �̻� ��ġ
        }

        matchCount = 1; // ī��Ʈ �ʱ�ȭ �� ���� ���� �˻�

        // ���� ���� �˻� (��)
        for (int i = _row - 1; i >= 0 && Blocks[_col][i] != nullptr && Blocks[_col][i]->GetBlockType() == CheckBL; i--)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3��ġ �߻� �� ���� ��� ����
                }
            }
        }
        // ���� ���� �˻� (�Ʒ�)
        for (int i = _row + 1; i < MapSize && Blocks[_col][i] != nullptr && Blocks[_col][i]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3��ġ �߻� �� ���� ��� ����
                }
            }
        }
        if (matchCount >= 3)
        {
            return true; // ���� �������� 3�� �̻� ��ġ
        }
    }
    else
    {
        int HIINTCOL = Hint_block->GetBlockLocationCol();
        int HIINTROW = Hint_block->GetBlockLocationRow();

        if (Blocks[HIINTCOL][HIINTROW] == nullptr)
            return false;

        AAnimal_Block::Block_Type CheckBL = Blocks[HIINTCOL][HIINTROW]->GetBlockType();
        int matchCount = 1; // ���� ����� �����Ͽ� ī��Ʈ ����

        // ���� ���� �˻� (����)
        for (int i = HIINTCOL - 1; i >= 0 && Blocks[i][HIINTROW] != nullptr && Blocks[i][HIINTROW]->GetBlockType() == CheckBL; i--)
        {
            matchCount++; 
        }
        // ���� ���� �˻� (������)
        for (int i = HIINTCOL + 1; i < MapSize && Blocks[i][HIINTROW] != nullptr && Blocks[i][HIINTROW]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;     
        }
        if (matchCount >= 3)
        {
            return true; // ���� �������� 3�� �̻� ��ġ
        }

        matchCount = 1; // ī��Ʈ �ʱ�ȭ �� ���� ���� �˻�

        // ���� ���� �˻� (��)
        for (int i = HIINTROW - 1; i >= 0 && Blocks[HIINTCOL][i] != nullptr && Blocks[HIINTCOL][i]->GetBlockType() == CheckBL; i--)
        {
            matchCount++;
        }
        // ���� ���� �˻� (�Ʒ�)
        for (int i = HIINTROW + 1; i < MapSize && Blocks[_col][i] != nullptr && Blocks[_col][i]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;
        }
        if (matchCount >= 3)
        {
            return true; 
        }
    }

    HintBlock = false;
    if (Hint_block != nullptr)
    {
        Hint_block->FindEndBlock();
        Hint_block = nullptr;
    }
    return false; // ���� �Ǵ� ���� ���⿡�� 3�� �̻� ��ġ�ϴ� ����� ����
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

                if (Blocks[col][row]->GetFirstPick() == true && AAnimal_Block::GetFirstClick() ==true)
                {
                    click_block = Blocks[col][row];
                    Clickpos = click_block->GetActorLocation();
                }

                if (Blocks[col][row]->GetSecondPick() == true && AAnimal_Block::GetSecondClick() == true)
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
        if (click_block == nullptr || swap_block == nullptr)
        {
            return;
        }

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
                click_block->AddActorLocation({ FVector::Up * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                YCLICKMOVE = true;
            }

            if (Swappos.Y <= TempClick.Y)
            {
                swap_block->AddActorLocation(FVector::Down * BlockSpeed * _DeltaTime);
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
                click_block->AddActorLocation({ FVector::Down * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                YCLICKMOVE = true;
            }

            if (Swappos.Y >= TempClick.Y)
            {
                swap_block->AddActorLocation(FVector::Up * BlockSpeed* _DeltaTime);
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
                click_block->AddActorLocation({ FVector::Left * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                XCLICKMOVE = true;
            }

            if (Swappos.X <= TempClick.X)
            {
                swap_block->AddActorLocation(FVector::Right * BlockSpeed * _DeltaTime);
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
                click_block->AddActorLocation({ FVector::Right * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempSwap });
                AAnimal_Block::ClickChange = true;
                XCLICKMOVE = true;
            }

            if (Swappos.X >= TempClick.X)
            {
                swap_block->AddActorLocation(FVector::Left * BlockSpeed* _DeltaTime);
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

            AAnimal_Block* Temp_Block = Blocks[clickCol][clickRow];
            Blocks[clickCol][clickRow] = Blocks[swapCol][swapkRow];
            Blocks[swapCol][swapkRow] = Temp_Block;

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

        AAnimal_Block::SwapREADY = false;
        AAnimal_Block::SwapChange = false;
        AAnimal_Block::ClickChange = false;
    }
}

bool UPlayLevel::CheckMatchAroundBlock(int col, int row)
{
    // ���� ����� Ÿ�� ��������
    if (Blocks[col][row] == nullptr) // ���� ��ġ�� ����� ���ٸ� �˻����� ����
    {
        return false;
    }
    AAnimal_Block::Block_Type currentType = Blocks[col][row]->GetBlockType();

    // ���� ���� ��ġ �˻�
    int horizontalMatchCount = 1; // ���� ��� ����
    // �������� �˻�
    for (int i = col - 1; i >= 0 && i >= col - 2; --i) {
        if (Blocks[i][row] != nullptr && Blocks[i][row]->GetBlockType() == currentType)
        {
            horizontalMatchCount++;
        }
        else
        {
            break; // ���ӵ��� ������ �ߴ�
        }
    }
    // ���������� �˻�
    for (int i = col + 1; i < MapSize && i <= col + 2; ++i) {
        if (Blocks[i][row] != nullptr && Blocks[i][row]->GetBlockType() == currentType) {
            horizontalMatchCount++;
        }
        else 
        {
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
        else
        {
            break; // ���ӵ��� ������ �ߴ�
        }
    }
    // �Ʒ��� �˻�
    for (int i = row + 1; i < MapSize && i <= row + 2; ++i) {
        if (Blocks[col][i] != nullptr && Blocks[col][i]->GetBlockType() == currentType) {
            verticalMatchCount++;
        }
        else
        {
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
                click_block->AddActorLocation({ FVector::Right * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });
            }

            if (Swappos.X >= TempSwap.X)
            {
                swap_block->AddActorLocation(FVector::Left * BlockSpeed * _DeltaTime);
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
                click_block->AddActorLocation({ FVector::Left * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });

            }

            if (Swappos.X <= TempSwap.X)
            {
                swap_block->AddActorLocation(FVector::Right * BlockSpeed * _DeltaTime);
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
                click_block->AddActorLocation({ FVector::Down * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });
            }

            if (Swappos.Y >= TempSwap.Y)
            {
                swap_block->AddActorLocation(FVector::Up * BlockSpeed * _DeltaTime);
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
                click_block->AddActorLocation({ FVector::Up * BlockSpeed * _DeltaTime });
            }
            else
            {
                click_block->SetActorLocation({ TempClick });

            }

            if (Swappos.Y <= TempSwap.Y)
            {
                swap_block->AddActorLocation(FVector::Down * BlockSpeed * _DeltaTime);
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

void UPlayLevel::BoombBlock_Destrot_Check()
{
    for (int row = 0; row < MapSize; ++row)
    {
        for (int col = 0; col < MapSize; ++col)
        {
            if (Blocks[col][row] == nullptr)
                continue;

            if (Blocks[col][row]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
            {
                if (Blocks[col][row] != nullptr)
                {
                    if (Blocks[col][row]->Check_Boomb_first_Toutch())
                    {
                        Blocks[col][row]->SetBoomb(true);
                        Blocks[col][row] = nullptr;
                        ComboTimeCheck = false;
                    }
                }
                continue;
            }

            if (Blocks[col][row]->Check_Boomb_Effect_Toutch() == true)
            {
                Blocks[col][row]->SetBoomb(true);
                Blocks[col][row] = nullptr;

                if (Combo == 0)
                {
                    Score += 10; // ���� ����
                    ComboTimeCheck = false;
                }
                else
                {
                    Score += 10 * Combo;                
                    ComboTimeCheck = false;
                }               
            }
        }
    }
}

void UPlayLevel::BlockDestroyCheck()
{
    //�޺��� 5�̻� �϶�
    if (Combo >= ComboBoombCheck)
    {
        // X�� �˻�
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {
                if (Blocks[col][row] == nullptr)
                    continue;

                AAnimal_Block* StartBlock = Blocks[col][row];
                int matchCount = 1;

                // ������ ����� Ȯ���Ͽ� ���� Ÿ���� ����� �� �� �ִ��� ����
                for (int checkCol = col + 1; checkCol < MapSize; checkCol++)
                {
                    if (Blocks[checkCol][row] != nullptr && Blocks[checkCol][row]->GetBlockType() == StartBlock->GetBlockType())
                    {
                        matchCount++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (matchCount >= 3) // ������ �����ϴ� ���
                {
                    Score += (10 * matchCount) * (Combo + 1);

                    for (int Y = -1; Y <= 1; Y++) // Y ���� ����
                    {
                        for (int X = 0; X < matchCount; X++)
                        {
                            // �迭 ������ ������� Ȯ��
                            if (col + X >= MapSize || row + Y < 0 || row + Y >= MapSize)
                                continue;

                            // �⺻ ���� ����
                            if (Blocks[col + X][row + Y] != nullptr)
                            {
                                if (Blocks[col + X][row + Y]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                    continue;

                                Blocks[col + X][row + Y]->SetBoomb(true);
                                Blocks[col + X][row + Y] = nullptr;
                                Score += 10 * Combo;
                                ComboAdd = true;
                                ComboTimeCheck = false;
                            }
                        }
                    }

                    // ���� ��ġ�� ��� ��� �� ���� �翷 �߰� ����
                    if (row > 0 && row < MapSize - 1) // ���� üũ
                    {
                        // ���� �߰� ����
                        if (col > 0 && Blocks[col - 1][row] != nullptr)
                        {
                            if (Blocks[col - 1][row]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col - 1][row]->SetBoomb(true);
                            Blocks[col - 1][row] = nullptr;
                            Score += 10 * Combo;                            
                        }
                        // ������ �߰� ����
                        if (col + matchCount < MapSize && Blocks[col + matchCount][row] != nullptr)
                        {
                            if (Blocks[col + matchCount][row]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col + matchCount][row]->SetBoomb(true);
                            Blocks[col + matchCount][row] = nullptr;
                            Score += 10 * Combo;                            
                        }
                    }                   
                    col += matchCount - 1; // �̹� �˻��� ����� �ǳʶٱ�
                }
            }
        }
        if (ComboAdd ==true)
        {
            ++Combo;
            ComboAdd = false;
        }


        // Y�� �˻�
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {
                if (Blocks[col][row] == nullptr) continue;

                AAnimal_Block* StartBlock = Blocks[col][row];
                int matchCount = 1;

                // �Ʒ��� ����� Ȯ���Ͽ� ���� Ÿ���� ����� �� �� �ִ��� ����
                for (int checkRow = row + 1; checkRow < MapSize; checkRow++)
                {
                    if (Blocks[col][checkRow] != nullptr && Blocks[col][checkRow]->GetBlockType() == StartBlock->GetBlockType())
                    {
                        matchCount++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (matchCount >= 3) // ������ �����ϴ� ���
                {
                    for (int Y = 0; Y < matchCount; Y++)
                    {
                        for (int X = -1; X <= 1; X++) // X ���� ����
                        {
                            // �迭 ������ ������� Ȯ��
                            if (col + X < 0 || col + X >= MapSize || row + Y >= MapSize)
                                continue;

                            // �⺻ ���� ����
                            if (Blocks[col + X][row + Y] != nullptr)
                            {
                                if (Blocks[col + X][row + Y]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                    continue;

                                Blocks[col + X][row + Y]->SetBoomb(true);
                                Blocks[col + X][row + Y] = nullptr;
                                Score += 10 * Combo;
                                ComboAdd = true;
                                ComboTimeCheck = false;
                            }
                        }
                    }

                    // ���� ��ġ�� ��� ��� �� ���� ���Ʒ� �߰� ����
                    if (col > 0 && col < MapSize - 1) // ���� üũ
                    {
                        // ���� �߰� ����
                        if (row > 0 && Blocks[col][row - 1] != nullptr)
                        {
                            if (Blocks[col][row - 1]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col][row - 1]->SetBoomb(true);
                            Blocks[col][row - 1] = nullptr;
                            Score += 10 * Combo;
                        }
                        // �Ʒ��� �߰� ����
                        if (row + matchCount < MapSize && Blocks[col][row + matchCount] != nullptr)
                        {
                            if (Blocks[col][row + matchCount]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col][row + matchCount]->SetBoomb(true);
                            Blocks[col][row + matchCount] = nullptr;
                            Score += 10 * Combo;
                        }
                    }                   
                    row += matchCount - 1; // �̹� �˻��� ����� �ǳʶٱ�
                }
            }
        }
        if (ComboAdd == true)
        {
            ++Combo;
            ComboAdd = false;
        }
    }
    else // �޺��� 5�̸� �϶� 
    {
        std::list<AAnimal_Block*> RowColBlockMatch;
        int Col_matchCount = 0;
        int Row_matchCount = 0;
     
        //X���� ��Ʈ����           
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {

                if (Blocks[col][row] == nullptr)
                    continue;

                AAnimal_Block* StartBlock = Blocks[col][row];
                Col_matchCount = 1;

                // ������ ����� Ȯ���Ͽ� ���� Ÿ���� ����� �� �� �ִ��� ����
                for (int checkCol = col + 1; checkCol < MapSize; checkCol++) {
                    if (Blocks[checkCol][row] != nullptr && Blocks[checkCol][row]->GetBlockType() == StartBlock->GetBlockType())
                    {
                        Col_matchCount++;
                    }
                    else
                    {
                        break;
                    }
                }

                // 3�� �̻� ������ ��� ��� ���� ��� ����
                if (Col_matchCount >= 3)
                {
                    for (int i = 0; i < Col_matchCount; i++)
                    {
                        RowColBlockMatch.push_back(Blocks[col + i][row]);
                        XLINE_Block_Destroy_Check = true;
                        //Blocks[col + i][row]->SetBoomb(true);
                        //Blocks[col + i][row] = nullptr;
                    }
                    //if (Combo == 0)
                    //{
                    //    Score += 10 * matchCount; // ���� ����
                    //}
                    //else
                    //{
                    //    Score += 10 * matchCount * Combo;
                    //}
                    //++Combo;
                    //ComboTimeCheck = false;
                    //col += matchCount - 1; // �̹� �˻��� ����� �ǳʶٱ�
                }
            }
            

            //Y���� ��Ʈ����
            for (int row = 0; row < MapSize; row++)
            {
                for (int col = 0; col < MapSize; col++)
                {
                    if (Blocks[col][row] == nullptr) continue;

                    AAnimal_Block* StartBlock = Blocks[col][row];
                    int Row_matchCount = 1;

                    // �Ʒ��� ����� Ȯ���Ͽ� ���� Ÿ���� ����� �� �� �ִ��� ����
                    for (int checkRow = row + 1; checkRow < MapSize; checkRow++) {
                        if (Blocks[col][checkRow] != nullptr && Blocks[col][checkRow]->GetBlockType() == StartBlock->GetBlockType())
                        {
                            Row_matchCount++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    // 3�� �̻� ������ ��� ��� ���� ��� ����
                    if (Row_matchCount >= 3)
                    {
                        for (int i = 0; i < Row_matchCount; i++)
                        {
                            RowColBlockMatch.push_back(Blocks[col][row + i]);
                            YLINE_Block_Destroy_Check = true;
                            //Blocks[col][row + i]->SetBoomb(true);
                            //Blocks[col][row + i] = nullptr;
                        }
                        //if (Combo == 0)
                        //{
                        //    Score += 10 * matchCount; // ���� ����
                        //}
                        //else
                        //{
                        //    Score += 10 * matchCount * Combo;
                        //}
                        //++Combo;
                        //ComboTimeCheck = false;
                        //row += matchCount - 1; // �̹� �˻��� ����� �ǳʶٱ�
                    }
                }
            }
           
        }

        if (YLINE_Block_Destroy_Check == true && XLINE_Block_Destroy_Check == true)
        {
            XYLINE_Block_Destroy_Check = true;
            if (XYLINE_Block_Destroy_Check == true)
            {
                for (AAnimal_Block* Animal : RowColBlockMatch)
                {
                    if (Blocks[Animal->GetBlockLocationCol()][Animal->GetBlockLocationRow()] == nullptr)
                    {
                        continue;
                    }
                    Blocks[Animal->GetBlockLocationCol()][Animal->GetBlockLocationRow()] = nullptr;
                    Animal->SetBoomb(true);
                    Animal = nullptr;
                }
                if (Combo == 0)
                {
                    Score += ((10 * Col_matchCount) + (10 * Row_matchCount)); // ���� ����
                }
                else
                {
                    Score += ((10 * Col_matchCount * Combo) + (10 * Row_matchCount * Combo));
                }
            }    
            ++Combo;
            ComboTimeCheck = false;
            YLINE_Block_Destroy_Check = false;
            XLINE_Block_Destroy_Check = false;
            XYLINE_Block_Destroy_Check = false;
        }
        else if (YLINE_Block_Destroy_Check == true)
        {
            for (AAnimal_Block* Animal : RowColBlockMatch)
            {
                if (Blocks[Animal->GetBlockLocationCol()][Animal->GetBlockLocationRow()] == nullptr)
                {
                    continue;
                }
                Blocks[Animal->GetBlockLocationCol()][Animal->GetBlockLocationRow()] = nullptr;
                Animal->SetBoomb(true);
                Animal = nullptr;
            }
            if (Combo == 0)
            {
                Score += ((10 * Col_matchCount) + (10 * Row_matchCount)); // ���� ����
            }
            else
            {
                Score += ((10 * Col_matchCount * Combo) + (10 * Row_matchCount * Combo));
            }
            ComboTimeCheck = false;
            YLINE_Block_Destroy_Check = false;
            XLINE_Block_Destroy_Check = false;
            XYLINE_Block_Destroy_Check = false;
            ++Combo;
        }
        else if (XLINE_Block_Destroy_Check == true)
        {
            for (AAnimal_Block* Animal : RowColBlockMatch)
            {
                if (Blocks[Animal->GetBlockLocationCol()][Animal->GetBlockLocationRow()] == nullptr)
                {
                    continue;
                }
                Blocks[Animal->GetBlockLocationCol()][Animal->GetBlockLocationRow()] = nullptr;
                Animal->SetBoomb(true);
                Animal = nullptr;
            }
            if (Combo == 0)
            {
                Score += ((10 * Col_matchCount) + (10 * Row_matchCount)); // ���� ����
               
            }
            else
            {
                Score += ((10 * Col_matchCount * Combo) + (10 * Row_matchCount * Combo));
               
            }
            ComboTimeCheck = false;
            YLINE_Block_Destroy_Check = false;
            XLINE_Block_Destroy_Check = false;
            XYLINE_Block_Destroy_Check = false;
            ++Combo;            
        }
    }
}

void UPlayLevel::BlockMove(float _DeltaTime)
{
    for (int row = 0; row < MapSize - 1; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            if (Blocks[col][row] == nullptr)
            {
                continue;
            }
            int count = 0;

            if (Blocks[col][row + 1] == nullptr)
            {
                if (Blocks[col][row]->GetUnderBoomb() == false)
                {
                    swap_block = Blocks[col][row];
                    FVector BeenBlockpos = Blocks[col][row]->GetBlockFVector(col, row + 1);

                    Blocks[col][row]->SetUnderPos(BeenBlockpos);
                    Blocks[col][row]->SetRow(row + 1);
                    Blocks[col][row]->SetUnderBoomb(true);
                    Blocks[col][row + 1] = Blocks[col][row];
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
            // �޺��� 10�̻� �϶� ��ź �� ����      
            int CheckCombo = Combo - ComboTens;
            if (CheckCombo >= 10)
            {
                Blocks[col][0] = SpawnActor<ABoomb_Block>();
                ComboTens=  Combo;
            }
            else
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

void UPlayLevel::BlockMoveCheck()
{
    int count = 0;

    for (int row = 0; row < MapSize - 1; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            if (Blocks[col][row] == nullptr)
            {
                ++count;
            }
        }
    }

    for (int row = 0; row < MapSize - 1; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            if (Blocks[col][row] == nullptr)
            {
                continue;
            }
            if (Blocks[col][row]->GetUnderBoomb() == true)
            {
                ++count;
            }
        }
    }

    if (count >= 1)
    {
        BlockDestroyAllow = false;
        CheckMatch = false;
    }
    else if (count == 0)
    {
        BlockDestroyAllow = true;
        CheckMatch = true;
    }
}


void UPlayLevel::AllDestroyCheck()
{
    for (int row = 0; row < MapSize; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            bool Boomb = true;
            Blocks[col][row]->SetBoomb(Boomb);
            Blocks[col][row] = nullptr;
        }
    }
    Hint_block = nullptr;
    HintBlock = false;
    AllDestroy = true;
}

void UPlayLevel::TestClick()
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

                if (Blocks[col][row]->GetFirstPick() == true && AAnimal_Block::GetFirstClick() == true)
                {
                    click_block = Blocks[col][row];
                    Clickpos = click_block->GetActorLocation();
                }

                if (Blocks[col][row]->GetSecondPick() == true && AAnimal_Block::GetSecondClick() == true)
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
        //Clickpos = click_block->GetActorLocation();
        //Swappos = swap_block->GetActorLocation();

        int clickRow = click_block->GetBlockLocation().Row;
        int clickCol = click_block->GetBlockLocation().Column;
        int swapkRow = swap_block->GetBlockLocation().Row;
        int swapCol = swap_block->GetBlockLocation().Column;


        bool _set = false;
        FVector TempPos = Clickpos;
        click_block->SetActorLocation(Swappos);
        swap_block->SetActorLocation(TempPos);

        click_block->SetBlockstate(_set, 1);
        swap_block->SetBlockstate(_set, 2);
        click_block->SetColumn(swapCol);
        click_block->SetRow(swapkRow);
        swap_block->SetColumn(clickCol);
        swap_block->SetRow(clickRow);

        AAnimal_Block* Temp_Block = Blocks[clickCol][clickRow];
        Blocks[clickCol][clickRow] = Blocks[swapCol][swapkRow];
        Blocks[swapCol][swapkRow] = Temp_Block;


        AAnimal_Block::SwapREADY = false;
        AAnimal_Block::SwapChange = false;
        AAnimal_Block::ClickChange = false;
        ClickChangeCheck = true;        
    }
}

void UPlayLevel::Test_BlockMoveMode()
{
    if (Test_BlockMove_Mode == false)
    {
        Timer->Test_BlockMove_Mode_Off();
        BlockMoveMode_Font->Destroy(0.f);
        BlockMoveMode_Font = nullptr;
    }
    else
    {
        BlockMoveMode_Font = SpawnActor<ANumberFont>();
        BlockMoveMode_Font->SetFont("���̵� ���", 35);
        BlockMoveMode_Font->SetFontColor(Color8Bit::Black, Color8Bit::Red);
        BlockMoveMode_Font->SetActorLocation({ 250,120 });
        BlockMoveMode_Font->FonRenderNumber(99);
        Timer->Test_BlockMove_Mode_On();
    }
}

void UPlayLevel::Test_TimeStop_Mode()
{
    if (UEngineInput::IsDown(VK_F8))
    {
        if (Test_TimeStop_Switch == false)
        {
            Timer->TimeStopOn();
            Test_TimeStop_Switch = true;
            TimeStopMode_Font = SpawnActor<ANumberFont>();
            TimeStopMode_Font->SetFont("Timer_OFF", 35);
            TimeStopMode_Font->SetFontColor(Color8Bit::Black, Color8Bit::Red);
            TimeStopMode_Font->SetActorLocation({ 235,155 });
            TimeStopMode_Font->FonRenderNumber(99);
        }
        else
        {
            Timer->TimeStopOff();
            Test_TimeStop_Switch = false;
            TimeStopMode_Font->Destroy(0.f);
            TimeStopMode_Font = nullptr;
        }
    }
}

void UPlayLevel::Manual_Switch()
{
    if (UEngineInput::IsDown(VK_F2))
    {
        ManualSwitch = !ManualSwitch;

        if (ManualSwitch == true)
        {
            Manual = SpawnActor<AManual>();
            Manual->SetActorLocation({ 235,155 });
        }
        else
        {
            Manual->Destroy(0.f);
            Manual = nullptr;
        }
    }
}

void UPlayLevel::InputKey_DestroyBlock()
{
    if (true == UEngineInput::IsDown(VK_F7))
    {
        AllDestroy = true;
    }
    if (AllDestroy == true)
    {
        AllDestroyCheck();
        CreateBlock();
        AllDestroy = false;
    }
}

