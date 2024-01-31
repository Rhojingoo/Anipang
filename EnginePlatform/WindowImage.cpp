#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>

// �����쿡�� �̹����� ����ϱ� ���ؼ� �����ϴ� ���̺귯��.
// ����� �ٸ��� ���̺귯���� #pragma comment ���ؼ� �߰� �ؾ� �Ѵ�.
#pragma comment(lib, "Msimg32.lib")

#include <objidl.h>
#include <gdiplus.h>

// Png�� �ε��ϴ� ����� ������ �⺻ ���̺귯�������� ���������� �ʱ� ������ GDIPlus�� ����ؾ� �Ѵ�.
// GIDPlus�� �����찡 �ʱ� �������� �׷��� �ý����� �����ؼ� �߰��� ���̺귯����.
#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage() 
{
}

UWindowImage::~UWindowImage() 
{
	DeleteObject(hBitMap);
	DeleteDC(ImageDC);
}

bool UWindowImage::Load(UWindowImage* _Image)
{
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
			MsgBoxAssert("Png ���� ���ҽ� �ε忡 �����߽��ϴ�.");
		}

		ImageType = EWIndowImageType::IMG_PNG;
	}

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
		return false;
	}

	HBITMAP OldBitMap = (HBITMAP)SelectObject(ImageDC, hBitMap);
	DeleteObject(OldBitMap);
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

FVector UWindowImage::GetScale()
{
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}


bool UWindowImage::Create(UWindowImage* _Image, const FVector& _Scale)
{
	// ������ ���� �̹����� �����.


	// HBITMAP ��Ʈ�� �̹����� �޸𸮱���
	HANDLE ImageHandle = CreateCompatibleBitmap(_Image->ImageDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
		return false;
	}

	hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// hBitMap���� �����ڴ�.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
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
		SRCCOPY							  // DWORD rop => �̹��� �״�� ��� ���縦 �ض�.
	);
}

void UWindowImage::TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, const FTransform& _ImageTrans, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr �� �̹����� ������ �� �����ϴ�");
	}

	HDC hdc = ImageDC;
	// �̹���
	HDC hdcSrc = _CopyImage->ImageDC;
	TransparentBlt(
		hdc, 							  // HDC hdc, // 
		_Trans.iLeft(), 				  // int x,   // 
		_Trans.iTop(), 					  // int y,   // 
		_Trans.GetScale().iX(), 		  // int cx,  // 
		_Trans.GetScale().iY(),			  // int cy,  
		hdcSrc,							// HDC hdcSrc, 
		_ImageTrans.GetPosition().iX(),								// int y1, 
		_ImageTrans.GetPosition().iY(),								// int x1,  
		_ImageTrans.GetScale().iX(),								// int y1, 
		_ImageTrans.GetScale().iY(),								// int y1, 
		_Color.Color						// DWORD rop => �̹��� �״�� ��� ���縦 �ض�.
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
