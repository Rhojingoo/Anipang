#pragma once
#include "UI_OBJ.h"

class AReStart_UI : public UUI_OBJ
{
public:
	AReStart_UI();
	~AReStart_UI();

	AReStart_UI(const AReStart_UI& _Other)					= delete;
	AReStart_UI(AReStart_UI& _Other) noexcept					= delete;
	AReStart_UI& operator =(const 	AReStart_UI& _Other)		= delete;
	AReStart_UI& operator =(AReStart_UI& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

