#pragma once  
#include "pch.h"  
#include "base_executable.h"  
#include "vssd_optcmd.h"  
#include "tools_path.h" 
#include "vssd_inode.h"   
#include "tools_vssd.h"  
#include "vssdMklink.h"
namespace sjh { 
	class vssdMkdir :public sjh::base_executable
	{
		
 		//friend vssd_inode*  (* vssdMklink::friendfunc(vssdMkdir& taskMd))(VirtualDisk & MyVssd, const std::wstring & mdCommand);

	public: 
		vssd_inode* vMd(VirtualDisk & MyVssd, const std::wstring & mdCommand);
		virtual int Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear);

	};
}