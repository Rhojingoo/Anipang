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

	FVector GetSize()
	{
		return Size;
	}
	FVector GetPos()
	{
		return Pos;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer	 = nullptr;
	FVector Pos					 = {};
	FVector Size				 = {};
};

