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
		tools_path a(MyVssd.GetNooowPan()->GetNowPath());
		a.DeleteOneSub();
		now->PrintAllSub(Type, a.GetPathWstring());

	}
	void vssdDir::vDir(VirtualDisk & MyVssd, std::vector<std::wstring> Dirs, int DirsPos, int Type)
	{
		// 切割/字符串（DirsPos）位置 
		for (size_t i = DirsPos; i < Dirs.size(); i++)
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
				a.DeleteOneSub();
				Inode->PrintAllSub(Type, a.GetPathWstring());
			}
			 
		}
	}
	void vssdDir::vDir(VirtualDisk & MyVssd, std::vector<std::wstring> Dirs)
	{
		
		if (!Dirs.size()) { vDir(MyVssd, DIR_TYPE_SELF); return; }
		//判断开关
		if (Dirs[0].at(EXE_OK) == '/' && Dirs[0].size() >= 2)
		{
			if (Dirs[0].size() == 2 && Dirs[EXE_OK].at(1) == 's' )
			{
				if (Dirs.size() == 1)
				{
					vDir(MyVssd, DIR_TYPE_TREE);
				}
				else
				{
					vDir(MyVssd, Dirs, 1, DIR_TYPE_TREE);
				}
				
			}
			else if (Dirs[0].size() == 3 && Dirs[EXE_OK].at(1) == 'a' && Dirs[EXE_OK].at(2) == 'd')
			{
				if (Dirs.size() == 1)
				{
					vDir(MyVssd, DIR_TYPE_SELF);
				}
				else
				{
					vDir(MyVssd, Dirs, 1, DIR_TYPE_SELF);
				} 
			}
			
		}
		else 
		{
			//无开关
		}

	}
	void vssdDir::Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear)
	{
		vDir(MyVssd, Rear);
		status = EXE_OK;
	}
}