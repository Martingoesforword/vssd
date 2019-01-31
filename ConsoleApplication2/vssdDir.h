#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdDir :public base_executable
	{
		void vDir(vssd_disk & MyVssd, int Type);
		void vDir(vssd_disk & MyVssd, std::vector<std::wstring> Dirs, int Type);
		void vDir(vssd_disk & MyVssd, std::wstring & DirCommand);
	public:

		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);
	};
}