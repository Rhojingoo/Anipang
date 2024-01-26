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
		MsgBoxAssert("������ ������ ������ �������� �ʾҽ��ϴ� ġ������ �����Դϴ�");
	}

	EngineInput::KeyCheckTick(DeltaTime);

	// ������ ���� ƽ�� ������
	CurLevel->Tick(DeltaTime);

	// ���Ϳ� �ΰ����� ������Ʈ���� ƽ�� ������
	CurLevel->LevelTick(DeltaTime);

	// ���������� ������ ���ؼ� ȭ�鿡 �׸��� �׸��� => �׸���
	CurLevel->LevelRender(DeltaTime);

	// �����Ѵ�.(�׾���� ������Ʈ���� �� �ı��Ѵ�)
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
		MsgBoxAssert(std::string(_Name) + "��� �������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�");
	}

	// ���� �������� ��������?
	CurLevel = AllLevel[UpperName];
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}
