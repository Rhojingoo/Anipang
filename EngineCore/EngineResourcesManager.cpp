#include "EngineResourcesManager.h"
#include <EnginePlatform\WindowImage.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>
#include "EngineCore.h"
#include "EngineBase\EngineDebug.h"



UEngineResourcesManager::UEngineResourcesManager() 
{
}

UEngineResourcesManager::~UEngineResourcesManager() 
{
	for (std::pair<const std::string, UWindowImage*>& Pair : Images)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	Images.clear();
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadImg(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Images.contains(UpperName))
	{
		MsgBoxAssert(std::string("경로 : ") + std::string(_Path) + "파일명 : " + std::string(_Name) + "이미 로드한 파일을 또 로드하려고 했습니다");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->Load(GEngine->MainWindow.GetWindowImage());

	Images[UpperName] = NewImage;

	return nullptr;
}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == Images.contains(UpperName))
	{
		MsgBoxAssert("파일명 : " + std::string(_Name) + "은 존재하지 않는 이미지입니다");
		return nullptr;
	}

	return Images[UpperName];
}