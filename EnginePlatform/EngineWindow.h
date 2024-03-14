#pragma once
#include <Windows.h>
#include <string>
#include <EngineBase\EngineMath.h>

class UWindowImage;
class UEngineWindow
{
public : 
	UEngineWindow();
	~UEngineWindow();

	UEngineWindow(const UEngineWindow& _Other)						= delete;
	UEngineWindow(UEngineWindow& _Other) noexcept					= delete;
	UEngineWindow& operator =(const 	UEngineWindow& _Other)		= delete;
	UEngineWindow& operator =(UEngineWindow& _Other)noexcept		= delete;

	void Open(std::string_view _Title = "Title", std::string_view _IconPath = "");

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	UWindowImage* GetWindowImage()
	{
		return WindowImage;
	}

	UWindowImage* GetBackBufferImage()
	{
		return BackBufferImage;
	}

	void SetWindowPosition(const FVector& _Pos);
	void SetWindowScale(const FVector& _Scale);

	void ScreenClear();
	void ScreenUpdate();

	FVector GetWindowScale()
	{
		return Scale;
	}

	void SetClearColor(Color8Bit _Color)
	{
		_Color.A = 0;
		ClearColor = _Color;
	}

	void SetWindowTitle(std::string_view _Text)
	{
		SetWindowTextA(hWnd, _Text.data());
	}

	void CursorOff();


	FVector GetMousePosition();

	void Off()
	{
		WindowLive = false;
	}

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	Color8Bit ClearColor = Color8Bit::NAWhite;

	HWND hWnd = nullptr;
	UWindowImage* WindowImage = nullptr;

	UWindowImage* BackBufferImage = nullptr;
	FVector Scale;
	FVector Position;
};

