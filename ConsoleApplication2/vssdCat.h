#pragma once   
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h"  
#include "tools_path.h" 
#include "vssd_pan.h"  
#include "vssd_inode.h" 
namespace sjh {
	class vssd_disk;
	class vssdCat :public base_executable
	{
		void vCat(vssd_disk & MyVssd, std::wstring & Rear);
	public:
		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);
	};
}