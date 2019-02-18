#include "pch.h"  
#include "vssdCd.h"
namespace sjh {
	//当下文件夹下cd
	void vssdCd::vCd(VirtualDisk & MyVssd)
	{ 
		std::wcout << MyVssd.GetNooowPan()->GetNowPathWString() << "\n";
	}
	void vssdCd::vCd(VirtualDisk & MyVssd, const std::wstring & CdCommand)
	{ 
		 
		vssd_pan * Pan = MyVssd.GetNooowPan();
		if (0 == CdCommand.size()) { vCd(MyVssd); return; }
		else if (CdCommand.compare(L"/") == 0 || CdCommand.compare(L"\\") == 0)
		{
			while (Pan->GetNowPath().Inodes.size() > 2) Pan->DeleteOneSub();
			return;
		}

		tools_path a;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, CdCommand, a);

		if (Inode && Inode->IsFile())
		{
			std::cout << "VSSD ERROR : This Inode is not exist!" << std::endl;
			return;
		}

		if (Inode && ((!Inode->IsLink()) || (Inode->IsLink() && Inode->GetSubInodes()[EXE_OK])))
		{
			MyVssd.GetNooowPan()->SetNowPath(a);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}




	}

	int vssdCd::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{ 
		vCd(MyVssd, Rear[1]);
		return EXE_OK;
	}
	 
}