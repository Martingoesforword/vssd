#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_manager.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h"
#include "vssdDel.h"
namespace sjh {
	class vssdRd :public base_executable
	{
		void vRd(vssd_manager & MyVssd, std::wstring & RdCommand);
	public:
		virtual int Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear);

	};
}