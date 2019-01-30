#include "pch.h" 
void sjh::vssdDir::vDir(vssd_disk & MyVssd)
{
	sjh::vssd_folder *now = MyVssd.GetNooowPan()->GetNooowPos();

	while (now->IsLink())
	{
		if (now) now = now->GetSubFolders()[0];
		else
		{
			return;
		}
	}
	now->PrintAllSub(MyVssd,1, MyVssd.GetNooowPan()->GetNowPath().GetPathWstring());

}
void sjh::vssdDir::vDir(vssd_disk & MyVssd, std::wstring & DirCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::tools_vssd::Split(DirCommand, Dirs, L" ");
	if (!Dirs.size()) vDir(MyVssd);
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_folder * Folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
		if (!Folder)
		{
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl; continue;
		}
		if (Folder->IsFile())
		{
			std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
			return;
		}
		else
		{
			Folder->PrintAllSub(MyVssd,1, a.GetPathWstring());
		}


	}


}
