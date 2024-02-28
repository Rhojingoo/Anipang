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
	//SpawnActor<AScoreBoard>();
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

    //ScoreMN = SpawnActor<ScoreManager>();
    //ScoreMN->Screen_ScoreLevel_On();


	{
		ANumberFont* font = SpawnActor<ANumberFont>();
		font->SetActorLocation({ 75,410 });
		font->SetFont("4.", 40.f);
	}
	{
		ANumberFont* font = SpawnActor<ANumberFont>();
		font->SetActorLocation({ 75,500 });
		font->SetFont("5.", 40.f);
	}

    SettingScore();
    //Begin = true;
}


void UScreenScore_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);


    if (InputName == true)
    {
        InputCheck();
        if (Input_Text == true)
        {
            if (!TextInput.empty())
            {
                Input_Font->SetFont(TextInput, 40.f);
            }
            else
            {
                Input_Font->SetFont("입력하세요", 40.f);
            }
            Input_Text = false;
        }
    }

    if (ScoreReset == true)
    {
        if (Input_Font != nullptr)
        {
            Input_Font->Destroy();
        }
        ResetScore(Score);
    }
}

void UScreenScore_Level::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
	Play_Game_Sound = UEngineSound::SoundPlay("Anipang_Title_Music.mp3");

    //Score = ScoreManager::GetScore();
    Score = 15000;

    if (Score > 0)
    {
        ScoreCheck(Score);
    }
}

void UScreenScore_Level::LevelEnd(ULevel* _Level)
{
	Play_Game_Sound.Off();
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
            score = std::stoi(item); 

            // 읽은 데이터로 ScoreManager 객체 생성
            ScoreRecord* newScoreManager = new ScoreRecord(num, name, score);
            // 리스트에 추가
            check_list.push_back(newScoreManager);
        }
        // 파일 닫기
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
        font[count]->FontCenterSwitch();
        ++count;
    }
}

void UScreenScore_Level::ScoreCheck(int _score)
{
    int scorecheck = _score;

    for (ScoreRecord* sm : check_list)
    {
        if (sm->Score < scorecheck)
        {           
            InputName = true;
            Input_Font = SpawnActor<ANumberFont>();
            Input_Font->FontCenterSwitch();
            Input_Font->SetActorLocation({ 110,400 });
            Input_Font->SetFont("입력하세요", 40.f);     
            return;
        }
    }
}

void UScreenScore_Level::ResetScore(int _score)
{
    //변경중
    int score = _score;
    int temp = 0;
    std::string nametemp;
    bool change = false;

    for (ScoreRecord* sm : check_list)
    {
        if (change == true)
        {
            int change = temp;
            temp = sm->Score;
            sm->Score = change;
            std::string changename = nametemp;
            nametemp = sm->Name;
            sm->Name = changename;
            continue;
        }

        if (sm->Score < score)
        {
            temp = sm->Score;
            sm->Score = score;
            nametemp = sm->Name; 
            sm->Name = TextInput;
            change = true;
            continue;
        }
    }


    UEngineDirectory NewDir;
    NewDir.MoveToSearchChild("ContentsResources");
    std::fstream fs;
    std::string str_buf;
    UEngineFile NewFile = NewDir.NewFile("ScoreSheet.csv");
    std::string test = NewFile.GetFullPath(); 

    {
        fs.open(NewFile.GetFullPath(), std::ios::out);
        fs << "Num,Name,Score\n";
        for (ScoreRecord* sm : check_list)
        {
            int Num = sm->Num;
            std::string Name = sm->Name;
            int Score = sm->Score;
            fs << Num << "," << Name << "," << Score << std::endl;
        }
        fs.close();
    }

    {
        //UEngineDirectory NewDir;
        //NewDir.MoveToSearchChild("ContentsResources");
        //std::fstream fs;
        //std::string str_buf;

        //UEngineFile NewFile = NewDir.NewFile("ScoreSheet.csv");
        //std::string test = NewFile.GetFullPath();

        //// 읽기 모드로 파일 열기
        //fs.open(NewFile.GetFullPath(), std::ios::in);

        //// 첫 줄은 헤더이므로 먼저 읽고 버립니다.
        //std::getline(fs, str_buf);

        //// 파일 끝까지 읽기
        //while (std::getline(fs, str_buf))
        //{
        //    std::stringstream ss(str_buf); // 읽은 줄을 스트링스트림으로 변환
        //    std::string item;
        //    int num, score;
        //    std::string name;
        //    std::string text;

        //    // 쉼표를 구분자로 사용하여 파싱
        //    std::getline(ss, item, ',');
        //    num = std::stoi(item); // 문자열을 정수로 변환

        //    std::getline(ss, name, ',');

        //    std::getline(ss, item, ',');
        //    score = std::stoi(item);

        //    //// 읽은 데이터로 ScoreManager 객체 생성
        //    //ScoreRecord* newScoreManager = new ScoreRecord(num, name, score);
        //    //// 리스트에 추가
        //    //check_list.push_back(newScoreManager);
        //}
        //// 파일 닫기
        //fs.close();
    }

    count = 0;
    for (ScoreRecord* sm : check_list)
    {
        int num = sm->Num;
        int score = sm->Score;

        std::string name = sm->Name + " : " + std::to_string(score);
        font[count]->SetFont(name, 40.f);
        ++count;
    }

    ScoreReset = false;
}


