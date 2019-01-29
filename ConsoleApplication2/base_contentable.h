#pragma once
#include "pch.h"
class base_contentable
{
private:
	std::vector<wchar_t> Content;
public:
	virtual std::vector<wchar_t>& GetContent() { return Content; }; 
	base_contentable();
	~base_contentable();
};

