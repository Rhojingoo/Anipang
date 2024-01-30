#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UEngineWindow;
class UWindowImage : public UPathObject
{
	friend UEngineWindow;
public:
	UWindowImage();
	~UWindowImage();

	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	bool Load(UWindowImage* _Image);

	FVector GetScale();

	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);

protected:

private:

	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP BitMapInfo = BITMAP();
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
	bool Create(HDC _MainDC);
};

