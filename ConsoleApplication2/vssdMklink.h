#pragma once 
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
#include "vssdMkdir.h" 

namespace sjh {

	class vssdMklink :public sjh::base_executable
	{ 
	public:
		void vMklink(sjh::VirtualDisk & MyVssd, std::wstring & Src, std::wstring & LinkName);
		virtual int Execute(sjh::VirtualDisk & MyVssd, std::vector<std::wstring> Rear);
	};
}