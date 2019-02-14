#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 

namespace sjh {
	class vssdDir :public base_executable
	{
		void vDir(VirtualDisk & MyVssd, int Type);
		void vDir(VirtualDisk & MyVssd, std::vector<std::wstring> DirsDirs, int Pos, int Type);
		void vDir(VirtualDisk & MyVssd, std::vector<std::wstring> Dirs); 
	public: 
		virtual void Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear); 
		~vssdDir() { }
	};
}