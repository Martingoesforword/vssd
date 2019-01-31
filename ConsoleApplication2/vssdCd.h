#pragma once 
#include "pch.h"  
#include "base_executable.h" 
#include "vssd_vcmd.h" 
#include "vssd_manager.h"  
#include "tools_path.h" 
#include "vssd_inode.h" 
namespace sjh {
	 
	class vssdCd :public base_executable
	{
		void vCd(vssd_manager & MyVssd);
		void vCd(vssd_manager & MyVssd, std::wstring & CdCommand);
	public:
		virtual int Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear);
	};
}