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
                        //클릭으로 이동된 블럭 3Match가 되는지 판단하는 검사로직
                        XlineBlock_Swap_Check(_DeltaTime);
                        XlineBlock_Swap_Move(_DeltaTime);
                        ////검사된 블럭의 return 또는 stay를 나타내는 실행로직
                        YlineBlock_Swap_Check(_DeltaTime);
                        YlineBlock_Swap_Move(_DeltaTime);

                        //수정블럭이동
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
            // 동물 블록 생성
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

            // 스왑할 수 있는 두 방향: 오른쪽과 아래
            int directions[2][2] = { {0, 1}, {1, 0} };

            for (auto& dir : directions)
            {
                int newRow = row + dir[1];
                int newCol = col + dir[0];

                // 새 위치가 보드 내에 있는지 확인
                if (newRow < MapSize && newCol < MapSize && Blocks[newCol][newRow] != nullptr)
                {
                    // 블록을 스왑
                    AAnimal_Block* temp = Blocks[col][row];
                    Blocks[col][row] = Blocks[newCol][newRow];
                    Blocks[newCol][newRow] = temp;

                    // 스왑 후 매치가 있는지 확인
                    if (CheckForMatch(col, row) == true || CheckForMatch(newCol, newRow) == true)
                    {
                        // 원상태로 복구
                        Blocks[newCol][newRow] = Blocks[col][row];
                        Blocks[col][row] = temp;
                        return true; // 한 번의 움직임으로 매치 가능
                    }

                    // 원상태로 복구
                    Blocks[newCol][newRow] = Blocks[col][row];
                    Blocks[col][row] = temp;
                }
            }
        }
    }
    return false; // 어떤 움직임으로도 3개 이상의 매치를 만들 수 없음
}

bool UPlayLevel::CheckForMatch(int _col, int _row)
{
    if(HintBlock == false)
    {
        if (Blocks[_col][_row] == nullptr)
            return false;

        AAnimal_Block::Block_Type CheckBL = Blocks[_col][_row]->GetBlockType();
        int matchCount = 1; // 시작 블록을 포함하여 카운트 시작

        // 수평 방향 검사 (왼쪽)
        for (int i = _col - 1; i >= 0 && Blocks[i][_row] != nullptr && Blocks[i][_row]->GetBlockType() == CheckBL; i--)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3매치 발생 시 현재 블록 저장
                }
            }
        }
        // 수평 방향 검사 (오른쪽)
        for (int i = _col + 1; i < MapSize && Blocks[i][_row] != nullptr && Blocks[i][_row]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3매치 발생 시 현재 블록 저장
                }
            }
        }
        if (matchCount >= 3)
        {
            return true; // 수평 방향으로 3개 이상 일치
        }

        matchCount = 1; // 카운트 초기화 후 수직 방향 검사

        // 수직 방향 검사 (위)
        for (int i = _row - 1; i >= 0 && Blocks[_col][i] != nullptr && Blocks[_col][i]->GetBlockType() == CheckBL; i--)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3매치 발생 시 현재 블록 저장
                }
            }
        }
        // 수직 방향 검사 (아래)
        for (int i = _row + 1; i < MapSize && Blocks[_col][i] != nullptr && Blocks[_col][i]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;
            if (matchCount == 3)
            {
                if (Hint_block == nullptr)
                {
                    Hint_block = Blocks[_col][_row]; // 3매치 발생 시 현재 블록 저장
                }
            }
        }
        if (matchCount >= 3)
        {
            return true; // 수직 방향으로 3개 이상 일치
        }
    }
    else
    {
        int HIINTCOL = Hint_block->GetBlockLocationCol();
        int HIINTROW = Hint_block->GetBlockLocationRow();

        if (Blocks[HIINTCOL][HIINTROW] == nullptr)
            return false;

        AAnimal_Block::Block_Type CheckBL = Blocks[HIINTCOL][HIINTROW]->GetBlockType();
        int matchCount = 1; // 시작 블록을 포함하여 카운트 시작

        // 수평 방향 검사 (왼쪽)
        for (int i = HIINTCOL - 1; i >= 0 && Blocks[i][HIINTROW] != nullptr && Blocks[i][HIINTROW]->GetBlockType() == CheckBL; i--)
        {
            matchCount++; 
        }
        // 수평 방향 검사 (오른쪽)
        for (int i = HIINTCOL + 1; i < MapSize && Blocks[i][HIINTROW] != nullptr && Blocks[i][HIINTROW]->GetBlockType() == CheckBL; i++)
        {
            matchCount++;     
        }
        if (matchCount >= 3)
        {
            return true; // 수평 방향으로 3개 이상 일치
        }

        matchCount = 1; // 카운트 초기화 후 수직 방향 검사

        // 수직 방향 검사 (위)
        for (int i = HIINTROW - 1; i >= 0 && Blocks[HIINTCOL][i] != nullptr && Blocks[HIINTCOL][i]->GetBlockType() == CheckBL; i--)
        {
            matchCount++;
        }
        // 수직 방향 검사 (아래)
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
    return false; // 수평 또는 수직 방향에서 3개 이상 일치하는 블록이 없음
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
    // 현재 블록의 타입 가져오기
    if (Blocks[col][row] == nullptr) // 현재 위치에 블록이 없다면 검사하지 않음
    {
        return false;
    }
    AAnimal_Block::Block_Type currentType = Blocks[col][row]->GetBlockType();

    // 수평 방향 매치 검사
    int horizontalMatchCount = 1; // 현재 블록 포함
    // 왼쪽으로 검사
    for (int i = col - 1; i >= 0 && i >= col - 2; --i) {
        if (Blocks[i][row] != nullptr && Blocks[i][row]->GetBlockType() == currentType)
        {
            horizontalMatchCount++;
        }
        else
        {
            break; // 연속되지 않으면 중단
        }
    }
    // 오른쪽으로 검사
    for (int i = col + 1; i < MapSize && i <= col + 2; ++i) {
        if (Blocks[i][row] != nullptr && Blocks[i][row]->GetBlockType() == currentType) {
            horizontalMatchCount++;
        }
        else 
        {
            break; // 연속되지 않으면 중단
        }
    }
    if (horizontalMatchCount >= 3) return true; // 3개 이상 연속되면 true 반환

    // 수직 방향 매치 검사
    int verticalMatchCount = 1; // 현재 블록 포함
    // 위로 검사
    for (int i = row - 1; i >= 0 && i >= row - 2; --i) {
        if (Blocks[col][i] != nullptr && Blocks[col][i]->GetBlockType() == currentType) {
            verticalMatchCount++;
        }
        else
        {
            break; // 연속되지 않으면 중단
        }
    }
    // 아래로 검사
    for (int i = row + 1; i < MapSize && i <= row + 2; ++i) {
        if (Blocks[col][i] != nullptr && Blocks[col][i]->GetBlockType() == currentType) {
            verticalMatchCount++;
        }
        else
        {
            break; // 연속되지 않으면 중단
        }
    }
    if (verticalMatchCount >= 3) return true; // 3개 이상 연속되면 true 반환

    // 수평 및 수직 매치 모두 없으면 false 반환
    return false;
}


