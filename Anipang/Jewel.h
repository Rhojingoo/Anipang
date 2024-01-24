#pragma once
#include <EngineCore\Actor.h>

class Jewel : public AActor
{
public : 
	Jewel();
	~Jewel();

	Jewel(const Jewel& _Other)					 = delete;
	Jewel(Jewel& _Other) noexcept				 = delete;
	Jewel& operator =(const Jewel& _Other)		 = delete;
	Jewel& operator =(Jewel& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

