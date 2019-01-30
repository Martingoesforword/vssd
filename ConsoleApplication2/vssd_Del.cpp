#include "pch.h" 
void sjh::vssdDel::vDel(vssd_disk & MyVssd, std::wstring & DelCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::tools_vssd::Split(DelCommand, Dirs, L" ");
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_folder * folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
		if (folder && a.Folders.size() >= 3)
		{
			a.RealFolders.at(a.RealFolders.size() - 2)->DeleteOneSub(folder);
		}
		else
		{
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
		}
	}
}
