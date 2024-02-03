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

	if (nullptr != CurAnimation)
	{
		Image = CurAnimation->Image;
		InfoIndex = CurAnimation->Update(_DeltaTime);
	}

	FTransform RendererTrans = GetTransform();
	FTransform ActorTrans = GetOwner()->GetTransform();
	RendererTrans.AddPosition(ActorTrans.GetPosition());

	EWIndowImageType ImageType = Image->GetImageType();
	//

	// 이려면 윈도우 이미지에 그리면 화면의 갱신이 산발적으로 발생
	//GEngine->MainWindow.GetWindowImage()->BitCopy(Image, RendererTrans);
	
	// bitblt
	//GEngine->MainWindow.GetBackBufferImage()->BitCopy(Image, RendererTrans);

	//Transparentsblt
	//GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, InfoIndex);
	//GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, InfoIndex, TransColor);

	switch (ImageType)
	{
	case EWIndowImageType::IMG_BMP:
		GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, InfoIndex, TransColor);
		// bmp일때는 일반적으로 Transcopy로 투명처리를 한다.
		break;
	case EWIndowImageType::IMG_PNG:
		GEngine->MainWindow.GetBackBufferImage()->AlphaCopy(Image, RendererTrans, InfoIndex, TransColor);
		break;
	default:
		MsgBoxAssert("투명처리가 불가능한 이미지 입니다.");
		break;
	}
}


void UImageRenderer::SetImage(std::string_view _Name, int _InfoIndex)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}
	InfoIndex = _InfoIndex;
}

void UImageRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _ImageName, int _Start, int _End, float _Inter, bool _Loop)
{
	UWindowImage* FindImage = UEngineResourcesManager::GetInst().FindImg(_ImageName);

	if (nullptr == FindImage)
	{
		MsgBoxAssert(std::string(_ImageName) + "이미지가 존재하지 않습니다.");
		return;
	}

	std::string UpperAniName = UEngineString::ToUpper(_AnimationName);

	if (true == AnimationInfos.contains(UpperAniName))
	{
		MsgBoxAssert(std::string(UpperAniName) + "라는 이름의 애니메이션이 이미 존재합니다.");
		return;
	}

	// AnimationInfos.operator[]("AAAA");
	// "AAA"가 없으면 만들어서 리턴
	// "AAA"가 있으면 찾아서 리턴

	// UAnimationInfo Info;
	// AnimationInfos.emplace();

	// 아래의 함수는 만약에 여러분들이 Key를 넣어주면
	// 없으면 MapNode를 내부에서 insert해버린다.
	// 있으면 알아서 Find해서 second만 리턴해준다.
	// AnimationInfos.operator[](Key)

	UAnimationInfo& Info = AnimationInfos[UpperAniName];
	Info.Image = FindImage;
	Info.CurFrame = 0;
	Info.Start = _Start;
	Info.End = _End;
	Info.CurTime = 0.0f;
	Info.Loop = _Loop;

	//          12         0
	int Size = Info.End - Info.Start;
	Info.Times.reserve(Size);
	Info.Indexs.reserve(Size);
	for (int i = _Start; i <= _End; i++)
	{
		Info.Times.push_back(_Inter);
	}

	for (int i = _Start; i <= _End; i++)
	{
		Info.Indexs.push_back(i);
	}
}

void UImageRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperAniName = UEngineString::ToUpper(_AnimationName);

	if (false == AnimationInfos.contains(UpperAniName))
	{
		MsgBoxAssert(std::string(UpperAniName) + "라는 이름의 애니메이션이 존재하지 않습니다.");
		return;
	}

	UAnimationInfo& Info = AnimationInfos[UpperAniName];
	CurAnimation = &Info;
	CurAnimation->CurFrame = 0;
	CurAnimation->CurTime = CurAnimation->Times[0];
}

void UImageRenderer::AnimationReset()
{
	CurAnimation = nullptr;
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}

int UAnimationInfo::Update(float _DeltaTime)
{
	CurTime -= _DeltaTime;

	if (0.0f >= CurTime)
	{
		CurTime = Times[CurFrame];
		++CurFrame;
	}

	//  6                 6
	if (Indexs.size() <= CurFrame)
	{
		if (true == Loop)
		{
			// //            0  1  2  3  4  5 
			//    Indexs => 20 21 22 23 24 25
			CurFrame = 0;
		}
		else
		{
			//                               
			//               0  1  2  3  4  5 
			//    Indexs => 20 21 22 23 24 25
			--CurFrame;
		}
	}

	int Index = Indexs[CurFrame];

	return Index;
}
