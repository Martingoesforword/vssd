#include "pch.h"
#include "vssdMklink.h"
namespace sjh {
	void vssdMklink::vMklink(vssd_manager & MyVssd, std::wstring & Src, std::wstring & LinkName)
	{

		//找到需要指向的文件夹
		tools_path a;
		vssd_inode * SrcInode = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

		if (SrcInode && a.Inodes.size() >= 3)
		{
			//找到之后
			int posq = LinkName.find_last_of(L"\\");
			int posp = LinkName.find_last_of(L"/");
			posp = posp > posq ? posp : posq;
			std::wstring InodeOfLinkPath = LinkName.substr(0, posp - 0);
			vssdMkdir taskMd;
			vssd_inode *InodeOfLink = taskMd.vMd(MyVssd, InodeOfLinkPath);

			//创建Link文件
			vssd_inode *Link = new vssd_inode(L"", vssd_inode::IS_LINK);
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
	int vssdMklink::Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear)
	{
		return 0;
	}
}