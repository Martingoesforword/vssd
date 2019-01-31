#pragma once 
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_disk.h"  
#include "tools_path.h" 
#include "vssd_inode.h" 
namespace sjh {
	 
	class vssdCd :public base_executable
	{
		void vCd(vssd_disk & MyVssd);
		void vCd(vssd_disk & MyVssd, std::wstring & CdCommand);
	public:
		virtual int Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear);
	};
}