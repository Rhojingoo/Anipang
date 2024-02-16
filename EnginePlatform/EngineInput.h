#pragma once
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineMath.h>


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

	
		void KeyCheck(float _DeltaTime);

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

	static float GetPressTime(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].PressTime;
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

	static bool IsAnykeyDown()
	{
		return AnykeyDown;
	}
	static bool IsAnykeyPress()
	{
		return AnykeyPress;
	}
	static bool IsAnykeyUp()
	{
		return AnykeyUp;
	}
	static bool IsAnykeyFree()
	{
		return AnykeyFree;
	}

	static void KeyCheckTick(float _DeltaTime);
protected:
	static std::map<int, UEngineKey> AllKeys;

	static bool AnykeyDown;
	static bool AnykeyPress;
	static bool AnykeyUp;
	static bool AnykeyFree;

	int Value;

private:
	static void InputInit();
};

