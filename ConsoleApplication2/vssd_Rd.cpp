#include "pch.h"
#include "vssdRd.h"
namespace sjh {
	//当下文件夹下rd

	void vssdRd::vRd(VirtualDisk & MyVssd, std::wstring & RdCommand)
	{

		tools_path a;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, RdCommand, a);
		if (!Inode)
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;  return;
		}
		if (Inode->IsFile())
		{
			std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
			vssdDel vDel;
			return;
		}
		if (Inode && a.Inodes.size() >= 3)
		{
			a.RealInodes.at(a.RealInodes.size() - 2)->DeleteOneSub(Inode);
		}



	}
	int vssdRd::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		return EXE_OK;
	}

}