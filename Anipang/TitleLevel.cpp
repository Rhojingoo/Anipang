#include "TitleLevel.h"
#include "Animal.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	UEngineDirectory NewPath;

	NewPath.MoveParent();

	NewPath.Move("ContentsResources");
	NewPath.Move("Texture");

	// resource Image의 전체적인 순회
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	SpawnActor<AAnimal>();
}
