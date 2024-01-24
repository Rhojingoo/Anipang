#pragma once
#include <Windows.h>
#include <string>

class EngineWindow
{
public : 
	EngineWindow();
	~EngineWindow();

	EngineWindow(const EngineWindow& _Other)					= delete;
	EngineWindow(EngineWindow& _Other) noexcept					= delete;
	EngineWindow& operator =(const 	EngineWindow& _Other)		= delete;
	EngineWindow& operator =(EngineWindow& _Other)noexcept		= delete;

	void Open(std::string_view _Title = "Title");

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	HDC GetWindowDC()
	{
		return hDC;
	}

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND hWnd = nullptr;
	HDC hDC = nullptr;
};

