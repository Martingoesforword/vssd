#pragma once  
#include "pch.h"  
#include "base_executable.h"  
#include "vssd_vcmd.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h"  
#include "vssdMklink.h"
namespace sjh { 
	class vssdMkdir :public sjh::base_executable
	{
		sjh::vssd_inode* vMd(sjh::vssd_disk & MyVssd, std::wstring & mdCommand);
	public:
		friend void sjh::vssdMklink::vMklink(sjh::vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName);
		virtual int Execute(sjh::vssd_disk & MyVssd, std::vector<std::wstring> Rear);

	};
}