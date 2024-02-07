#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>

// 윈도우에서 이미지를 사용하기 위해서 지원하는 라이브러리.
// 헤더랑 다르게 라이브러리는 #pragma comment 통해서 추가 해야 한다.
#pragma comment(lib, "Msimg32.lib")

#include <objidl.h>
#include <gdiplus.h>

// Png를 로드하는 기능을 윈도우 기본 라이브러리만으로 지원해주지 않기 때문에 GDIPlus를 사용해야 한다.
// GIDPlus는 윈도우가 초기 윈도우의 그래픽 시스템을 개선해서 추가한 라이브러리다.
#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage() 
{
}

UWindowImage::~UWindowImage() 
{
	switch (LoadType)
	{
	case EImageLoadType::IMG_Folder:
	{
		for (size_t i = 0; i < Infos.size(); i++)
		{
			DeleteObject(Infos[i].hBitMap);
			DeleteDC(Infos[i].ImageDC);
		}
		break;
	}
	case EImageLoadType::IMG_Cutting:
		DeleteObject(hBitMap);
		DeleteDC(ImageDC);
		break;
	default:
		break;
	}
}

bool UWindowImage::Load(UWindowImage* _Image)
{
	LoadType = EImageLoadType::IMG_Cutting;

	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	if (".BMP" == UpperExt)
	{
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
		ImageType = EWIndowImageType::IMG_BMP;
	}
	else if (".PNG" == UpperExt)
	{
		ULONG_PTR gdiplusToken = 0;
		Gdiplus::GdiplusStartupInput gdistartupinput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);

		std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());

		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 255, 0, 255), &hBitMap);

		if (Gdiplus::Status::Ok != stat)
		{
			MsgBoxAssert("Png 형식 리소스 로드에 실패했습니다.");
		}

		ImageType = EWIndowImageType::IMG_PNG;
	}

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	HBITMAP OldBitMap = (HBITMAP)SelectObject(ImageDC, hBitMap);
	DeleteObject(OldBitMap);
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	ImageInfo Info;
	Info.hBitMap = hBitMap;
	Info.ImageDC = ImageDC;
	Info.CuttingTrans.SetPosition({ 0,0 });
	Info.CuttingTrans.SetScale(GetScale());
	Info.ImageType = ImageType;
	Infos.push_back(Info);

	return true;
}

bool UWindowImage::LoadFolder(UWindowImage* _Image)
{
	LoadType = EImageLoadType::IMG_Folder;

	UEnginePath EnginePath = GetEnginePath();

	if (false == EnginePath.IsDirectory())
	{
		MsgBoxAssert("디렉토리가 아닌 경로로 폴더로드를 하려고 했습니다");
	}

	UEngineDirectory Dir = EnginePath;

	std::list<UEngineFile> NewList = Dir.AllFile({ ".png", ".bmp" }, false);

	Infos.reserve(NewList.size());

	for (UEngineFile& File : NewList)
	{
		UEnginePath Path = File;

		std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

		if (".BMP" == UpperExt)
		{
			HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
			ImageType = EWIndowImageType::IMG_BMP;
		}
		else if (".PNG" == UpperExt)
		{
			ULONG_PTR gdiplusToken = 0;
			Gdiplus::GdiplusStartupInput gdistartupinput;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);
			std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());
			Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
			Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());
			Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 255, 0, 255), &hBitMap);
			if (Gdiplus::Status::Ok != stat)
			{
				MsgBoxAssert("Png 형식 리소스 로드에 실패했습니다.");
			}

			ImageType = EWIndowImageType::IMG_PNG;
		}
		ImageDC = CreateCompatibleDC(_Image->ImageDC);

		if (nullptr == ImageDC)
		{
			MsgBoxAssert("이미지 생성에 실패했습니다");
			return false;
		}

		HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
		DeleteObject(OldBitMap);
		GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

		ImageInfo Info;
		Info.hBitMap = hBitMap;
		Info.ImageDC = ImageDC;
		Info.CuttingTrans.SetPosition({ 0,0 });
		Info.CuttingTrans.SetScale(GetScale());
		Infos.push_back(Info);
	}

		return true;
}

