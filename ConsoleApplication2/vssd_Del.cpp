#include "pch.h"
#include "vssdDel.h"
namespace sjh {
	void vssdDel::vDel(VirtualDisk & MyVssd, std::wstring & DelCommand)
	{
		std::vector<std::wstring> Dirs;
		tool::stringtools::Split(DelCommand, Dirs, L" ");
		for (size_t i = EXE_OK; i < Dirs.size(); i++)
		{
			tools_path a;
			vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
			if (Inode && a.Inodes.size() >= 3)
			{
				a.RealInodes.at(a.RealInodes.size() - 2)->DeleteOneSub(Inode);
			}
			else
			{
				std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
			}
		}
	}
	int vssdDel::Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear)
	{
		return EXE_OK;
	}
}