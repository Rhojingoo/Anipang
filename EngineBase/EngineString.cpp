#include "EngineString.h"

std::string EngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}

EngineString::EngineString()
{
}

EngineString::~EngineString()
{
}
