#include "vssdCd.h"
namespace sjh {
	//当下文件夹下cd
	void vssdCd::vCd(vssd_manager & MyVssd)
	{
		MyVssd.GetNooowPan()->PrintNowPath();
		std::wcout << "\n";
	}
	void vssdCd::vCd(vssd_manager & MyVssd, std::wstring & CdCommand)
	{
		if (!CdCommand.size()) { vCd(MyVssd); return; }
		tools_path a;
		vssd_inode * Inode = vssd_vcmd::v_FindPathForFirst(MyVssd, CdCommand, a);

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

	int vssdCd::Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear)
	{
		return EXE_OK;
	}
	 
}