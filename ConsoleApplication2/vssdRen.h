#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdRen :public base_executable
	{
		void vRen(VirtualDisk & MyVssd, const std::wstring SrcCommand, const std::wstring DesName);
	public:
		virtual int Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear);

	};
}