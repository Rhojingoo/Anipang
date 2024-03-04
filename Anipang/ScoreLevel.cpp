#include "ScoreLevel.h"
#include <EngineCore\EngineCore.h>
#include "FadeIN_OUT.h"
#include "Score_BackGround.h"
#include "ScoreBoard.h"
#include "RecordBoard.h"
#include "Cursor.h"
#include "ScoreManager.h"

#include "ReStart_UI.h"
#include "GameEnd_UI.h"
#include "MainScreen_UI.h"


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



UScoreLevel::UScoreLevel()
{
}

UScoreLevel::~UScoreLevel()
{
}

void UScoreLevel::BeginPlay()
{
	ULevel::BeginPlay();
	SpawnActor<AScore_BackGround>();
	SpawnActor<AScoreBoard>();
	Cursor = SpawnActor<ACursor>();
	bool Scoreset = true;

	ScoreMN = SpawnActor<ScoreManager>();
	ScoreMN->ScoreLevelON();


	AReStart_UI* GameStartUI = SpawnActor<AReStart_UI>();
	GameStartUI->SetActorLocation({ 240,540 });
	GameStartUI->SetCursor(Cursor);

	AMainScreen_UI* ScoreUI = SpawnActor<AMainScreen_UI>();
	ScoreUI->SetActorLocation({ 240,588 });
	ScoreUI->SetCursor(Cursor);

	AGameEnd_UI* GameendUI = SpawnActor<AGameEnd_UI>();
	GameendUI->SetActorLocation({ 240,636 });
	GameendUI->SetCursor(Cursor);
}

void UScoreLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

    if (InputName == true)
    {
        InputCheck();
        ScoreMN->SetActorLocation({ 240,250 });
        if (Input_Text == true)
        {
           

            if (!TextInput.empty())
            {
                Input_Font->SetFont(TextInput, 40.f);
                Input_Font->SetActorLocation({ 200,340 });
            }
            else
            {
                Input_Font->SetFont("입력하세요", 40.f);
                Input_Font->FontCenterOff();
                Input_Font->SetActorLocation({ 110,340 });
            }
            Input_Text = false;
        }
    }
    if (ScoreReset == true)
    {
        if (Input_Font != nullptr)
        {
            Input_Font->Destroy();
            Input_Font = nullptr;
            RecordBoard->Destroy();
            RecordBoard = nullptr;
        }
        ResetScore(ScoreManager::GetScore());
        ScoreReset = false;
        ScoreMN->ScoreLevelON();
        //ScoreMN->SetActorLocation({ 240,200 });
    }



	//if (UEngineInput::IsDown('N'))
	//{
	//	GEngine->ChangeLevel("Ending");
	//}
}

void UScoreLevel::LevelStart(ULevel* _Level)
{
	SpawnActor<AFadeIN_OUT>();
    ScoreMN->ScoreLevelON();
    SettingScore();
    ScoreCheck(ScoreManager::GetScore());
}

void UScoreLevel::LevelEnd(ULevel* _Level)
{
    if (check_list.empty() == false)
    {
        for (ScoreRecord* check : check_list)
        {
            delete check;
        }
        check_list.clear();
    }
    ScoreReset = false;
}

void UScoreLevel::SettingScore()
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

        ++count;
    }
}

void UScoreLevel::ScoreCheck(int _score)
{
    int scorecheck = _score;

    for (ScoreRecord* sm : check_list)
    {
        if (sm->Score < scorecheck)
        {
            InputName = true;
            RecordBoard = SpawnActor<ARecordBoard>();

            Input_Font = SpawnActor<ANumberFont>();
            Input_Font->FontCenterOff();
            Input_Font->SetActorLocation({ 110,340 });
            Input_Font->SetFont("입력하세요", 40.f);   
            InputName = true;            
            return;
        }
    }
}

void UScoreLevel::ResetScore(int _score)
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
}

void UScoreLevel::InputCheck()
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
