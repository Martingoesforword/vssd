#include "pch.h"  
#include "vssdCat.h"   
namespace sjh { 
	 
	void vssdCat::vCat(VirtualDisk & MyVssd, std::wstring & Rear)
	{
		 
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Rear);
		if (SrcInode) SrcInode->PrintContent();
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}

	}
	int vssdCat::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		return EXE_OK;
	}

}