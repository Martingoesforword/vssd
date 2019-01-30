#include "pch.h" 
 
void sjh::vssdCat::vCat(vssd_disk & MyVssd, std::wstring & Rear)
{
	tool_path a;
	//找到需要指向的文件夹
	sjh::vssd_Inode * SrcInode = vssd_vcmd::v_FindPathForFirst(MyVssd, Rear, a);
	if (SrcInode) SrcInode->PrintContent();
	else
	{ 
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}

}