#pragma once
#include <EngineCore\Actor.h>

class ATitle_Button : public AActor
{
public : 
	ATitle_Button();
	~ATitle_Button();

	ATitle_Button(const ATitle_Button& _Other)						= delete;
	ATitle_Button(ATitle_Button& _Other) noexcept					= delete;
	ATitle_Button& operator =(const ATitle_Button& _Other)			= delete;
	ATitle_Button& operator =(ATitle_Button& _Other) noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
};

