#include "pch.h" 
void sjh::tool_vcmd::vDel(vssd & MyVssd, std::wstring & DelCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::vssd_tool::split(DelCommand, Dirs, L" ");
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_folder * folder = v_FindPathForFirst(MyVssd, Dirs[i], a);
		if (folder && a.Folders.size() >= 3) {
			a.RealFolders.at(a.RealFolders.size() - 2)->DeletOne(folder);
		}
		else {
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
		}
	}
}
