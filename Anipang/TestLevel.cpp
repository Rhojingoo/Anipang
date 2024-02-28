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

//파일 입출력
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineSerializer.h>
#include <EngineBase\EngineFile.h>
//
//파일입출력 수정하는 기능
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <sstream> // std::stringstream 사용을 위해 추가
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

        // 읽기 모드로 파일 열기
        fs.open(NewFile.GetFullPath(), std::ios::in);     

        // 첫 줄은 헤더이므로 먼저 읽고 버립니다.
        std::getline(fs, str_buf);

        // 파일 끝까지 읽기
        while (std::getline(fs, str_buf))
        {
            std::stringstream ss(str_buf); // 읽은 줄을 스트링스트림으로 변환
            std::string item;
            int num, score;
            std::string name;
            std::string text;

            // 쉼표를 구분자로 사용하여 파싱
            std::getline(ss, item, ',');
            num = std::stoi(item); // 문자열을 정수로 변환

            std::getline(ss, name, ',');

            std::getline(ss, item, ',');
            score = std::stoi(item); // 문자열을 정수로 변환

            // 읽은 데이터로 ScoreManager 객체 생성
            Scoremanager* newScoreManager = new Scoremanager(num, name, score);
            // 리스트에 추가
            check_list.push_back(newScoreManager);
        }
        // 파일 닫기
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
        //std::string Text = "파일저장 시도";
        //std::string Text2 = "파일저장 잘되나요?";
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

            //// 리스트 출력 확인
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
            //        // 키업데이트로 변경 해서 넣어주기
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

            // 동물 블록 생성           
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
