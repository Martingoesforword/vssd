#pragma once  
#include "pch.h"  
namespace sjh { 
	class base_contentable
	{
	private:
		std::vector<wchar_t> Content;
	public:
		virtual std::vector<wchar_t>& GetContent() { return Content; };
		base_contentable();
		~base_contentable();
	};

}