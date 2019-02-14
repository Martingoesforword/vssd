#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdSave :public base_executable
	{
		void vSave(VirtualDisk & MyVssd, std::wstring & JumpTo);
	public:
		virtual void Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear);

	};
}