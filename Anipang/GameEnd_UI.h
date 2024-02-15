#pragma once
#include "UI_OBJ.h"


class AGameEnd_UI : public UUI_OBJ
{
public:
	AGameEnd_UI();
	~AGameEnd_UI();

	AGameEnd_UI(const AGameEnd_UI& _Other)						= delete;
	AGameEnd_UI(AGameEnd_UI& _Other) noexcept					= delete;
	AGameEnd_UI& operator =(const 	AGameEnd_UI& _Other)		= delete;
	AGameEnd_UI& operator =(AGameEnd_UI& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
};

