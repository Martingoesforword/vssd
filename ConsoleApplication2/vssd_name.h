#pragma once  
#include "pch.h"  
namespace sjh {
	class vssd_name
	{
	private:
		std::wstring Name;
	public:
		//ԭʼ����
		vssd_name();
		vssd_name(std::wstring aName);

		//name���
		void				Set(std::wstring aName);
		const std::wstring&	Get() const; 
	}; 
}