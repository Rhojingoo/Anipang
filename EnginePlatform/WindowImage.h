#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

enum class EImageLoadType
{
	IMG_Folder,
	IMG_Cutting,
};

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class ImageInfo
{
public:
	HBITMAP hBitMap;
	HDC ImageDC = nullptr;
	FTransform CuttingTrans;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
};

class UEngineWindow;
class UWindowImage : public UPathObject
{
	friend UEngineWindow;
public:
	UWindowImage();
	~UWindowImage();

	UWindowImage(const UWindowImage& _Other)							= delete;
	UWindowImage(UWindowImage&& _Other) noexcept						= delete;
	UWindowImage& operator=(const UWindowImage& _Other)					= delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept				= delete;

	bool Load(UWindowImage* _Image);

	bool LoadFolder(UWindowImage* _Image);

	FVector GetScale();

	void BitCopy(UWindowImage* _CopyImage, const FTransform& _Trans);
	//void TransCopy(UWindowImage* _CopyImage, const FTransform& _CopyTrans, const FTransform& _ImageTrans, Color8Bit _Color = Color8Bit::NAMagenta);

	void TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Magenta);

	void AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Magenta);

	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color );

	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _OutLineColor, Color8Bit _FillColor);

	bool Create(UWindowImage* _Image, const FVector& _Scale);

	void Cutting(int _X, int _Y);

	void DrawRectangle(const FTransform& _Trans);
	void DrawEllipse(const FTransform& _Trans);

	Color8Bit GetColor(int _X, int _Y, Color8Bit _DefaultColor);

	EWIndowImageType GetImageType()
	{
		return ImageType;
	}
protected:

private:
	EImageLoadType LoadType = EImageLoadType::IMG_Cutting;

	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP BitMapInfo = BITMAP();
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
	std::vector<ImageInfo> Infos;
	bool Create(HDC _MainDC);
};

