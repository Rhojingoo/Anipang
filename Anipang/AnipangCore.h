#pragma once
#include <EngineCore\EngineCore.h>

class UAnipangCore : public UEngineCore
{
public : 
	UAnipangCore();
	~UAnipangCore();

	UAnipangCore(const UAnipangCore& _Other)						 = delete;
	UAnipangCore(UAnipangCore& _Other) noexcept						 = delete;
	UAnipangCore& operator =(const 	UAnipangCore& _Other)			 = delete;
	UAnipangCore& operator =(UAnipangCore& _Other)noexcept			 = delete;


protected:
	void BeginPlay()	override;
	void Tick(float _DeltaTime)	override;
	void WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath) override;

private:
};

