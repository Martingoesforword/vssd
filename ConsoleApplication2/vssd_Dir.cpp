#include "pch.h" 
void sjh::vssdDir::vDir(vssd_disk & MyVssd, int Type)
{
	sjh::vssd_Inode *now = MyVssd.GetNooowPan()->GetNooowPos();

	while (now->IsLink())
	{
		if (now) now = now->GetSubInodes()[0];
		else
		{
			return;
		}
	}
	now->PrintAllSub(MyVssd, Type, MyVssd.GetNooowPan()->GetNowPath().GetPathWstring());

}
void sjh::vssdDir::vDir(vssd_disk & MyVssd, std::vector<std::wstring> Dirs, int Type)
{
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_Inode * Inode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
		if (!Inode)
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl; continue;
		}
		if (Inode->IsFile())
		{
			std::cout << "VSSD ERROR : This Inode is not exist!" << std::endl;
			return;
		}
		else
		{
			Inode->PrintAllSub(MyVssd, Type, a.GetPathWstring());
		}


	}
}
void sjh::vssdDir::vDir(vssd_disk & MyVssd, std::wstring & DirCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::tools_vssd::Split(DirCommand, Dirs, L" "); 
	if (!Dirs.size()) { vDir(MyVssd, 2); return; }
	
	//ÅÐ¶Ï¿ª¹Ø
	if(Dirs[0].at(0) == '/' && Dirs[0].size() >= 2)
	{
		if (Dirs[0].at(1) == 'a')
		{
			vDir(MyVssd, 2);
		}
		else if(Dirs[0].at(1) == 's')
		{
			vDir(MyVssd, 1);
		}
	} 

}
