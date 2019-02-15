#pragma once  
#include "pch.h"  
namespace sjh { 
	class base_contentable
	{
	protected:
		std::vector<wchar_t>	Content;
	public:
		virtual const std::vector<wchar_t>&	GetContent() const { return Content; }; 
	};

}