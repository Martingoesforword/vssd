#include "pch.h"  
#include "vssdCat.h"   
namespace sjh { 
	 
	void vssdCat::vCat(VirtualDisk & MyVssd, std::wstring & Rear)
	{
		tools_path a;
		//�ҵ���Ҫָ����ļ���
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Rear, a);
		if (SrcInode) SrcInode->PrintContent();
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}

	}
	void vssdCat::Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}

}