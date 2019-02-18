#include "pch.h"
#include "vssdRen.h"
namespace sjh {
	 
	void vssdRen::vRen(VirtualDisk & MyVssd, std::wstring & SrcCommand, std::wstring & DesName)
	{
		tools_path a;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, SrcCommand, a);
		if (Inode && a.Inodes.size() > 2 && !(a.RealInodes.at(a.RealInodes.size() - 2)->FindSelfSubForNext(DesName, EXE_OK)))
		{
			Inode->Set(DesName);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}

	}

	int vssdRen::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		return EXE_OK;
	}
 
}