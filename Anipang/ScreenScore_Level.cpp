#include "ScreenScore_Level.h"
#include <EngineCore\EngineCore.h>
#include "FadeIN_OUT.h"
#include "Score_BackGround.h"
#include "ScoreBoard.h"
#include "Cursor.h"
#include "ScoreManager.h"
#include "Screen_Score_Board.h"

#include "GameStart_UI.h"
#include "CheckScore_UI.h"
#include "GameEnd_UI.h"
#include "MainScreen_UI.h"

#include "NumberFont.h"


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
#include "ScoreManager.h"


UScreenScore_Level::UScreenScore_Level()
{
}

UScreenScore_Level::~UScreenScore_Level()
{
    for (ScoreRecord* check : check_list)
    {
        delete check;
    }
}

void UScreenScore_Level::BeginPlay()
{
	ULevel::BeginPlay();
	SpawnActor<AScore_BackGround>();
	Cursor = SpawnActor<ACursor>();

	AGameStart_UI* GameStartUI = SpawnActor<AGameStart_UI>();
	GameStartUI->SetActorLocation({ 240,590 });
	GameStartUI->SetCursor(Cursor);


	AMainScreen_UI* ScoreUI = SpawnActor<AMainScreen_UI>();
	ScoreUI->SetActorLocation({ 240,638 });
	ScoreUI->SetCursor(Cursor);


	AGameEnd_UI* GameendUI = SpawnActor<AGameEnd_UI>();
	GameendUI->SetActorLocation({ 240,686 });
	GameendUI->SetCursor(Cursor);


	AScreen_Score_Board* Score_Board = SpawnActor<AScreen_Score_Board>();
	Score_Board->SetActorLocation({ 240,285 });

	{
		ANumberFont* font = SpawnActor<ANumberFont>();
		font->SetActorLocation({ 107,410 });
		font->SetFont("4.", 40.f);
	}
	{
		ANumberFont* font = SpawnActor<ANumberFont>();
		font->SetActorLocation({ 107,500 });
		font->SetFont("5.", 40.f);
	}
}


void UScreenScore_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UScreenScore_Level::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
	Play_Game_Sound = UEngineSound::SoundPlay("Anipang_Title_Music.mp3");

    SettingScore();
}

void UScreenScore_Level::LevelEnd(ULevel* _Level)
{
	Play_Game_Sound.Off();

    if (check_list.empty() == false)
    {        
        for (int Num = 0; Num < 5; Num++)
        {
            font[Num]->Destroy();
            font[Num] = nullptr;
        }
        for (ScoreRecord* check : check_list)
        {            
            delete check;
        }
        check_list.clear();
    }
    count = 0;
}

void UScreenScore_Level::SettingScore()
{
    {
        UEngineDirectory NewDir;
        NewDir.MoveToSearchChild("ContentsResources");
        std::fstream fs;
        std::string str_buf;

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
            score = std::stoi(item); 

            // ���� �����ͷ� ScoreManager ��ü ����
            ScoreRecord* newScoreManager = new ScoreRecord(num, name, score);
            // ����Ʈ�� �߰�
            check_list.push_back(newScoreManager);
        }
        // ���� �ݱ�
        fs.close();
    }
    for (ScoreRecord* sm : check_list)
    {
        int num = sm->Num;
        int score = sm->Score;

        std::string name = sm->Name + " : " + std::to_string(score);

        font[count] = SpawnActor<ANumberFont>();
        font[count]->SetActorLocation({ 150,140 + 90 * count });
        font[count]->SetFont(name, 40.f);


        if (count == 0)
        {            
            font[count]->SetFontColor(Color8Bit::White, Color8Bit::Orange);
        }
        font[count]->FontCenterOff();
        ++count;
    }   
}
