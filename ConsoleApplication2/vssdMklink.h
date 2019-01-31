#pragma once 
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_manager.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
#include "vssdMkdir.h" 

namespace sjh {

	class vssdMklink :public sjh::base_executable
	{ 
	public:
		void vMklink(sjh::vssd_manager & MyVssd, std::wstring & Src, std::wstring & LinkName);
		virtual int Execute(sjh::vssd_manager & MyVssd, std::vector<std::wstring> Rear);
	};
}