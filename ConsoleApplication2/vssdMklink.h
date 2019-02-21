#pragma once 
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h"  
namespace sjh {
	class vssdMkdir;
	class vssdMklink :public sjh::base_executable
	{
		//vssd_inode*  (*friendfunc(vssdMkdir& taskMd))(VirtualDisk & MyVssd, const std::wstring & mdCommand);
		void vMklink(sjh::VirtualDisk & MyVssd, const std::wstring & Src, const std::wstring & LinkName);
		void vMklinkF(VirtualDisk & MyVssd, const std::wstring & Src, const std::wstring & LinkName);
		void vMklinkSwitch( VirtualDisk & MyVssd, std::vector<std::wstring> Dirs);
	public: 
		virtual int Execute(sjh::VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear);
	};
}