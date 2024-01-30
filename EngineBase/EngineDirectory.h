#pragma once
#include "EnginePath.h"
#include <list>

class UEngineFile;
class UEngineDirectory : public UEnginePath
{
public:
	UEngineDirectory();
	~UEngineDirectory();

	//UEngineDirectory(const UEngineDirectory& _Other)							= delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept						= delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other)				= delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept			= delete;



	/// <summary>
	/// ������ ���δ� ã���ִ� �Լ�
	/// </summary>
	/// <param name="_Ext">Ȯ���ڵ� �ҹ��� �빮�� ������ ������.</param>
	/// <param name="_Rescursive">���� �������� �� �˻��Ұ���.</param>
	/// <returns></returns>
	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

protected:

private:
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};

