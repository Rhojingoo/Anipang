#pragma once
#include "UI_OBJ.h"

class AGameStart_UI : public UUI_OBJ
{
public : 
	AGameStart_UI();
	~AGameStart_UI();

	AGameStart_UI(const AGameStart_UI& _Other)						= delete;
	AGameStart_UI(AGameStart_UI& _Other) noexcept					= delete;
	AGameStart_UI& operator =(const AGameStart_UI& _Other)			= delete;
	AGameStart_UI& operator =(AGameStart_UI& _Other) noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

