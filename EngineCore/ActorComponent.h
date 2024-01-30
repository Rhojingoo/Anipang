#pragma once
#include "TickObject.h"

class AActor;
class UActorComponent : public UTickObject
{
	friend AActor;

public:
	UActorComponent();
	~UActorComponent();

	UActorComponent(const UActorComponent& _Other)						= delete;
	UActorComponent(UActorComponent&& _Other) noexcept					= delete;
	UActorComponent& operator=(const UActorComponent& _Other)			= delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept		= delete;

	AActor* GetOwner()
	{
		return Owner;
	}

protected:

private:
	AActor* Owner = nullptr;

	void SetOwner(AActor* _Owner)
	{
		Owner = _Owner;
	}
};

