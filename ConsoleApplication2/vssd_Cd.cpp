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
		
		if ((CdCommand == (L"/"))  || (CdCommand == (L"\\")))
		{
			while (! Pan->GetNowPath().IsAbsAndRoot()) Pan->DeleteOneSub();
			return;
		}

		tools_path a;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, CdCommand,a);
		if (Inode) 
		{
			if (Inode->IsFile())
			{
				std::cout << "VSSD ERROR : This Inode is not exist!" << std::endl;
				return;
			} 
			else if (Inode->IsFolder())
			{
				MyVssd.GetNooowPan()->SetNowPath(a);
			}
			else if (Inode->IsLinkD())
			{
				vssd_inode * aInode = vssd_optcmd::CheckLink(MyVssd, Inode);
				if (aInode != nullptr)
				{
					MyVssd.GetNooowPan()->GetNowPath().LoadOneSub(aInode);
					MyVssd.GetNooowPan()->GetNowPath().Inodes[MyVssd.GetNooowPan()->GetNowPath().Inodes.size() - 1] = Inode->GetName();
				}
				else 
				{
					std::cout << "VSSD ERROR : The Folder for this Link is not exist!" << std::endl;
				}
			}
			else if (Inode->IsLinkF())
			{
				std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
			}
			
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}




	}

	int vssdCd::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		//Rear长度 == 1 OR > 1
		if (1 == Rear.size())
		{
			vCd(MyVssd); 
			return EXE_OK;
		}
		else
		{
			vCd(MyVssd, Rear[1]);
			return EXE_OK;
		}
		
	}
	 
}