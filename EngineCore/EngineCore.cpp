#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"

UEngineCore* GEngine = nullptr;


UEngineCore::UEngineCore()
	:MainWindow(), MainTimer()
{
}


UEngineCore::~UEngineCore()
{
}


void UEngineCore::EngineStart(HINSTANCE _hInstance, UEngineCore* _UserCore)
{
	UEngineCore* Ptr = _UserCore;
	GEngine = Ptr;
	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();
	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void UEngineCore::EngineTick()
{
	GEngine->CoreTick();
}

void UEngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck();
	double dDeltaTime = MainTimer.GetDeltaTime();



	if (1 <= Frame)
	{
		CurFrameTime += DeltaTime;
		if (CurFrameTime <= FrameTime)
		{
			return;
		}
		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	if (nullptr == CurLevel)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	UEngineInput::KeyCheckTick(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->LevelTick(DeltaTime);
	MainWindow.ScreenClear();
	CurLevel->LevelRender(DeltaTime);
	MainWindow.ScreenUpdate();
	CurLevel->LevelRelease(DeltaTime);
}


void UEngineCore::EngineEnd()
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


void UEngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	UEngineWindow::Init(_HINSTANCE);
	MainWindow.Open("ANIPANG");

	this->AllLevel;

	EngineInit = true;
}

void UEngineCore::BeginPlay()
{
}

void UEngineCore::Tick(float _DeltaTime)
{
}

void UEngineCore::End()
{
}

void UEngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 체인지 하려고 했습니다");
	}
	CurLevel = AllLevel[UpperName];
}

void UEngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}
