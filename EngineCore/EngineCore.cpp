#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"
#include <EnginePlatform\EngineSound.h>


UEngineCore* GEngine = nullptr;
bool UEngineCore::IsDebugValue = false;

UEngineCore::UEngineCore()
	:MainWindow(), MainTimer()
{
}


UEngineCore::~UEngineCore()
{
}


void UEngineCore::EngineStart(HINSTANCE _hInstance)
{
	GEngine = this;
	MainTimer.TimeCheckStart();
	CoreInit(_hInstance);
	BeginPlay();
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

	if (1.0f / 60.0f <= DeltaTime)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	UEngineSound::Update();
	UEngineInput::KeyCheckTick(DeltaTime);

	if (nullptr != NextLevel)
	{
		// 최초에는 현재 레벨이 존재하지 않을 것이다.
		// 바꿀 레벨이 있다는 이야기입니다.
		if (nullptr != CurLevel)
		{
			// 레베링 끝났음을 알립니다.
			CurLevel->LevelEnd(NextLevel);
		}

		NextLevel->LevelStart(CurLevel);
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}


	if (nullptr == CurLevel)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	GEngine->Tick(DeltaTime);
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

void UEngineCore::Exit()
{
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
	NextLevel = AllLevel[UpperName];
}

void UEngineCore::LevelInit(ULevel* _Level, std::string_view _Name)
{
	_Level->SetName(_Name);
	_Level->BeginPlay();
}
