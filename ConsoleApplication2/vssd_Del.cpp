#include "pch.h" 
void sjh::vssdDel::vDel(vssd_disk & MyVssd, std::wstring & DelCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::tools_vssd::Split(DelCommand, Dirs, L" ");
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_Inode * Inode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
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
