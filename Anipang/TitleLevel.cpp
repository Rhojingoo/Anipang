#include "TitleLevel.h"
#include "Animal.h"
//#include <EngineCore\EngineResourcesManager.h>
//#include <EngineBase\EngineDirectory.h>
//#include <EngineBase\EngineFile.h>

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	//UEngineDirectory NewPath;

	{
		//ATestTitleLogo* Logo = SpawnActor<ATestTitleLogo>();
	}

	SpawnActor<AAnimal>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
