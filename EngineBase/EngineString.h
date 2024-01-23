#pragma once


class EngineString
{
public : 
	EngineString();
	~EngineString();

	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString& _Other) noexcept = delete;
	EngineString& operator =(const 	EngineString& _Other) = delete;
	EngineString& operator =(EngineString& _Other)noexcept = delete;

protected:

private:
};

