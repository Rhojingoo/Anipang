#pragma once
#include <EngineCore\Actor.h>

class AFadeIN_OUT : public AActor
{
public:
	AFadeIN_OUT();
	~AFadeIN_OUT();

	AFadeIN_OUT(const AFadeIN_OUT& _Other)						= delete;
	AFadeIN_OUT(AFadeIN_OUT& _Other) noexcept					= delete;
	AFadeIN_OUT& operator =(const 	AFadeIN_OUT& _Other)		= delete;
	AFadeIN_OUT& operator =(AFadeIN_OUT& _Other)noexcept		= delete;

	void EndWidonw() { WindowEnd = true, CheckAlpha = 0.f; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer			 = nullptr;
	float AlphaTime						 = 0.0f;
	float CheckAlpha					 = 1.0f;
	bool Dir							 = false;
	bool WindowEnd						 = false;
};

