#pragma once
#include <EngineCore\Actor.h>

class ACombo_OBJ : public AActor
{
public:
	ACombo_OBJ();
	~ACombo_OBJ();

	ACombo_OBJ(const ACombo_OBJ& _Other)					= delete;
	ACombo_OBJ(ACombo_OBJ& _Other) noexcept					= delete;
	ACombo_OBJ& operator =(const 	ACombo_OBJ& _Other)		= delete;
	ACombo_OBJ& operator =(ACombo_OBJ& _Other)noexcept		= delete;

	void SetCombo(int _SET) { combo = _SET; }
	void ClearCombo() { combo = 0; }
	void SetFont();


protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string Text = "";
	int combo = 0;
	float Time = 1.0f;
	bool RenderON = false;
	bool RenderOFF = false;
	float Speed = 50.f;
};

