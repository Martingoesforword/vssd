#include "vssdCat.h"   
namespace sjh { 
	 
	void vssdCat::vCat(vssd_disk & MyVssd, std::wstring & Rear)
	{
		tools_path a;
		//�ҵ���Ҫָ����ļ���
		vssd_inode * SrcInode = vssd_vcmd::v_FindPathForFirst(MyVssd, Rear, a);
		if (SrcInode) SrcInode->PrintContent();
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}

	}
	int vssdCat::Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear)
	{
		return EXE_OK;
	}

}