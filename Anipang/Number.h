#pragma once
#include <EngineCore\Actor.h>

class ANumber : public AActor
{
public:
	enum class NumberState
	{
		None,
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		end
	};


	ANumber();
	~ANumber();

	ANumber(const ANumber& _Other)						= delete;
	ANumber(ANumber& _Other) noexcept					= delete;
	ANumber& operator =(const 	ANumber& _Other)		= delete;
	ANumber& operator =(ANumber& _Other)noexcept		= delete;

	void SetNumber(int _set);
	void SetNumScale(int _X, int _Y)
	{
		Renderer->SetScale({ _X,_Y });
	}


protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	NumberState NumState = NumberState::None;
	int Number = 0;

};

