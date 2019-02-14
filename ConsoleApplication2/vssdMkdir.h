#pragma once  
#include "pch.h"  
#include "base_executable.h"  
#include "vssd_optcmd.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h"  
#include "vssdMklink.h"
namespace sjh { 
	class vssdMkdir :public sjh::base_executable
	{
		vssd_inode* vMd(VirtualDisk & MyVssd, std::wstring & mdCommand);
	public:
		 
		virtual void Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear);

	};
}