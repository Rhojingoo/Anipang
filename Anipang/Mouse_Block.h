#pragma once
#include "Animal_Block.h"

class AMouse_Block : public AAnimal_Block
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
