#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>
#include <map>


class UAnimationInfo
{
public:
	// 애니메이션을 구성할때 이미지는 1장
	UWindowImage* Image = nullptr;
	int Start = -1;
	int End = -1;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = false;
	std::vector<float> Times;
	std::vector<int> Indexs;

	int Update(float _DeltaTime);
};

class UWindowImage;
class UImageRenderer : public USceneComponent
{
public:
	UImageRenderer();
	~UImageRenderer();

	UImageRenderer(const UImageRenderer& _Other)					 = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept				 = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other)			 = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept		 = delete;

	void SetOrder(int _Order) override;
	void Render(float _DeltaTime);

	void SetImage(std::string_view _Name, int _InfoIndex = 0);

	void SetImageIndex(int _InfoIndex)
	{
		InfoIndex = _InfoIndex;
	}	

	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTransform(_Value);
	}

	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

	void CreateAnimation(
		std::string_view _AnimationName, 
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName);

	void AnimationReset();

	void SetTransColor(Color8Bit _Color)
	{
		TransColor = _Color;
	}

	void SetAlpha(float _Alpha)
	{
		if (0.0f >= _Alpha)
		{
			_Alpha = 0.0f;
		}

		if (1.0f <= _Alpha)
		{
			_Alpha = 1.0f;
		}

		TransColor.A = static_cast<char>(_Alpha * 255.0f);
	}

protected:
	void BeginPlay() override;

private:
	int InfoIndex = 0;
	UWindowImage* Image = nullptr;
	FTransform ImageCuttingTransform;
	Color8Bit TransColor;

	std::map<std::string, UAnimationInfo> AnimationInfos;
	UAnimationInfo* CurAnimation = nullptr;
};

