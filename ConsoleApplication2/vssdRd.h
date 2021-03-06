#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h"
#include "vssdDel.h"
namespace sjh {
	class vssdRd :public base_executable
	{
		void vRd(VirtualDisk & MyVssd, const std::vector<std::wstring>& Dels, int PosDel, int DEL_TYPE);
		void vRd(VirtualDisk & MyVssd, const std::vector<std::wstring>& Dels);
	public:
		virtual int Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear);

	};
}