#pragma once
#include "Base_Block.h"

class AMouse_Block : public ABase_Block
{
public:
	AMouse_Block();
	~AMouse_Block();

	AMouse_Block(const AMouse_Block& _Other)						= delete;
	AMouse_Block(AMouse_Block& _Other) noexcept						= delete;
	AMouse_Block& operator =(const AMouse_Block& _Other)			= delete;
	AMouse_Block& operator =(AMouse_Block& _Other) noexcept			= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};
