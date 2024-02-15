#pragma once
#include <EngineCore\Actor.h>
#include "Cursor.h"

class UUI_OBJ : public AActor
{
public:
	UUI_OBJ();
	~UUI_OBJ();

	UUI_OBJ(const UUI_OBJ& _Other)					= delete;
	UUI_OBJ(UUI_OBJ& _Other) noexcept					= delete;
	UUI_OBJ& operator =(const 	UUI_OBJ& _Other)		= delete;
	UUI_OBJ& operator =(UUI_OBJ& _Other)noexcept		= delete;

	FVector GetSize()
	{
		return Size;
	}

	FVector GetPos()
	{
		return Pos;
	}

	void SetCursor(ACursor* _Cursor) 
	{
		Cursor = _Cursor; 
	}


protected:
	enum class ButtonState
	{
		None,
		ON_Button,
		Click,
		End,
	};

	ButtonState UIstate = ButtonState::None;
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};
	FVector Size = {};
	bool ButtonClick = false;
	bool OnButton = false;
		
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	ACursor* Cursor = nullptr;
};

