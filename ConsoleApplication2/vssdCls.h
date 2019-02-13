#pragma once   
#include "pch.h"  
#include "base_executable.h" 

namespace sjh {
	class VirtualDisk;  
	class vssdCls :public base_executable
	{
		void vCls();
	public:
		virtual int Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear);
	};
}