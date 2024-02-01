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
		MsgBoxAssert("이미지가 존재하지 않는 랜더러 입니다");
	}

	FTransform RendererTrans = GetTransform();
	FTransform ActorTrans = GetOwner()->GetTransform();
	RendererTrans.AddPosition(ActorTrans.GetPosition());

	// 이려면 윈도우 이미지에 그리면 화면의 갱신이 산발적으로 발생
	//GEngine->MainWindow.GetWindowImage()->BitCopy(Image, RendererTrans);
	
	// bitblt
	//GEngine->MainWindow.GetBackBufferImage()->BitCopy(Image, RendererTrans);

	GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, ImageCuttingTransform);
}

void UImageRenderer::SetImage(std::string_view _Name)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}
}


void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}