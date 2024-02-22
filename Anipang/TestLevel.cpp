#include "TestLevel.h"
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

#include "BoombBlock_Effect.h"
#include "Boomb_Block_Effect.h"
#include "Helper.h"


TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{
    ULevel::BeginPlay();
    //SpawnActor<APlay_Frame>();
    Cursor = SpawnActor<ACursor>();
   // CreateBlock();
    ABoombBlock_Effect* Test =  SpawnActor<ABoombBlock_Effect>();
    Test->SetActorLocation({240,480});


    // Foot_1_1.wav
    //BGMPlayer = UEngineSound::SoundPlay("Foot_1_1.wav");
    //BGMPlayer.Loop();
    // BGMPlayer = UEngineSound::SoundPlay("anipang_ingame_wav.wav");
    // BGMPlayer.Off();


}

void TestLevel::Tick(float _DeltaTime)
{
    ULevel::Tick(_DeltaTime);

    if (UEngineInput::IsDown(VK_F3))
    {
        BGMPlayer.OnOffSwitch();
    }


    {
        for (int row = 0; row < MapSize; ++row)
        {
            for (int col = 0; col < MapSize; ++col)
            {
                if (Blocks[col][row] == nullptr)
                    continue;

                if (Blocks[col][row]->GetBlockType() == AAnimal_Block::Block_Type::Boomb)
                    continue;


                if (Blocks[col][row]->Check_Boomb_Effect_Toutch() == true)
                {
                    Blocks[col][row]->SetBoomb(true);
                    Blocks[col][row] = nullptr;
                }
            }
        }
    }

    if (true == UEngineInput::IsDown('1'))
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

void TestLevel::LevelStart(ULevel* _Level)
{
}

void TestLevel::LevelEnd(ULevel* _Level)
{
}

void TestLevel::CreateBlock()
{
    for (int row = 0; row < MapSize; ++row)
    {
        for (int col = 0; col < MapSize; ++col)
        {
            if ((col == 0 && row == 0) || 
                (col == 0 && row == MapSize - 1) ||
                (col == MapSize - 1 && row == 0) || 
                (col == MapSize - 1 && row == MapSize - 1)||
                (row == 3 && col == 3))
            {
                Blocks[col][row] = SpawnActor<ABoomb_Block>();              
            }           
            else
            {
                Blocks[col][row] = SpawnActor<ACat_Block>();
            }

            // ���� ��� ����           
            /*int random = 0;
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
            }*/
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

void TestLevel::AllDestroyCheck()
{
    for (int row = 0; row < MapSize; row++)
    {
        for (int col = 0; col < MapSize; col++)
        {
            if (Blocks[col][row] == nullptr)
                continue;

            bool Boomb = true;
            Blocks[col][row]->SetBoomb(Boomb);
            Blocks[col][row] = nullptr;
        }
    }
    AllDestroy = true;
}
