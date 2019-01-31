#pragma once  
#include "pch.h"  
#include "base_executable.h"  
#include "vssd_disk.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdLoad :public base_executable
	{
		void vLoad(vssd_disk & MyVssd, std::wstring & GetFrom);
	public:

		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);

	};
}