#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineWindow.h>
#include <Anipang\AnipangCore.h>


// ���� �������� �����鿡�� ������ �⵿�� �����ϱ� ���ؼ� ����� ���.

// ����ڰ� �ϰ� �������� ��� ��� �����ϰ� ����ų�?
// ���� ������ ũ�⸦ �����ϰ� �;�.

//ENGINESTART(AnipangCore)

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LeakCheck;
	AnipangCore NewUserCore = AnipangCore();
	EngineCore::EngineStart(hInstance, &NewUserCore);
}