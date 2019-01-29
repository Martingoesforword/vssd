#pragma once
#include "pch.h"
class base_namedable:public sjh::base_displayable
{
protected:
	std::wstring Name;
public:
	std::wstring GetName(); 
	void SetName(std::wstring aName);
	base_namedable(std::wstring aName);
	~base_namedable();

	virtual void Display();
};

