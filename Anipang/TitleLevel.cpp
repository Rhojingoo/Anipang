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



	// �����ΰ� ���;� �Ѵٰ� �����մϴ�.
	UEngineDirectory NewPath;

	NewPath.MoveParent();
	// NewPath.Move("ContentsResources");

	NewPath.Move("ContentsResources");
	NewPath.Move("Texture");


	// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	// CherryBomb_0.png
	UEngineResourcesManager::GetInst().LoadImg("C:\\GM\\Win\\ContentsResources\\AAAA.png");


	SpawnActor<AAnimal>();

	// ������ 
	// �÷��̾�
	// ���
	// ����
	// ������ �ڵ�� ���⼭ �� ������ �Ѵ�.
}
