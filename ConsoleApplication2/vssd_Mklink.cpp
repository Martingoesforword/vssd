#include "pch.h" 
void sjh::vssdMklink::vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	
	//找到需要指向的文件夹
	tool_path a;
	sjh::vssd_Inode * SrcInode = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

	if (SrcInode && a.Inodes.size() >= 3)
	{
		//找到之后
		int posq = LinkName.find_last_of(L"\\");
		int posp = LinkName.find_last_of(L"/");
		posp = posp > posq ? posp : posq;
		std::wstring InodeOfLinkPath = LinkName.substr(0, posp-0);
		sjh::vssd_Inode *InodeOfLink = vssdMd::vMd(MyVssd, InodeOfLinkPath);
		
		//创建Link文件
		sjh::vssd_Inode *Link = new sjh::vssd_Inode(L"", sjh::vssd_Inode::IS_LINK); 
		InodeOfLink->LoadOneSub(Link); 
		//找到创建的Link文件
		Link->LoadOneSub(SrcInode);
		//将Link文件第一个子文件放入指向文件 
	}
	else
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}
}
