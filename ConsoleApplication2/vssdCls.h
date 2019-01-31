#pragma once   
#include "pch.h"  
#include "base_executable.h" 

namespace sjh {
	class vssd_disk;  
	class vssdCls :public base_executable
	{
		void vCls();
	public:
		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);
	};
}