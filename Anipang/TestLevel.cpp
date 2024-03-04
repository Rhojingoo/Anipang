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

//���� �����
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineSerializer.h>
#include <EngineBase\EngineFile.h>
//
//��������� �����ϴ� ���
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <sstream> // std::stringstream ����� ���� �߰�
#include "NumberFont.h"
#include "ScreenScore_Level.h"
#include "ScoreManager.h"


TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
    for (ScoreRecord* check : check_list)
    {
        delete check;
    }
}

void TestLevel::BeginPlay()
{
    ULevel::BeginPlay();
    //SpawnActor<APlay_Frame>();
    Cursor = SpawnActor<ACursor>();
    //CreateBlock();
    

    //NewDir.Move("Save");
    {
        //std::string Text = "�������� �õ�";
        //std::string Text2 = "�������� �ߵǳ���?";
        //int SetA = 20;
        //int SetB = 20;

        //UEngineFile NewFile = NewDir.NewFile("TEST.txt");
        //UEngineSerializer Ser;
        //Ser << Text;
        //Ser << Text2;
       // Ser << SetA;
        //Ser << SetB;   

        //NewFile.Open(IOOpenMode::Write, IODataType::Text);
        //NewFile.Save(Ser);

        //int a = 0;
    }

    {
    //    std::string Text;
    //    std::string Text2;
    //    int SetA = 0;

    //    UEngineSerializer Ser;

    //    UEngineFile NewFile = NewDir.NewFile("TEST.txt");
    //    NewFile.Open(IOOpenMode::Read, IODataType::Text);
    //    NewFile.Load(Ser);

    //    Ser >> SetA;
    //    //Ser >> Text;
    //    //Ser >> Text2;

    //    int a = 0;
    }
}

void TestLevel::Tick(float _DeltaTime)
{
    ULevel::Tick(_DeltaTime);

    //if (UEngineInput::IsDown(VK_F3))
    //{
    //    BGMPlayer.OnOffSwitch();
    //}


 /*   {
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
    }*/
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

void TestLevel::InputCheck()
{    
    if (UEngineInput::IsDown(VK_BACK))
    {
        if (!TextInput.empty()) 
        { // teststring�� ������� ���� ���
            TextInput.erase(TextInput.size() - 1); // ������ ���ڸ� ����
            Input_Text = true;
        }
    }
    if (UEngineInput::IsDown(VK_RETURN))
    {
        int a = 0;
    }
    
    if (UEngineInput::IsDown('Q'))
    {
        TextInput += 'Q';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('W'))
    {
        TextInput += 'W';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('E'))
    {
        TextInput += 'E';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('R'))
    {
        TextInput += 'R';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('T'))
    {
        TextInput += 'T';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('Y'))
    {
        TextInput += 'Y';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('U'))
    {
        TextInput += 'U';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('I')) 
    {
        TextInput += 'I';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('O')) 
    {
        TextInput += 'O';
        Input_Text = true;
    }

    if (UEngineInput::IsDown('P')) 
    {
        TextInput += 'P';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('A')) 
    {
        TextInput += 'A';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('S')) 
    {
        TextInput += 'S';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('D')) 
    {
        TextInput += 'D';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('F')) 
    {
        TextInput += 'F';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('G')) 
    {
        TextInput += 'G';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('H')) 
    {
        TextInput += 'H';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('J')) 
    {
        TextInput += 'J';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('K')) 
    {
        TextInput += 'K';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('L')) 
    {
        TextInput += 'L';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('Z')) 
    {
        TextInput += 'Z';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('X')) 
    {
        TextInput += 'X';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('C')) 
    {
        TextInput += 'C';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('V')) 
    {
        TextInput += 'V';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('B')) 
    {
        TextInput += 'B';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('N')) 
    {
        TextInput += 'N';
        Input_Text = true;
    }
    if (UEngineInput::IsDown('M')) 
    {
        TextInput += 'M';
        Input_Text = true;
    }
}
