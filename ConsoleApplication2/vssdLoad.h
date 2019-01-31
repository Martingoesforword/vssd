#pragma once  
#include "pch.h"  
#include "base_executable.h"  
#include "vssd_manager.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdLoad :public base_executable
	{
		void vLoad(vssd_manager & MyVssd, std::wstring & GetFrom);
	public:

		virtual int Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear);

	};
}