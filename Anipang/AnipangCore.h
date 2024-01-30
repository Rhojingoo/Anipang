#pragma once
#include <EngineCore\EngineCore.h>

class AnipangCore : public EngineCore
{
public : 
	AnipangCore();
	~AnipangCore();

	AnipangCore(const AnipangCore& _Other)							 = delete;
	AnipangCore(AnipangCore& _Other) noexcept						 = delete;
	AnipangCore& operator =(const 	AnipangCore& _Other)			 = delete;
	AnipangCore& operator =(AnipangCore& _Other)noexcept			 = delete;

protected:
	void BeginPlay()	override;
	void Tick(float _DeltaTime)	override;
	void End()		override;

private:
};

