#include "TitleLevel.h"
#include "Animal.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	SpawnActor<AAnimal>();

	// SpawnActor<Player>();

	// 할일은 
	// 플레이어
	// 배경
	// 몬스터
	// 등등등을 코드로 여기서 다 만들어야 한다.
}
