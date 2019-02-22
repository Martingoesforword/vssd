#include "pch.h"
#include "vssdCopy.h"
namespace sjh {
	void vssdCopy::vCopy(VirtualDisk & MyVssd, const std::wstring & rearSrc, const std::wstring & rearDes)
	{
		if (rearSrc.at(0) == L'@')
		{
			 
			vssd_inode *Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearDes);
			if (nullptr == Inode)
			{
				tools_path a(rearDes);
				if (a.IsAbsolutePath())
				{
					Inode = MyVssd.BuildPath(MyVssd,MyVssd.GetGenius(), a, vssd_inode::IS_FILE);
				}
				else
				{
					Inode = MyVssd.BuildPath(MyVssd,MyVssd.GetNooowPan()->GetNooowPos(), a, vssd_inode::IS_FILE);
				}
			}
			else {
				if (Inode->IsFile())
				{
					std::cout << "覆盖 " << tool::string::WStringToString(Inode->GetName()) << " 吗 ? (Yes / No / All) :";
					std::string Answer;
					while (1)
					{
						std::cin >> Answer;
						if (Answer.at(EXE_OK) == 'Y' || Answer.at(EXE_OK) == 'y')
						{
							break;
						}
						else if (Answer.at(EXE_OK) == 'N' || Answer.at(EXE_OK) == 'n')
						{
							return;
						}
						else if (Answer.at(EXE_OK) == 'A' || Answer.at(EXE_OK) == 'a')
						{
							break;
						}
					}

					//处理文件是否覆盖或是...但最终要产生Inode指针

				}
				else if (Inode->IsFolder()) {
					//处理文件夹      但最终要产生Inode指针
				}
				else if (Inode->IsLinkD()) {

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
		else if (rearDes.at(0) == L'@')
		{
			vssd_inode *Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearSrc);

			std::wstring RealDes = rearDes.substr(1, rearDes.size() - 1);
			std::ofstream DesFile(RealDes, std::ios::binary);
			if (DesFile.is_open())
			{
				std::wstring data;
				//tools_vssd::GetStringAnd0(Inode->Content, EXE_OK, Inode->Content.size(), data);

				DesFile.write((const char*)&data[0], data.size() * 2);
				DesFile.close();
			}
			else
			{
				std::cout << "Error opening file" << std::endl;
			} 
		}
		else
		{

			tools_path		a;
			tools_path		b;
			vssd_inode	* SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearSrc, a);
			vssd_inode	* disInode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearDes, b);
			if (SrcInode && disInode && a.Inodes.size() >= 2 && b.Inodes.size() >= 1)
			{
				vssd_inode	* inode = new vssd_inode(SrcInode->GetName(), vssd_inode::IS_FILE);
				inode->CopyFolder(MyVssd, SrcInode);
				disInode->LoadOneSub(inode); 

			}
			else
			{
				std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
			}
		}
		 
	}
	int vssdCopy::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vCopy(MyVssd, Rear[1], Rear[2]);
		return EXE_OK;
	}
}