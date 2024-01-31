#pragma once
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>


class UEngineInput
{
	friend class InputInitCreator;

private:
	class UEngineKey
	{
		friend UEngineInput;

	public:
		bool Down = false; 
		bool Press = false; 
		bool Up = false;
		bool Free = true; 

		float PressTime = 0.0f;

		int Key = -1; 

		void KeyCheck();

		UEngineKey()
		{

		}

		UEngineKey(int _Key)
			: Key(_Key)
		{

		}
	};

public:
	UEngineInput();
	~UEngineInput();

	UEngineInput(const UEngineInput& _Other)						= delete;
	UEngineInput(UEngineInput&& _Other) noexcept					= delete;
	UEngineInput& operator=(const UEngineInput& _Other)			= delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept		= delete;

	static bool IsDown(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Free;
	}

	static void KeyCheckTick(float _DeltaTime);
protected:
	static std::map<int, UEngineKey> AllKeys;

	int Value;

private:
	static void InputInit();
};

