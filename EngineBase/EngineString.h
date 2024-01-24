#pragma once
#include <string>
#include <string_view>

class EngineString
{
public : 
	static std::string ToUpper(std::string_view View);

protected:

private:
	EngineString();
	~EngineString();

	EngineString(const EngineString& _Other)					= delete;
	EngineString(EngineString& _Other) noexcept					= delete;
	EngineString& operator =(const 	EngineString& _Other)		= delete;
	EngineString& operator =(EngineString& _Other)noexcept		= delete;
};

