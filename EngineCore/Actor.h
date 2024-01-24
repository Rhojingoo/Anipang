#pragma once
#include <EngineBase\FTransform.h>
#include "TickObject.h"
#include "NameObject.h"


// 설명 : A가 붙은 오브젝트는 화면에 위치가 존재해야한다.
class ULevel;
class AActor : public UNameObject, public UTickObject
{
	friend ULevel;

public : 
	AActor();
	~AActor();

	AActor(const AActor& _Other)							= delete;
	AActor(AActor& _Other) noexcept							= delete;
	AActor& operator =(const 	AActor& _Other)				= delete;
	AActor& operator =(AActor& _Other)noexcept				= delete;

	FVector GetActorLocation()
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	void SetActorScale(FVector _Value)
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	ULevel* GetWorld()
	{
		return World;
	}


protected:

private:
	ULevel* World;
	FTransform Transform;

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

