#include "pch.h"  
#include "vssdCd.h"
namespace sjh {
	//当下文件夹下cd
	void vssdCd::vCd(VirtualDisk & MyVssd)
	{ 
		std::wcout << MyVssd.GetNooowPan()->GetNowPathWString() << "\n";
	}
	void vssdCd::vCd(VirtualDisk & MyVssd, std::wstring & CdCommand)
	{
		if (!CdCommand.size()) { vCd(MyVssd); return; }
		tools_path a;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, CdCommand, a);

		if (Inode && Inode->IsFile())
		{
			std::cout << "VSSD ERROR : This Inode is not exist!" << std::endl;
			return;
		}

		if (Inode && ((!Inode->IsLink()) || (Inode->IsLink() && Inode->GetSubInodes()[EXE_OK])))
		{
			MyVssd.GetNooowPan()->GetNowPath() = a;
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}




	}

	void vssdCd::Execute(VirtualDisk & MyVssd, std::vector<std::wstring> Rear)
	{
		status = EXE_OK;
	}
	 
}