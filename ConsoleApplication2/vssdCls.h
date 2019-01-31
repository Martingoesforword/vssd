#pragma once   
#include "pch.h"  
#include "base_executable.h" 

namespace sjh {
	class vssd_manager;  
	class vssdCls :public base_executable
	{
		void vCls();
	public:
		virtual int Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear);
	};
}