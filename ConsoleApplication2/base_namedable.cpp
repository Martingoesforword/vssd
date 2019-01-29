#include "pch.h"
 

std::wstring sjh::base_namedable::GetName()
{
	return Name;
}

void sjh::base_namedable::SetName(std::wstring aName)
{
	Name = aName;
}
 
sjh::base_namedable::base_namedable(std::wstring aName)
{
	Name = aName;
}
 


sjh::base_namedable::~base_namedable()
{
}

 