FVector UWindowImage::GetScale()
{
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}


bool UWindowImage::Create(UWindowImage* _Image, const FVector& _Scale)
{
	// 시작이 먼저 이미지를 만든다.


	// HBITMAP 비트맵 이미지의 메모리권한
	HANDLE ImageHandle = CreateCompatibleBitmap(_Image->ImageDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// hBitMap에서 얻어오겠다.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

void UWindowImage::Cutting(int _X, int _Y)
{
	Infos.clear();

	FVector CuttingScale = { GetScale().X / _X,  GetScale().Y / _Y };
	FVector CuttingPos = { 0, 0 };

	for (int i = 0; i < _Y; i++)
	{
		for (int i = 0; i < _X; i++)
		{
			ImageInfo Info;
			Info.ImageDC = ImageDC;
			Info.CuttingTrans.SetPosition(CuttingPos);
			Info.CuttingTrans.SetScale(CuttingScale);
			Infos.push_back(Info);

			CuttingPos.X += CuttingScale.X;
		}

		CuttingPos.X = 0.0f;
		CuttingPos.Y += CuttingScale.Y;
	}
}

Color8Bit UWindowImage::GetColor(int _X, int _Y)
{
	Color8Bit Color;

	Color.Color = ::GetPixel(ImageDC, _X, _Y);

	return Color;
}

void UWindowImage::BitCopy(UWindowImage* _CopyImage, const FTransform& _Trans)
{	
	HDC hdc = ImageDC;
	
	HDC hdcSrc = _CopyImage->ImageDC;
	BitBlt(
		hdc, 							  // HDC hdc,  
		_Trans.iLeft(), 				  // int x,    
		_Trans.iTop(), 					  // int y,    
		_Trans.GetScale().iX(), 		  // int cx,   
		_Trans.GetScale().iY(),			  // int cy,  
		hdcSrc,							  // HDC hdcSrc, 
		0,								  // int x1,  
		0,								  // int y1, 
		SRCCOPY							  // DWORD rop => 이미지 그대로 고속 복사를 해라.
	);
}

void UWindowImage::TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "이미지 정보의 인덱스를 오버하여 사용했습니다");
	}

	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;


	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();


	HDC hdc = ImageDC;
	// 이미지
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	TransparentBlt(
		hdc, 									 // HDC hdc, 
		RenderLeft, 							 // int x,   
		RenderTop, 								 // int y,   
		RenderScaleX, 							 // int cx,  
		RenderScaleY,							 // int cy,  
		hdcSrc,									 // HDC hdcSrc, 
		ImageLeft,								 // int y1, 
		ImageTop,								 // int x1,  
		ImageScaleX,							 // int y1, 
		ImageScaleY,							 // int y1, 
		_Color.Color							 // DWORD rop => 이미지 그대로 고속 복사를 해라.
	);
}

void UWindowImage::AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "이미지 정보의 인덱스를 오버하여 사용했습니다");
	}


	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();


	HDC hdc = ImageDC;
	// 이미지
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	BLENDFUNCTION Function;
	Function.BlendOp = AC_SRC_OVER;
	Function.BlendFlags = 0;
	Function.SourceConstantAlpha = _Color.A;
	Function.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hdc, 							 // HDC hdc,  
		RenderLeft, 					 // int x,    
		RenderTop, 						 // int y,    
		RenderScaleX,					 // int cx,   
		RenderScaleY,					 // int cy,  
		hdcSrc,							 // HDC hdcSrc, 
		ImageLeft,   					 // int y1, 
		ImageTop,   					 // int x1,  
		ImageScaleX, 					 // int y1, 
		ImageScaleY, 					 // int y1, 
		Function
	);
}

bool UWindowImage::Create(HDC _MainDC)
{
	ImageDC = _MainDC;

	if (nullptr == ImageDC)
	{
		return false;
	}

	return true;
}
