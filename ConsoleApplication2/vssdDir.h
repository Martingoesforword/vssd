#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_manager.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdDir :public base_executable
	{
		void vDir(vssd_manager & MyVssd, int Type);
		void vDir(vssd_manager & MyVssd, std::vector<std::wstring> Dirs, int Type);
		void vDir(vssd_manager & MyVssd, std::wstring & DirCommand);
	public:

		virtual int Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear);
	};
}