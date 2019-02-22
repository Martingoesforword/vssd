#include "pch.h"
#include "vssdCopy.h"
namespace sjh {
	void vssdCopy::vCopy(VirtualDisk & MyVssd, const std::wstring & rearSrc, const std::wstring & rearDes)
	{ 
		if (rearSrc.at(0) == L'@')
		{ 
			std::vector<vssd_inode *> Inodes;
			vssd_optcmd::v_FindPathForAll(MyVssd, rearDes, Inodes);
			for (size_t i = 0; i < Inodes.size(); i++)
			{
				vssd_inode * Inode = Inodes[i];
				if (nullptr == Inode)
				{
					tools_path a(rearDes);
					if (a.IsAbsolutePath())
					{
						Inode = MyVssd.BuildPath(MyVssd, MyVssd.GetGenius(), a, vssd_inode::IS_FILE);
					}
					else
					{
						Inode = MyVssd.BuildPath(MyVssd, MyVssd.GetNooowPan()->GetNooowPos(), a, vssd_inode::IS_FILE);
					}
				}
				else {

					if (Inode->IsLinkF() || Inode->IsFile())
					{
						std::cout << "覆盖 " << tool::string::WStringToString(Inode->GetName()) << " 吗 ? (Yes / No / All) :";
						std::string Answer;
						while (1)
						{
							std::cin >> Answer;
							if (Answer.at(0) == 'Y' || Answer.at(0) == 'y')
							{
								break;
							}
							else if (Answer.at(0) == 'N' || Answer.at(0) == 'n')
							{
								return;
							}
							else if (Answer.at(0) == 'A' || Answer.at(0) == 'a')
							{
								break;
							}
						} 
					}
					else if (Inode->IsLinkD() || Inode->IsFolder()) {
						vssd_inode *Inodea = new vssd_inode(Inode->GetName(), Inode->IS_FOLDER);

					}

				}
				std::wstring RealSrc = rearSrc.substr(1, rearSrc.size() - 1);

				char ch;

				std::ifstream RealFile(RealSrc, std::ios::binary);

				if (!RealFile.is_open())
				{
					std::cout << "Error opening file"; exit(1);
				}

				while (!RealFile.eof())
				{
					ch = ' ';
					RealFile.read(&ch, 1);
					Inode->AddContent(ch);
				}
				RealFile.close();
				//读并放入vector<std::wstring>
				//得到文件名
				//判断文件类型

				//建立目的虚拟文件rearSrc1
				//调用vssdCopy::vCopy(MyVssd, rearSrc1, reardis);
			} 

		}
		else if (rearDes.at(0) == L'@')
		{  
			std::vector<vssd_inode *> Inodes;
			vssd_optcmd::v_FindPathForAll(MyVssd, rearSrc, Inodes);
			for (size_t i = 0; i < Inodes.size(); i++)
			{
				vssd_inode * Inode = Inodes[i];
				std::wstring RealDes = rearDes.substr(1, rearDes.size() - 1);
				std::ofstream DesFile(RealDes, std::ios::binary);
				if (DesFile.is_open())
				{
					std::wstring data; 
					tool::string::GetWString(Inode->GetContent(), data);
					DesFile.write((const char*)&data[0], data.size() * 2);
					DesFile.close();
				}
				else
				{
					std::cout << "Error opening file" << std::endl;
				} 
			}
			
		}
		else
		{
			vssd_inode	* disInode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearDes);
			
			std::vector<vssd_inode *> Inodes;
			vssd_optcmd::v_FindPathForAll(MyVssd, rearSrc, Inodes);
			for (size_t i = 0; i < Inodes.size(); i++)
			{
				/*
				if (disInode && disInode->IsFolder()) {

				}

				if (SrcInode && disInode && a.Inodes.size() >= 3 && b.Inodes.size() >= 2)
				{
					a.RealInodes.at(a.RealInodes.size() - 2)->UnloadOneSub(SrcInode);
					disInode->LoadOneSub(SrcInode);
				}
				else
				{
					std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
				}
				*/
			}
			
		}




	}
	int vssdCopy::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		if (Rear.size() > 2) vCopy(MyVssd, Rear[1], Rear[2]);
		return EXE_OK;
	}
}