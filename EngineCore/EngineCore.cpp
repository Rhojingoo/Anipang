#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"

EngineCore* GEngine = nullptr;


EngineCore::EngineCore()
	:MainWindow()
{
}


EngineCore::~EngineCore()
{
}


void EngineCore::EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore)
{
	EngineCore* Ptr = _UserCore;
	GEngine = Ptr;
	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();
	EngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void EngineCore::EngineTick()
{
	GEngine->CoreTick();
}

void EngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck();
	double dDeltaTime = MainTimer.GetDeltaTime();



	if (1 <= Frame)
	{
		//               5.0f
		CurFrameTime += DeltaTime;

		//  0.00001        0.016666675
		if (CurFrameTime <= FrameTime)
		{
			return;
		}

		//  0.0167         0.016666675
		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	if (nullptr == CurLevel)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	EngineInput::KeyCheckTick(DeltaTime);

	// 레벨이 먼저 틱을 돌리고
	CurLevel->Tick(DeltaTime);

	// 액터와 부가적인 오브젝트들의 틱도 돌리고
	CurLevel->LevelTick(DeltaTime);

	// 랜더러들의 랜더를 통해서 화면에 그림도 그린다 => 그리고
	CurLevel->LevelRender(DeltaTime);

	// 정리한다.(죽어야할 오브젝트들은 다 파괴한다)
	CurLevel->LevelRelease(DeltaTime);


	//HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	//Rectangle(WindowDC, -200, -200, 3000, 3000);
}


void EngineCore::EngineEnd()
{
	for (std::pair<const std::string, ULevel*>& _Pair : GEngine->AllLevel)
	{
		if (nullptr == _Pair.second)
		{
			continue;
		}

		delete _Pair.second;
		_Pair.second = nullptr;
	}

	GEngine->AllLevel.clear();
}


void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	EngineWindow::Init(_HINSTANCE);
	MainWindow.Open("ANIPANG");

	this->AllLevel;

	EngineInit = true;
}

void EngineCore::BeginPlay()
{
}

void EngineCore::Tick(float _DeltaTime)
{
}

void EngineCore::End()
{
}

void EngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 체인지 하려고 했습니다");
	}

	// 눈에 보여야할 레벨이죠?
	CurLevel = AllLevel[UpperName];
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}
