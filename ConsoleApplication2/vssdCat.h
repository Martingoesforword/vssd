#pragma once   
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_optcmd.h"  
#include "tools_path.h" 
#include "vssd_pan.h"  
#include "vssd_inode.h" 
namespace sjh {
	class VirtualDisk;
	class vssdCat :public base_executable
	{
		void vCat(VirtualDisk & MyVssd, std::wstring & Rear);
	public:
		virtual int Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear);
	};
}