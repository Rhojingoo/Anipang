#pragma once
#include "UI_OBJ.h"

class AMainScreen_UI : public UUI_OBJ
{
public:
	AMainScreen_UI();
	~AMainScreen_UI();

	AMainScreen_UI(const AMainScreen_UI& _Other)					= delete;
	AMainScreen_UI(AMainScreen_UI& _Other) noexcept					= delete;
	AMainScreen_UI& operator =(const 	AMainScreen_UI& _Other)		= delete;
	AMainScreen_UI& operator =(AMainScreen_UI& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

