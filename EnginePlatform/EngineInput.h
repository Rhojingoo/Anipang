#pragma once
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>


class EngineInput
{
	friend class InputInitCreator;

private:
	class EngineKey
	{
		friend EngineInput;

	public:
		bool Down = false; 
		bool Press = false; 
		bool Up = false;
		bool Free = true; 

		float PressTime = 0.0f;

		int Key = -1; 

		void KeyCheck();

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
		{

		}
	};

public:
	EngineInput();
	~EngineInput();

	EngineInput(const EngineInput& _Other)						= delete;
	EngineInput(EngineInput&& _Other) noexcept					= delete;
	EngineInput& operator=(const EngineInput& _Other)			= delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept		= delete;

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
	static std::map<int, EngineKey> AllKeys;

	int Value;

private:
	static void InputInit();
};

