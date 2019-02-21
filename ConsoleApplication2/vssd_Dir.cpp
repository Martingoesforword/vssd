#include "pch.h"
#include "vssdDir.h"
namespace sjh {
	void vssdDir::vDir(const VirtualDisk & MyVssd, int Type)
	{
		const vssd_inode *now = MyVssd.GetNooowPan()->GetNooowPos();  
		now->PrintAllSub(Type, MyVssd.GetNooowPan()->GetNowPath().GetPathWstring()); 
	}
	void vssdDir::vDir(const VirtualDisk & MyVssd, std::vector<std::wstring> Dirs, int DirsPos, int Type)
	{
		// �и�/�ַ�����DirsPos��λ�� 
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
				Inode->PrintAllSub(Type, a.GetPathWstring());
			}
			 
		}
	}
	void vssdDir::vDirSwitch(const VirtualDisk & MyVssd, std::vector<std::wstring> Dirs)
	{
		
		if (Dirs.size() == 1) { vDir(MyVssd, DIR_TYPE_SELF); return; }
		//�жϿ���
		using namespace tool::string;
		if (HasSwitch(Dirs[1]))
		{
			if (IsThisSwitch(Dirs[1],L"s"))
			{
				if (Dirs.size() == 2)
				{
					vDir(MyVssd, DIR_TYPE_TREE);
				}
				else
				{
					vDir(MyVssd, Dirs, 2, DIR_TYPE_TREE);
				}	
			}
			else if (IsThisSwitch(Dirs[1], L"ad"))
			{
				if (Dirs.size() == 2)
				{
					vDir(MyVssd, DIR_TYPE_SELF);
				}
				else
				{
					vDir(MyVssd, Dirs, 2, DIR_TYPE_SELF);
				} 
			}
			
		}
		else 
		{
			//�޿���
		}

	}
	int vssdDir::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vDirSwitch(MyVssd, Rear);
		return EXE_OK;
	}
}