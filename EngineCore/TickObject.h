#pragma once
#include <EngineBase\EngineDebug.h>

class UTickObject
{
public:
	UTickObject();
	~UTickObject();

	UTickObject(const UTickObject& _Other)								= delete;
	UTickObject(UTickObject&& _Other) noexcept							= delete;
	UTickObject& operator=(const UTickObject& _Other)					= delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept				= delete;

	void ActiveOn()
	{
		IsActiveValue = true;
	}

	void ActiveOff()
	{
		IsActiveValue = false;
	}

	void SetActive(bool _Active)
	{
		IsActiveValue = _Active;
	}

	bool IsActive()
	{
		return IsActiveValue && IsDestroyValue == false;
	}


	virtual void Destroy(float _DestroyTime = 0.0f)
	{
		IsDestroyUpdate = true;
		DestroyTime = _DestroyTime;
		if (0.0f >= _DestroyTime)
		{
			this->IsDestroyValue = true;
		}
	}

	int GetOrder()
	{
		return Order;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}


	virtual void DestroyUpdate(float _DeltaTime)
	{
		if (false == IsDestroyUpdate)
		{
			return;
		}

		DestroyTime -= _DeltaTime;
		if (0.0f >= DestroyTime)
		{
			Destroy(0.0f);
		}
	}

	bool IsDestroy()
	{
		return IsDestroyValue;
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

protected:

private:
	int Order = 0;
	bool IsDestroyUpdate = false;
	float DestroyTime = 0.0f;
	bool IsActiveValue = true;
	bool IsDestroyValue = false;
};

