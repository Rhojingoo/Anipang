#include "EngineInput.h"

std::map<int, UEngineInput::UEngineKey> UEngineInput::AllKeys;

bool UEngineInput::AnykeyDown = false;
bool UEngineInput::AnykeyPress = false;
bool UEngineInput::AnykeyUp = false;
bool UEngineInput::AnykeyFree = true;


UEngineInput::UEngineInput()
{
}

UEngineInput::~UEngineInput()
{
}

void UEngineInput::UEngineKey::KeyCheck(float _DeltaTime)
{
	if (0 != GetAsyncKeyState(Key))
	{
		if (true == Free)
		{
			UpTime;
			PressTime = 0.0f;
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else if (true == Down)
		{
			UpTime = 0.0f;
			PressTime += _DeltaTime;
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		UpTime += _DeltaTime;
		if (true == Press)
		{
			PressTime = 0.0f;
			Down = false;
			Press = false;
			Up = true;
			Free = false;
		}
		else if (true == Up)
		{
			PressTime = 0.0f;
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}

	}
}


void UEngineInput::InputInit()
{
	AllKeys[VK_LBUTTON] = UEngineKey(VK_LBUTTON);
	AllKeys[VK_RBUTTON] = UEngineKey(VK_RBUTTON);
	AllKeys[VK_CANCEL] = UEngineKey(VK_CANCEL);
	AllKeys[VK_MBUTTON] = UEngineKey(VK_MBUTTON);
	AllKeys[VK_BACK] = UEngineKey(VK_BACK);
	AllKeys[VK_TAB] = UEngineKey(VK_TAB);
	AllKeys[VK_CLEAR] = UEngineKey(VK_CLEAR);
	AllKeys[VK_RETURN] = UEngineKey(VK_RETURN);
	AllKeys[VK_SHIFT] = UEngineKey(VK_SHIFT);
	AllKeys[VK_LSHIFT] = UEngineKey(VK_LSHIFT);
	AllKeys[VK_CONTROL] = UEngineKey(VK_CONTROL);
	AllKeys[VK_MENU] = UEngineKey(VK_MENU);
	AllKeys[VK_PAUSE] = UEngineKey(VK_PAUSE);
	AllKeys[VK_CAPITAL] = UEngineKey(VK_CAPITAL);
	AllKeys[VK_KANA] = UEngineKey(VK_KANA);
	AllKeys[VK_HANGEUL] = UEngineKey(VK_HANGEUL);
	AllKeys[VK_HANGUL] = UEngineKey(VK_HANGUL);
	AllKeys[VK_IME_ON] = UEngineKey(VK_IME_ON);
	AllKeys[VK_JUNJA] = UEngineKey(VK_JUNJA);
	AllKeys[VK_FINAL] = UEngineKey(VK_FINAL);
	AllKeys[VK_IME_OFF] = UEngineKey(VK_IME_OFF);
	AllKeys[VK_ESCAPE] = UEngineKey(VK_ESCAPE);
	AllKeys[VK_CONVERT] = UEngineKey(VK_CONVERT);
	AllKeys[VK_NONCONVERT] = UEngineKey(VK_NONCONVERT);
	AllKeys[VK_ACCEPT] = UEngineKey(VK_ACCEPT);
	AllKeys[VK_MODECHANGE] = UEngineKey(VK_MODECHANGE);
	AllKeys[VK_SPACE] = UEngineKey(VK_SPACE);
	AllKeys[VK_PRIOR] = UEngineKey(VK_PRIOR);
	AllKeys[VK_NEXT] = UEngineKey(VK_NEXT);
	AllKeys[VK_END] = UEngineKey(VK_END);
	AllKeys[VK_HOME] = UEngineKey(VK_HOME);
	AllKeys[VK_LEFT] = UEngineKey(VK_LEFT);
	AllKeys[VK_UP] = UEngineKey(VK_UP);
	AllKeys[VK_RIGHT] = UEngineKey(VK_RIGHT);
	AllKeys[VK_DOWN] = UEngineKey(VK_DOWN);
	AllKeys[VK_SELECT] = UEngineKey(VK_SELECT);
	AllKeys[VK_PRINT] = UEngineKey(VK_PRINT);
	AllKeys[VK_EXECUTE] = UEngineKey(VK_EXECUTE);
	AllKeys[VK_SNAPSHOT] = UEngineKey(VK_SNAPSHOT);
	AllKeys[VK_INSERT] = UEngineKey(VK_INSERT);
	AllKeys[VK_DELETE] = UEngineKey(VK_DELETE);
	AllKeys[VK_HELP] = UEngineKey(VK_HELP);
	AllKeys[VK_LWIN] = UEngineKey(VK_LWIN);
	AllKeys[VK_RWIN] = UEngineKey(VK_RWIN);
	AllKeys[VK_APPS] = UEngineKey(VK_APPS);
	AllKeys[VK_SLEEP] = UEngineKey(VK_SLEEP);
	AllKeys[VK_NUMPAD0] = UEngineKey(VK_NUMPAD0);
	AllKeys[VK_NUMPAD1] = UEngineKey(VK_NUMPAD1);
	AllKeys[VK_NUMPAD2] = UEngineKey(VK_NUMPAD2);
	AllKeys[VK_NUMPAD3] = UEngineKey(VK_NUMPAD3);
	AllKeys[VK_NUMPAD4] = UEngineKey(VK_NUMPAD4);
	AllKeys[VK_NUMPAD5] = UEngineKey(VK_NUMPAD5);
	AllKeys[VK_NUMPAD6] = UEngineKey(VK_NUMPAD6);
	AllKeys[VK_NUMPAD7] = UEngineKey(VK_NUMPAD7);
	AllKeys[VK_NUMPAD8] = UEngineKey(VK_NUMPAD8);
	AllKeys[VK_NUMPAD9] = UEngineKey(VK_NUMPAD9);
	AllKeys[VK_MULTIPLY] = UEngineKey(VK_MULTIPLY);
	AllKeys[VK_ADD] = UEngineKey(VK_ADD);
	AllKeys[VK_SEPARATOR] = UEngineKey(VK_SEPARATOR);
	AllKeys[VK_SUBTRACT] = UEngineKey(VK_SUBTRACT);
	AllKeys[VK_DECIMAL] = UEngineKey(VK_DECIMAL);
	AllKeys[VK_DIVIDE] = UEngineKey(VK_DIVIDE);
	AllKeys[VK_F1] = UEngineKey(VK_F1);
	AllKeys[VK_F2] = UEngineKey(VK_F2);
	AllKeys[VK_F3] = UEngineKey(VK_F3);
	AllKeys[VK_F4] = UEngineKey(VK_F4);
	AllKeys[VK_F5] = UEngineKey(VK_F5);
	AllKeys[VK_F6] = UEngineKey(VK_F6);
	AllKeys[VK_F7] = UEngineKey(VK_F7);
	AllKeys[VK_F8] = UEngineKey(VK_F8);
	AllKeys[VK_F9] = UEngineKey(VK_F9);
	AllKeys[VK_F10] = UEngineKey(VK_F10);
	AllKeys[VK_F11] = UEngineKey(VK_F11);
	AllKeys[VK_F12] = UEngineKey(VK_F12);
	AllKeys[VK_F13] = UEngineKey(VK_F13);
	AllKeys[VK_F14] = UEngineKey(VK_F14);
	AllKeys[VK_F15] = UEngineKey(VK_F15);
	AllKeys[VK_F16] = UEngineKey(VK_F16);
	AllKeys[VK_F17] = UEngineKey(VK_F17);
	AllKeys[VK_F18] = UEngineKey(VK_F18);
	AllKeys[VK_F19] = UEngineKey(VK_F19);
	AllKeys[VK_F20] = UEngineKey(VK_F20);
	AllKeys[VK_F21] = UEngineKey(VK_F21);
	AllKeys[VK_F22] = UEngineKey(VK_F22);
	AllKeys[VK_F23] = UEngineKey(VK_F23);
	AllKeys[VK_F24] = UEngineKey(VK_F24);
	AllKeys['-'] = UEngineKey(VK_OEM_MINUS);
	AllKeys['+'] = UEngineKey(VK_OEM_PLUS);
	AllKeys[VK_OEM_4] = UEngineKey(VK_OEM_4);
	AllKeys[VK_OEM_6] = UEngineKey(VK_OEM_6);

	for (int i = 'A'; i <= 'Z'; i++)
	{
		AllKeys[i] = UEngineKey(i);
	}

	for (int i = '0'; i <= '9'; i++)
	{
		AllKeys[i] = UEngineKey(i);
	}

}

void UEngineInput::KeyCheckTick(float _DeltaTime)
{
	bool KeyCheck = false;

	for (std::pair<const int, UEngineKey>& Key : AllKeys)
	{
		UEngineKey& CurKey = Key.second;

		CurKey.KeyCheck(_DeltaTime);

		if (true == CurKey.Press)
		{
			KeyCheck = true;
		}
	}

	// 어떤키든 눌렸다는 이야기
	if (true == KeyCheck)
	{
		if (true == AnykeyFree)
		{
			// 이전까지 이 키는 눌리고 있지 않았다
			AnykeyDown = true;
			AnykeyPress = true;
			AnykeyUp = false;
			AnykeyFree = false;
		}
		else if (true == AnykeyDown)
		{
			// 이전까지 이 키는 눌리고 있었다.
			AnykeyDown = false;
			AnykeyPress = true;
			AnykeyUp = false;
			AnykeyFree = false;
		}
	}
	else
	{
		if (true == AnykeyPress)
		{
			// 이전까지 이 키는 눌리고 있었다.
			AnykeyDown = false;
			AnykeyPress = false;
			AnykeyUp = true;
			AnykeyFree = false;
		}
		else if (true == AnykeyUp)
		{
			// 이전까지 이 키는 안눌리고 있었고 앞으로도 안눌릴거다.
			AnykeyDown = false;
			AnykeyPress = false;
			AnykeyUp = false;
			AnykeyFree = true;
		}

	}

	POINT mousePos = {};
	GetCursorPos(&mousePos);

	FVector mousenomal = FVector::Zero;
}

class InputInitCreator
{
public:
	InputInitCreator()
	{
		UEngineInput::InputInit();
	}
};

InputInitCreator CreateValue = InputInitCreator();

