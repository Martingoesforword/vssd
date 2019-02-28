#include "pch.h"
#include "vssdRen.h"
namespace sjh {
	 
	void vssdRen::vRen(VirtualDisk & MyVssd, const std::wstring  SrcCommand,const std::wstring  DesName)
	{
		tools_path a;
		std::wstring  sCommand(SrcCommand);
		std::wstring  dCommand(DesName);
		std::vector<vssd_inode *> sets;
		vssd_optcmd::v_FindPathForAll(MyVssd, sCommand, sets);
		for (size_t i = 0; i < sets.size(); i++)
		{
			if (sets[i]->GetFather()->FindSelfSubForNext(dCommand, 0) == vssd_inode::NOT_FINDED)
			{
				tool::string::CheckQuotation(dCommand);
				sets[i]->SetName(dCommand);
			}
			else
			{
				std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
			}
		} 
		if (sets.size() == 0)
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}
	}

	int vssdRen::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vRen(MyVssd, Rear[1], Rear[2]);
		return EXE_OK;
	}
 
}