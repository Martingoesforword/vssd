#include "pch.h"
#include "vssdDel.h"
namespace sjh {
	void vssdDel::vDel(VirtualDisk & MyVssd, const std::vector<std::wstring>& Dels, int PosDel, int DEL_TYPE)
	{
		if (DEL_TYPE == 1)
		{
			for (int ii = PosDel; ii < Dels.size(); ii++) {
				tools_path a;
				std::vector< vssd_inode *> Sets;
				vssd_optcmd::v_FindPathForAll(MyVssd, Dels[ii], Sets);
				if (Sets.size())
				{
					for (size_t i = 0; i < Sets.size(); i++)
					{
						if (Sets[i]->IsFile())
						{
							Sets[i]->GetFather()->DeleteOneSub(Sets[i]);
						}
					}
				}
				else
				{
					std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
				}
			}
		}
		else if(DEL_TYPE == 2)
		{
			for (int ii = PosDel; ii < Dels.size(); ii++) {
				tools_path a;
				std::vector< vssd_inode *> Sets;
				vssd_optcmd::v_FindPathForAll(MyVssd, Dels[ii], Sets);
				if (Sets.size())
				{
					for (size_t i = 0; i < Sets.size(); i++)
					{
						if (Sets[i]->IsFile())
						{
							Sets[i]->GetFather()->DeleteOneSub(Sets[i]);
						}
						else if(Sets[i]->IsFolder())
						{ 
							Sets[i]DeleteAllFile
						}
						
					}
				}
				else
				{
					std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
				}
			}
		}
		

	}
	void vssdDel::vDel(VirtualDisk & MyVssd, const std::vector<std::wstring>& Dels)
	{

		using namespace tool::string;
		if (HasSwitch(Dels[1]) && IsThisSwitch(Dels[1], L"s"))
		{
			vDel(MyVssd, Dels, 2, DEL_TYPE_TREE);
		}
		else
		{
			vDel(MyVssd, Dels, 1, DEL_TYPE_SELF);
		}

	}
	int vssdDel::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vDel(MyVssd, Rear);
		return EXE_OK;
	}
}