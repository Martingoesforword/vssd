#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdCopy :public base_executable
	{
		void vCopy(VirtualDisk & MyVssd, std::wstring & Src, std::wstring & Des);
	public:

		virtual int Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear);
	};
}