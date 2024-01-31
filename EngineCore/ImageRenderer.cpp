#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"
#include <EngineCore\EngineResourcesManager.h>

UImageRenderer::UImageRenderer() 
{
}

UImageRenderer::~UImageRenderer() 
{
}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;
	Renderers[GetOrder()].remove(this);
	UTickObject::SetOrder(_Order);


	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (nullptr == Image)
	{
		MsgBoxAssert("�̹����� �������� �ʴ� ������ �Դϴ�");
	}

	FTransform ThisTrans = GetTransform();
	FTransform OwnerTrans = GetOwner()->GetTransform();
	ThisTrans.AddPosition(OwnerTrans.GetPosition());

	// �̷��� ������ �̹����� �׸��� ȭ���� ������ ��������� �߻�
	//GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans);
	
	// bitblt
	//GEngine->MainWindow.GetBackBufferImage()->BitCopy(Image, ThisTrans);

	GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform);
}

void UImageRenderer::SetImage(std::string_view _Name, bool _IsImageScale)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		MsgBoxAssert(std::string(_Name) + "�̹����� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == _IsImageScale)
	{
		FVector Scale = Image->GetScale();
		SetScale(Scale);

		ImageCuttingTransform.SetPosition({ 0,0 });
		ImageCuttingTransform.SetScale(Scale);
	}
}

void UImageRenderer::SetImageToScale(std::string_view _Name)
{
	SetImage(_Name, true);
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}