void UScreenScore_Level::InputCheck()
{
    if (Text_Count >= Text_MaxCount)
    {
        if (UEngineInput::IsDown(VK_BACK))
        {
            if (!TextInput.empty())// teststring이 비어있지 않은 경우
            { 
                TextInput.erase(TextInput.size() - 1); // 마지막 문자를 제거
                Input_Text = true;
                Text_Count -= 1;
            }
        }
        if (UEngineInput::IsDown(VK_RETURN))
        {
           ScoreReset = true;
           InputName = false;
        }
    }
    else
    {
        if (UEngineInput::IsDown(VK_BACK))
        {
            if (!TextInput.empty())
            { 
                TextInput.erase(TextInput.size() - 1); 
                Input_Text = true;
                Text_Count -= 1;
            }
        }
        if (UEngineInput::IsDown(VK_RETURN))
        {
            ScoreReset = true;
            InputName = false;
        }

        if (UEngineInput::IsDown('Q'))
        {
            TextInput += 'Q';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('W'))
        {
            TextInput += 'W';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('E'))
        {
            TextInput += 'E';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('R'))
        {
            TextInput += 'R';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('T'))
        {
            TextInput += 'T';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('Y'))
        {
            TextInput += 'Y';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('U'))
        {
            TextInput += 'U';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('I'))
        {
            TextInput += 'I';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('O'))
        {
            TextInput += 'O';
            Input_Text = true;
            Text_Count += 1;
        }

        if (UEngineInput::IsDown('P'))
        {
            TextInput += 'P';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('A'))
        {
            TextInput += 'A';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('S'))
        {
            TextInput += 'S';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('D'))
        {
            TextInput += 'D';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('F'))
        {
            TextInput += 'F';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('G'))
        {
            TextInput += 'G';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('H'))
        {
            TextInput += 'H';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('J'))
        {
            TextInput += 'J';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('K'))
        {
            TextInput += 'K';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('L'))
        {
            TextInput += 'L';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('Z'))
        {
            TextInput += 'Z';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('X'))
        {
            TextInput += 'X';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('C'))
        {
            TextInput += 'C';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('V'))
        {
            TextInput += 'V';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('B'))
        {
            TextInput += 'B';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('N'))
        {
            TextInput += 'N';
            Input_Text = true;
            Text_Count += 1;
        }
        if (UEngineInput::IsDown('M'))
        {
            TextInput += 'M';
            Input_Text = true;
            Text_Count += 1;
        }
    }

   
}
