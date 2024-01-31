#pragma once
#include <EngineBase\Transform.h>
#include "TickObject.h"
#include <EngineBase\NameObject.h>
#include "ImageRenderer.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class UImageRenderer;
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

	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
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

	UImageRenderer* CreateImageRenderer(int Order = 0);

	void Destroy(float _DestroyTime) override;
	void DestroyUpdate(float _DeltaTime) override;

protected:
	void Tick(float _DeltaTime) override;

private:
	std::list<UImageRenderer*> Renderers;


	ULevel* World = nullptr;
	FTransform Transform = FTransform();

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

