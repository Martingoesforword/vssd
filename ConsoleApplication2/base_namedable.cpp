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

void sjh::base_namedable::Display()
{
	std::wcout << L"<base_info class>"<<std::endl;
	std::wcout << L"\tName = " << Name << std::endl; 
}
