#pragma once 
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h" 
namespace sjh {
	 
	class vssdCd :public base_executable
	{
		void vCd(VirtualDisk & MyVssd);
		void vCd(VirtualDisk & MyVssd, std::wstring & CdCommand);
	public:
		virtual void Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear);
	};
}