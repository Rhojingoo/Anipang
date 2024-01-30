#include "EngineString.h"
#include <Windows.h>
#include "EngineDebug.h"

UEngineString::UEngineString()
{
}

UEngineString::~UEngineString()
{
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{	
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	return Result;
}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}