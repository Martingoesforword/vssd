#pragma once  
#include "pch.h"  
namespace sjh {
	class vssd_name
	{
	private:
		std::wstring Name;
	public:
		//原始构造
		vssd_name();
		vssd_name(std::wstring aName);

		//name相关
		void				Set(std::wstring aName);
		const std::wstring&	Get() const; 
	}; 
}