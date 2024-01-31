#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>

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
	void SetImage(std::string_view _Name, bool _IsImageScale = false);
	void SetImageToScale(std::string_view _Name);

	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

protected:
	void BeginPlay() override;

private:
	UWindowImage* Image = nullptr;
	FTransform ImageCuttingTransform;

};

