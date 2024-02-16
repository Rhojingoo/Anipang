#pragma once
#include <EngineBase\Transform.h>
#include "TickObject.h"
#include <EngineBase\NameObject.h>
#include "ImageRenderer.h"
#include "Collision.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class UImageRenderer;
class UCollision;
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


	template<typename EnumType>
	UCollision* CreateCollision(EnumType _Order = 0)
	{
		return CreateCollision(static_cast<int>(_Order));
	}

	template<typename EnumType>
	UImageRenderer* CreateImageRenderer(EnumType _Order = 0)
	{
		return CreateImageRenderer(static_cast<int>(_Order));
	}

	UCollision* CreateCollision(int _Order = 0);
	UImageRenderer* CreateImageRenderer(int _Order = 0);

	void Destroy(float _DestroyTime = 0.0f) override;
	void DestroyUpdate(float _DeltaTime) override;

	void ActiveUpdate(float _DeltaTime) override;

	void CheckReleaseChild();

	void AllRenderersActiveOff();
	void AllRenderersActiveOn();

protected:
	void Tick(float _DeltaTime) override;

private:
	std::list<UImageRenderer*> Renderers;
	std::list<UCollision*> Collisions;


	ULevel* World = nullptr;
	FTransform Transform = FTransform();

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

