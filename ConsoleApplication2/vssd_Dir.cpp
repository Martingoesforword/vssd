#include "pch.h" 
void sjh::vssdDir::vDir(sjh::vssd_pan * Top)
{
	sjh::vssd_folder *now = Top->GetNowPos();

	while (now->VssdTypeCode == 2) {
		if (now) now = now->SubFolders[0];
		else {
			return;
		}
	}
	now->ShowOffSub(1, Top->NowPath.FoldersToPath());

}
void sjh::vssdDir::vDir(vssd_disk & MyVssd, std::wstring & DirCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::tools_vssd::split(DirCommand, Dirs, L" ");
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_folder * Folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
		if (!Folder) {
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl; continue;
		}
		if (Folder->isFile()) {
			std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
			return;
		}
		else {
			Folder->ShowOffSub(0, a.FoldersToPath());
		}


	}


}
