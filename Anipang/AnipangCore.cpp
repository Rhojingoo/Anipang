#include "AnipangCore.h"
#include "TitleLevel.h"

AnipangCore::AnipangCore()
{
}

AnipangCore::~AnipangCore()
{
}

void AnipangCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("Title");
	//CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("Title");
	int a = 0;
}

void AnipangCore::Tick(float _DeltaTime)
{
	//�÷��̾ ������ �� �ֵ��ΰ� �����ϸ�Ǵ� ��
}

void AnipangCore::End()
{
}
