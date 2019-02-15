#pragma once  
#include "pch.h"  
namespace sjh {
	class base_namedable
	{
	protected:
		std::wstring Name;
	public:
		//原始构造
		base_namedable(std::wstring aName);

		//name相关
		void				SetName(std::wstring aName);
		const std::wstring&	GetName() const; 
	}; 
}