#pragma once
#include <EngineCore\Actor.h>


class ANumberFont : public AActor
{
public : 
	ANumberFont();
	~ANumberFont();

	ANumberFont(const ANumberFont& _Other)					 = delete;
	ANumberFont(ANumberFont& _Other) noexcept				 = delete;
	ANumberFont& operator =(const ANumberFont& _Other)		 = delete;
	ANumberFont& operator =(ANumberFont& _Other) noexcept	 = delete;

	void SetFont(std::string_view  _Text, float _Size)
	{
		Text = _Text;
		Renderer->SetText(Text);
		Renderer->SetTextSize(_Size);
	}

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string Text = "";
};

