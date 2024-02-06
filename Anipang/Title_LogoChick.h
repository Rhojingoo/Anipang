#pragma once
#include <EngineCore\Actor.h>

class ATitle_LogoChick : public AActor
{
public:
	ATitle_LogoChick();
	~ATitle_LogoChick();

	ATitle_LogoChick(const ATitle_LogoChick& _Other)						= delete;
	ATitle_LogoChick(ATitle_LogoChick& _Other) noexcept					= delete;
	ATitle_LogoChick& operator =(const 	ATitle_LogoChick& _Other)		= delete;
	ATitle_LogoChick& operator =(ATitle_LogoChick& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
};

