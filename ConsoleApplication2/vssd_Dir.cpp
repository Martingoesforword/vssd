#include "pch.h"
#include "vssdDir.h"
namespace sjh {
	void vssdDir::vDir(VirtualDisk & MyVssd, int Type)
	{
		vssd_inode *now = MyVssd.GetNooowPan()->GetNooowPos();

		while (now->IsLink())
		{
			if (now) now = now->GetSubInodes()[EXE_OK];
			else
			{
				return;
			}
		}

		now->PrintAllSub(Type, MyVssd.GetNooowPan()->GetNowPath().GetPathWstring());

	}
	void vssdDir::vDir(VirtualDisk & MyVssd, std::vector<std::wstring> Dirs, int Type)
	{
		for (size_t i = EXE_OK; i < Dirs.size(); i++)
		{
			tools_path a;
			vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, Dirs[i], a);
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

				Inode->PrintAllSub(Type, a.GetPathWstring());
			}


		}
	}
	void vssdDir::vDir(VirtualDisk & MyVssd, std::vector<std::wstring> Dirs)
	{
		
		if (!Dirs.size()) { vDir(MyVssd, 2); return; } 
		//ÅÐ¶Ï¿ª¹Ø
		if (Dirs[EXE_OK].at(EXE_OK) == '/' && Dirs[EXE_OK].size() >= 2)
		{
			if (Dirs[EXE_OK].at(1) == 'a')
			{
				vDir(MyVssd, 2);
			}
			else if (Dirs[EXE_OK].at(1) == 's')
			{
				vDir(MyVssd, 1);
			}
		}

	}
	int vssdDir::Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear)
	{
		vDir(MyVssd, Rear);
		return EXE_OK;
	}
}