#include "EnginePath.h"
#include "EngineDebug.h"
#include <Windows.h>

UEnginePath::UEnginePath() 
	: Path(std::filesystem::current_path())	//������Ʈ�� ���۰�θ� �������Ƿ� App�� ��θ� �޾ƿ�
{
}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

UEnginePath::~UEnginePath() 
{
}

void UEnginePath::Move(std::string_view _Path)
{
	std::filesystem::path NextPath = Path;
	NextPath.append(_Path);

	bool Check = std::filesystem::exists(NextPath); 
	//�־��� ���(NextPath)�� ������ ���� �ý��ۿ� ���� ���θ� �˻�

	if (false == Check)
	{
		MsgBoxAssert(NextPath.string() + "��� ��δ� �������� �ʽ��ϴ�");
	}

	Path = NextPath;
}

std::string UEnginePath::AppendPath(std::string_view _Path)
{
	return Path.string() + "\\" + std::string(_Path);
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

std::string UEnginePath::GetFileName() const
{
	std::filesystem::path Text = Path.filename();
	return Text.string();
}

std::string UEnginePath::GetExtension() const
{
	std::filesystem::path Text = Path.extension();
	return Text.string();
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

bool UEnginePath::IsFile()
{
	return !std::filesystem::is_directory(Path);
}
bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}