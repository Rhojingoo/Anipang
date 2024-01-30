#include "EngineDirectory.h"
#include "EngineFile.h"
#include "EngineString.h"

UEngineDirectory::UEngineDirectory() 
{
}

UEngineDirectory::~UEngineDirectory() 
{
}

void UEngineDirectory::AllFileRecursive(
	const std::string_view _Path, 
	std::list<UEngineFile>& _Result, 
	std::vector<std::string> _Ext, 
	bool _Recursive )
{
	//�ش��θ� ��ȸ�Ҽ� � ������ �ִ��� �˼� �ְ� ��ȸ�ϴ� directory_iterator
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);


	//filesystem::directory_entry�� directory_iterator�� ���� ���� ���丮�� �׸���� ��Ÿ���� �� ���
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = UEngineString::ToUpper(Ext.string());

		// filesystem::directory_entry& Entry�� is_directory()�� �������� Ȯ�� �� ������� �� Ž��		
		if (true == Entry.is_directory())
		{
			if (true == _Recursive)
			{
				AllFileRecursive(Path.string(), _Result, _Ext, _Recursive);
			}
			continue;
		} 

		if (0 == _Ext.size())
		{
			_Result.push_back(UEngineFile(Path.string()));
			continue;
		}

		bool Check = false;

		for (size_t i = 0; i < _Ext.size(); i++)
		{
			if (_Ext[i] == UpperExt)
			{
				Check = true;
			}
		}

		if (true == Check)
		{
			_Result.push_back(UEngineFile(Path.string()));
		}

	}
}

std::list<UEngineFile> UEngineDirectory::AllFile(
	std::vector<std::string> _Ext , 
	bool _Rescursive)
{
	std::list<UEngineFile> Result;

	for (size_t i = 0; i < _Ext.size(); i++)
	{
		_Ext[i] = UEngineString::ToUpper(_Ext[i]);
	}

	AllFileRecursive(Path.string(), Result, _Ext, _Rescursive);
	return Result;
}