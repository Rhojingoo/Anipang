#pragma once
#include <string>
#include <filesystem> 


class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	//UEnginePath(const UEnginePath& _Other)						= delete;
	//UEnginePath(UEnginePath&& _Other) noexcept					= delete;
	//UEnginePath& operator=(const UEnginePath& _Other)				= delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept			= delete;

	// 이게 파일경로인지.
	bool IsFile();
	bool IsDirectory();

	bool IsExists();

	std::string GetFileName();
	std::string GetExtension();

	void MoveParent();
	void Move(std::string_view _Path);

	std::string GetFullPath()
	{
		return Path.string();
	}
protected:
	std::filesystem::path Path;
private:
};

