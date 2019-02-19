#include "pch.h"
#include "vssdCopy.h"
namespace sjh {
	void vssdCopy::vCopy(VirtualDisk & MyVssd, std::wstring & rearSrc, std::wstring & rearDes)
	{
		if (rearSrc.at(EXE_OK) == L'@')
		{

			tools_path a;
			vssd_inode *Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearDes, a);
			if (nullptr == Inode)
			{
				a.SetInodesByWstring(rearDes);
				if (a.IsAbsolutePath())
				{
					Inode = MyVssd.BuildPath(MyVssd.GetGenius(), a, vssd_inode::IS_FILE);
				}
				else
				{
					Inode = MyVssd.BuildPath(MyVssd.GetNooowPan()->GetNooowPos(), a, vssd_inode::IS_FILE);
				}
			}
			else {
				if (Inode->IsFile())
				{
					std::cout << "���� " << tool::string::WStringToString(Inode->Get()) << " �� ? (Yes / No / All) :";
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

					//�����ļ��Ƿ񸲸ǻ���...������Ҫ����Inodeָ��

				}
				else if (Inode->IsFolder()) {
					//�����ļ���      ������Ҫ����Inodeָ��
				}
				else if (Inode->IsLink()) {

				}
			}

			std::wstring RealSrc = rearSrc.substr(1, rearSrc.length() - 1);

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
			//��������vector<std::wstring>
			//�õ��ļ���
			//�ж��ļ�����

			//����Ŀ�������ļ�rearSrc1
			//����vssdCopy::vCopy(MyVssd, rearSrc1, reardis);

		}
		else if (rearDes.at(EXE_OK) == L'@')
		{
			tools_path a;
			vssd_inode *Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearSrc, a);

			std::wstring RealDes = rearDes.substr(1, rearDes.length() - 1);
			std::ofstream DesFile(RealDes, std::ios::binary);
			if (DesFile.is_open())
			{
				std::wstring data;
				//tools_vssd::GetStringAnd0(Inode->Content, EXE_OK, Inode->Content.size(), data);

				DesFile.write((const char*)&data[EXE_OK], data.size() * 2);
				DesFile.close();
			}
			else
			{
				std::cout << "Error opening file" << std::endl;
			}

			//�õ��ļ���
			//�����ļ�ָ�룬
			//��content���Բ�д���ļ��� 
		}
		else
		{

			tools_path		a;
			tools_path		b;
			vssd_inode	* SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearSrc, a);
			vssd_inode	* disInode = vssd_optcmd::v_FindPathForFirst(MyVssd, rearDes, b);
			if (SrcInode && disInode && a.Inodes.size() >= 3 && b.Inodes.size() >= 2)
			{
				a.RealInodes.at(a.RealInodes.size() - 2)->UnloadOneSub(SrcInode);
				disInode->LoadOneSub(SrcInode);
			}
			else
			{
				std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
			}
		}




	}
	int vssdCopy::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		return EXE_OK;
	}
}