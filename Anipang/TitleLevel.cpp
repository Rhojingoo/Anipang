#include "TitleLevel.h"
#include "Title_BackGround.h"
#include "Animal_Block.h"
#include "Title_BackGround.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();	
	SpawnActor<ATitle_BackGround>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
