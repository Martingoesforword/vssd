#pragma once  
#include "pch.h"  
namespace sjh {
	class base_namedable
	{
	protected:
		std::wstring Name;
	public:
		//ԭʼ����
		base_namedable(std::wstring aName);

		//name���
		void				SetName(std::wstring aName);
		const std::wstring&	GetName() const; 
	}; 
}