void UPlayLevel::XlineBlock_Swap_Check(float _DeltaTime)
{
    if (XSWAPMOVE && XCLICKMOVE)
    {
        // 클릭된 블록과 교환된 블록의 위치를 확인
        int clickRow = click_block->GetBlockLocation().Row;
        int clickCol = click_block->GetBlockLocation().Column;
        int swapCol = swap_block->GetBlockLocation().Column;

        // 클릭된 블록과 교환된 블록 주위의 3-match 검사
        bool clickMatchFound = CheckMatchAroundBlock(clickCol, clickRow);
        bool swapMatchFound = CheckMatchAroundBlock(swapCol, clickRow);

        // 결과에 따라 상태 업데이트
        XLINE_ChageCheck = (clickMatchFound || swapMatchFound) ? BlockChangeSuccess : BlockChangeFail;
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
    else if (XLINE_ChageCheck == BlockChangeSuccess)   // 검사 성공
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
        // 클릭된 블록과 교환된 블록의 위치를 확인
        int clickRow = click_block->GetBlockLocation().Row;
        int clickCol = click_block->GetBlockLocation().Column;
        int swapRow = swap_block->GetBlockLocation().Row;

        // 클릭된 블록과 교환된 블록 주위의 3-match 검사
        bool clickMatchFound = CheckMatchAroundBlock(clickCol, clickRow);
        bool swapMatchFound = CheckMatchAroundBlock(clickCol, swapRow);

        // 결과에 따라 상태 업데이트
        YLINE_ChageCheck = (clickMatchFound || swapMatchFound) ? BlockChangeSuccess : BlockChangeFail;
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
    else if (YLINE_ChageCheck == BlockChangeSuccess)   // 검사 성공
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
                    Score += 10; // 점수 증가
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
    //콤보가 5이상 일때
    if (Combo >= ComboBoombCheck)
    {
        // X축 검사
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {
                if (Blocks[col][row] == nullptr)
                    continue;

                AAnimal_Block* StartBlock = Blocks[col][row];
                int matchCount = 1;

                // 오른쪽 블록을 확인하여 같은 타입의 블록이 몇 개 있는지 세기
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

                if (matchCount >= 3) // 조건을 충족하는 경우
                {
                    Score += (10 * matchCount) * (Combo + 1);

                    for (int Y = -1; Y <= 1; Y++) // Y 범위 수정
                    {
                        for (int X = 0; X < matchCount; X++)
                        {
                            // 배열 범위를 벗어나는지 확인
                            if (col + X >= MapSize || row + Y < 0 || row + Y >= MapSize)
                                continue;

                            // 기본 폭발 로직
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

                    // 가로 매치의 경우 가운데 줄 기준 양옆 추가 폭발
                    if (row > 0 && row < MapSize - 1) // 범위 체크
                    {
                        // 왼쪽 추가 폭발
                        if (col > 0 && Blocks[col - 1][row] != nullptr)
                        {
                            if (Blocks[col - 1][row]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col - 1][row]->SetBoomb(true);
                            Blocks[col - 1][row] = nullptr;
                            Score += 10 * Combo;                            
                        }
                        // 오른쪽 추가 폭발
                        if (col + matchCount < MapSize && Blocks[col + matchCount][row] != nullptr)
                        {
                            if (Blocks[col + matchCount][row]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col + matchCount][row]->SetBoomb(true);
                            Blocks[col + matchCount][row] = nullptr;
                            Score += 10 * Combo;                            
                        }
                    }                   
                    col += matchCount - 1; // 이미 검사한 블록은 건너뛰기
                }
            }
        }
        if (ComboAdd ==true)
        {
            ++Combo;
            ComboAdd = false;
        }


        // Y축 검사
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {
                if (Blocks[col][row] == nullptr) continue;

                AAnimal_Block* StartBlock = Blocks[col][row];
                int matchCount = 1;

                // 아래쪽 블록을 확인하여 같은 타입의 블록이 몇 개 있는지 세기
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

                if (matchCount >= 3) // 조건을 충족하는 경우
                {
                    for (int Y = 0; Y < matchCount; Y++)
                    {
                        for (int X = -1; X <= 1; X++) // X 범위 수정
                        {
                            // 배열 범위를 벗어나는지 확인
                            if (col + X < 0 || col + X >= MapSize || row + Y >= MapSize)
                                continue;

                            // 기본 폭발 로직
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

                    // 세로 매치의 경우 가운데 줄 기준 위아래 추가 폭발
                    if (col > 0 && col < MapSize - 1) // 범위 체크
                    {
                        // 위쪽 추가 폭발
                        if (row > 0 && Blocks[col][row - 1] != nullptr)
                        {
                            if (Blocks[col][row - 1]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col][row - 1]->SetBoomb(true);
                            Blocks[col][row - 1] = nullptr;
                            Score += 10 * Combo;
                        }
                        // 아래쪽 추가 폭발
                        if (row + matchCount < MapSize && Blocks[col][row + matchCount] != nullptr)
                        {
                            if (Blocks[col][row + matchCount]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                                continue;

                            Blocks[col][row + matchCount]->SetBoomb(true);
                            Blocks[col][row + matchCount] = nullptr;
                            Score += 10 * Combo;
                        }
                    }                   
                    row += matchCount - 1; // 이미 검사한 블록은 건너뛰기
                }
            }
        }
        if (ComboAdd == true)
        {
            ++Combo;
            ComboAdd = false;
        }
    }
    else // 콤보가 5미만 일때 
    {
        std::list<AAnimal_Block*> RowColBlockMatch;
        int Col_matchCount = 0;
        int Row_matchCount = 0;
     
        //X라인 터트리기           
        for (int row = 0; row < MapSize; row++)
        {
            for (int col = 0; col < MapSize; col++)
            {

                if (Blocks[col][row] == nullptr)
                    continue;

                AAnimal_Block* StartBlock = Blocks[col][row];
                Col_matchCount = 1;

                // 오른쪽 블록을 확인하여 같은 타입의 블록이 몇 개 있는지 세기
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

                // 3개 이상 연속일 경우 모든 연속 블록 제거
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
                    //    Score += 10 * matchCount; // 점수 증가
                    //}
                    //else
                    //{
                    //    Score += 10 * matchCount * Combo;
                    //}
                    //++Combo;
                    //ComboTimeCheck = false;
                    //col += matchCount - 1; // 이미 검사한 블록은 건너뛰기
                }
            }
            

            //Y라인 터트리기
            for (int row = 0; row < MapSize; row++)
            {
                for (int col = 0; col < MapSize; col++)
                {
                    if (Blocks[col][row] == nullptr) continue;

                    AAnimal_Block* StartBlock = Blocks[col][row];
                    int Row_matchCount = 1;

                    // 아래쪽 블록을 확인하여 같은 타입의 블록이 몇 개 있는지 세기
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

                    // 3개 이상 연속일 경우 모든 연속 블록 제거
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
                        //    Score += 10 * matchCount; // 점수 증가
                        //}
                        //else
                        //{
                        //    Score += 10 * matchCount * Combo;
                        //}
                        //++Combo;
                        //ComboTimeCheck = false;
                        //row += matchCount - 1; // 이미 검사한 블록은 건너뛰기
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
                    Score += ((10 * Col_matchCount) + (10 * Row_matchCount)); // 점수 증가
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
                Score += ((10 * Col_matchCount) + (10 * Row_matchCount)); // 점수 증가
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
                Score += ((10 * Col_matchCount) + (10 * Row_matchCount)); // 점수 증가
               
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
            // 콤보가 10이상 일때 폭탄 블럭 생성      
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
        BlockMoveMode_Font->SetFont("블럭이동 모드", 35);
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

