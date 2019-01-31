#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdCopy :public base_executable
	{
		void vCopy(vssd_disk & MyVssd, std::wstring & Src, std::wstring & Des);
	public:

		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);
	};
}