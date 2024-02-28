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


TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
    for (Scoremanager* check : check_list)
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


    {
        UEngineDirectory NewDir;
        NewDir.MoveToSearchChild("ContentsResources");
        std::fstream fs;
        std::string str_buf;
        check_list;

        UEngineFile NewFile = NewDir.NewFile("ScoreSheet.csv");    
        std::string test = NewFile.GetFullPath();

        // �б� ���� ���� ����
        fs.open(NewFile.GetFullPath(), std::ios::in);     

        // ù ���� ����̹Ƿ� ���� �а� �����ϴ�.
        std::getline(fs, str_buf);

        // ���� ������ �б�
        while (std::getline(fs, str_buf))
        {
            std::stringstream ss(str_buf); // ���� ���� ��Ʈ����Ʈ������ ��ȯ
            std::string item;
            int num, score;
            std::string name;
            std::string text;

            // ��ǥ�� �����ڷ� ����Ͽ� �Ľ�
            std::getline(ss, item, ',');
            num = std::stoi(item); // ���ڿ��� ������ ��ȯ

            std::getline(ss, name, ',');

            std::getline(ss, item, ',');
            score = std::stoi(item); // ���ڿ��� ������ ��ȯ

            // ���� �����ͷ� ScoreManager ��ü ����
            Scoremanager* newScoreManager = new Scoremanager(num, name, score);
            // ����Ʈ�� �߰�
            check_list.push_back(newScoreManager);
        }
        // ���� �ݱ�
        fs.close();    
    }
    for (Scoremanager* sm : check_list)
    {
        int num = sm->Num;
        int score = sm->Score;
        std::string name = sm->Name + " : ";
        font[count] = SpawnActor<ANumberFont>();
        font[count] -> SetActorLocation({ 110,100 + 100* count });
        font[count] -> SetFont(name + " : ", 40.f);
        font[count];
        ++count;
    }

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

    if (UEngineInput::IsDown(VK_F2))
    {
        UEngineDirectory NewDir;
        NewDir.MoveToSearchChild("ContentsResources");

        UEngineFile NewFile = NewDir.NewFile("ScoreSheet.csv");

        {
            //int score = 1500;
            //int temp = 0;
            //std::string nametemp;
            //bool change = false;

            //// ����Ʈ ��� Ȯ��
            //for (Scoremanager* sm : check_list)
            //{
            //    if (change == true)
            //    {
            //        int change = temp;
            //        temp = sm->Score;
            //        sm->Score = change;

            //        std::string changename = nametemp;
            //        nametemp = sm->Name;
            //        sm->Name = changename;
            //        continue;
            //    }

            //    if (sm->Score < score)
            //    {
            //        temp = sm->Score;
            //        sm->Score = score;
            //        std::string asd;
            //        // Ű������Ʈ�� ���� �ؼ� �־��ֱ�
            //        nametemp = sm->Name;
            //        std::cin >> asd;
            //        sm->Name = asd;
            //        change = true;
            //        continue;
            //    }
            //    //std::cout << sm.Num << ", " << sm.Name << ", " << sm.Score << std::endl;
            //}


            //{
            //    fs.open("D:\\ScoreSheet1.csv", std::ios::out);
            //    fs << "Num,Name,Score\n";
            //    for (Scoremanager* sm : check_list)
            //    {
            //        int Num = sm->Num;
            //        std::string Name = sm->Name;
            //        int Score = sm->Score;
            //        fs << Num << "," << Name << "," << Score << std::endl;
            //    }
            //}
            //fs.close();    
        }
    }
    

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
