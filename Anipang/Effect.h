#pragma once


class Effect
{
public : 
	Effect();
	~Effect();

	Effect(const Effect& _Other) = delete;
	Effect(Effect& _Other) noexcept = delete;
	Effect& operator =(const 	Effect& _Other) = delete;
	Effect& operator =(Effect& _Other)noexcept = delete;

protected:

private:
};

