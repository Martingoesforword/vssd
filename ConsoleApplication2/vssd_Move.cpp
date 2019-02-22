#include "pch.h"
#include "vssdMove.h"
namespace sjh { 
	//ÒÆ¶¯ÎÄ¼þ¼Ð
	void vssdMove::vMove(VirtualDisk & MyVssd, const std::wstring & Src, const std::wstring & Des)
	{

		tools_path a;
		tools_path b;
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Src, a);
		vssd_inode * disInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Des, b);
		if (!SrcInode)
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;  return;
		}
		if (!SrcInode)
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;  return;
		}
		if (SrcInode->IsFile())
		{ 
			vssdCopy vCopy;
			vCopy.vCopy(MyVssd, Src, Des);
			SrcInode->GetFather()->UnloadOneSub(SrcInode);
			return;
		}
		if (SrcInode && disInode && a.Inodes.size() >= 3 && b.Inodes.size() >= 2)
		{
			a.RealInodes.at(a.RealInodes.size() - 2)->UnloadOneSub(SrcInode);
			disInode->LoadOneSub(SrcInode);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}



	}
	int vssdMove::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vMove(MyVssd, Rear[1], Rear[2]);
		return EXE_OK;
	}

}