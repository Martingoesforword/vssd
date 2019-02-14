#include "pch.h"
#include "vssdMklink.h"
namespace sjh {
	void vssdMklink::vMklink(VirtualDisk & MyVssd, std::wstring & Src, std::wstring & LinkName)
	{

		//找到需要指向的文件夹
		tools_path a;
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Src, a);

		if (SrcInode && a.Inodes.size() >= 3)
		{
			//找到之后
			size_t posq = LinkName.find_last_of(L"\\");
			size_t posp = LinkName.find_last_of(L"/");
			posp = posp > posq ? posp : posq;
			std::wstring InodeOfLinkPath = LinkName.substr(0, posp - 0);
			vssdMkdir taskMd;
			//vssd_inode *InodeOfLink = taskMd.vMd(MyVssd, InodeOfLinkPath);

			//创建Link文件
			vssd_inode *Link = new vssd_inode(L"", vssd_inode::IS_LINK);
			//InodeOfLink->LoadOneSub(Link);
			//找到创建的Link文件
			Link->LoadOneSub(SrcInode);
			//将Link文件第一个子文件放入指向文件 

			//同时把路径放入
			Link->SetLinkPath(a);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}
	}
	void vssdMklink::Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}
}