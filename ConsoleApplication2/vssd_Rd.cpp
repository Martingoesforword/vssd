#include "pch.h"
#include "vssdRd.h"
namespace sjh { 
	void vssdRd::vRd(VirtualDisk & MyVssd, const std::vector<std::wstring>& Dels, int PosDel, int DEL_TYPE)
	{
		for (int ii = PosDel; ii < Dels.size(); ii++) {
			tools_path a;
			std::vector< vssd_inode *> Sets;
			vssd_optcmd::v_FindPathForAll(MyVssd, Dels[ii], Sets);
			if (Sets.size())
			{
				for (size_t i = 0; i < Sets.size() ; i++)
				{
					if (Sets[i]->IsFolder() || Sets[i]->IsLinkD()) {
						if (DEL_TYPE == DEL_TYPE_TREE) {
							Sets[i]->GetFather()->DeleteOneSub(Sets[i]);
						}
						else if (DEL_TYPE == DEL_TYPE_SELF)
						{
							if (Sets[i]->SubSize() == 0)
							{
								Sets[i]->GetFather()->DeleteOneSub(Sets[i]);
							}
							else
							{
								if (Sets[i]->IsLinkD())
								{
									Sets[i]->UnloadOneSub(Sets[i]->GetSubInodes()[0]);
									Sets[i]->GetFather()->DeleteOneLink(Sets[i]);
								}
								//Ê§°Ü
							}

						}
					}
				}
			}
			else
			{
				std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
			}
		}

	}
	void vssdRd::vRd(VirtualDisk & MyVssd, const std::vector<std::wstring>& Dels)
	{

		using namespace tool::string;
		if (HasSwitch(Dels[1]) && IsThisSwitch(Dels[1], L"s"))
		{
			vRd(MyVssd, Dels, 2, DEL_TYPE_TREE);
		}
		else
		{
			vRd(MyVssd, Dels, 1, DEL_TYPE_SELF);
		}

	}
	int vssdRd::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vRd(MyVssd, Rear);
		return EXE_OK;
	} 

}