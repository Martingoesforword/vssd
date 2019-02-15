#include "pch.h"
#include "vssdMove.h"
namespace sjh {
	void vssdMove::vMove(VirtualDisk & MyVssd, std::wstring & Des)
	{

		tools_path b;
		vssd_inode * disInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Des, b);
		if (disInode)
		{
			disInode->LoadOneSub(MyVssd.GetNooowPan()->GetNooowPos());
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}

	}
	//ÒÆ¶¯ÎÄ¼þ¼Ð
	void vssdMove::vMove(VirtualDisk & MyVssd, std::wstring & Src, std::wstring & Des)
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
			std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
			vssdCopy vCopy;
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
	void vssdMove::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}

}