#pragma once  
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h" 
namespace sjh {
	class vssdRen :public base_executable
	{
		void vRen(vssd_disk & MyVssd, std::wstring & SrcCommand, std::wstring & DesName);
	public:
		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);

	};
}