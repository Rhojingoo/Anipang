#pragma once
#include <EngineCore\Actor.h>

class ACursor : public AActor
{
public:
	ACursor();
	~ACursor();

	ACursor(const ACursor& _Other)								= delete;
	ACursor(ACursor& _Other) noexcept							= delete;
	ACursor& operator =(const ACursor& _Other)					= delete;
	ACursor& operator =(ACursor& _Other) noexcept				= delete;

	FVector GetSize()
	{
		return Size;
	}
	FVector GetPos()
	{
		return Pos;
	}

	void UIEnter(bool _set) { EnterUI = _set; }


protected:
	void BeginPlay() override; 
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool				 = 0.0f;
	UImageRenderer* Renderer		 = nullptr;
	float AnimationTime				 = 0.0f;
	int AnimationFrame				 = 0;
	FVector Pos						 = {};
	FVector Size					 = {};
	bool EnterUI					 = false;
};

