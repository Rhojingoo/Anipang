#pragma once
#include "UI_OBJ.h"

class ACheckScore_UI : public UUI_OBJ
{
public:
	ACheckScore_UI();
	~ACheckScore_UI();

	ACheckScore_UI(const ACheckScore_UI& _Other)					= delete;
	ACheckScore_UI(ACheckScore_UI& _Other) noexcept					= delete;
	ACheckScore_UI& operator =(const 	ACheckScore_UI& _Other)		= delete;
	ACheckScore_UI& operator =(ACheckScore_UI& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

