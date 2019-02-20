#include "pch.h"
#include "vssdDel.h"
namespace sjh {
	void vssdDel::vDel(VirtualDisk & MyVssd, const std::wstring & DelCommand)
	{ 
		tools_path a;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, DelCommand, a);
		if (Inode && a.Inodes.size() >= 2)
		{
			Inode->GetFather()->DeleteOneSub(Inode);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}
	}
	int vssdDel::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		for (size_t i = 1; i < Rear.size(); i++)
		{
			vDel(MyVssd, Rear[i]);
		}
		return EXE_OK;
	}
}