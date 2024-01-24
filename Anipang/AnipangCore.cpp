#include "AnipangCore.h"
#include "TitleLevel.h"
#include "ScoreLevel.h"
#include "PlayLevel.h"

AnipangCore::AnipangCore()
{
}

AnipangCore::~AnipangCore()
{
}

void AnipangCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UScoreLevel>("Score");
	CreateLevel<UPlayLevel>("Play");

	ChangeLevel("Title");
}

void AnipangCore::Tick(float _DeltaTime)
{
	//�÷��̾ ������ �� �ֵ��ΰ� �����ϸ�Ǵ� ��
}

void AnipangCore::End()
{
}
