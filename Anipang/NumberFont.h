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

	void SetFontColor(Color8Bit _OutLineColor, Color8Bit _FillColor)
	{
		Renderer->SetTextColor(_OutLineColor, _FillColor);
	}

	void FontCenterOn()
	{
		Renderer->TextCneterOn();
	}
	void FontCenterOff()
	{
		Renderer->TextCneterOff();
	}

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string Text = "";
};

