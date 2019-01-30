#include "pch.h"
void sjh::vssdCopy::vCopy(vssd_disk & MyVssd, std::wstring & rearSrc, std::wstring & rearDes)
{
	if (rearSrc.at(0) == L'@')
	{

		sjh::tool_path a;
		sjh::vssd_Inode *Inode = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, a);
		if (nullptr == Inode)
		{
			a.SetInodesByWstring(rearDes); 
			if (a.IsAbsolutePath())
			{
				Inode = MyVssd.BuildPath(MyVssd.GetGenius(),a, vssd_Inode::IS_FILE);
			}
			else
			{
				Inode = MyVssd.BuildPath(MyVssd.GetNooowPan()->GetNooowPos(), a, vssd_Inode::IS_FILE);
			}    
		}
		else {
			if (Inode->IsFile()) 
			{
				std::cout << "���� "<<tools_vssd::WStringToString( Inode->GetName())<<" �� ? (Yes / No / All) :";
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
			Inode->GetContent().push_back(ch);
		}
		RealFile.close();
		//��������vector<std::wstring>
		//�õ��ļ���
		//�ж��ļ�����

		//����Ŀ�������ļ�rearSrc1
		//����sjh::vssdCopy::vCopy(MyVssd, rearSrc1, reardis);

	}
	else if (rearDes.at(0) == L'@')
	{
		sjh::tool_path a;
		sjh::vssd_Inode *Inode = vssd_vcmd::v_FindPathForFirst(MyVssd, rearSrc, a);

		std::wstring RealDes = rearDes.substr(1, rearDes.length() - 1);
		std::ofstream DesFile(RealDes, std::ios::binary);
		if (DesFile.is_open())
		{
			std::wstring data;
			//tools_vssd::GetStringAnd0(Inode->Content, 0, Inode->Content.size(), data);

			DesFile.write((const char*)&data[0], data.size() * 2);
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
		 
		tool_path		a;
		tool_path		b;
		sjh::vssd_Inode	* SrcInode = vssd_vcmd::v_FindPathForFirst(MyVssd, rearSrc, a);
		sjh::vssd_Inode	* disInode = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, b);
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