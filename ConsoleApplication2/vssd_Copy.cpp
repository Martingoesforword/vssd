#include "pch.h"
void sjh::vssdCopy::vCopy(vssd_disk & MyVssd, std::wstring & rearSrc, std::wstring & rearDes)
{
	if (rearSrc.at(0) == L'@')
	{

		sjh::tool_path a;
		sjh::vssd_folder *folder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, a);
		if (nullptr == folder)
		{
			a.SetFoldersByWstring(rearDes); 
			if (a.IsAbsolutePath())
			{
				folder = MyVssd.GetNooowPan()->GetNooowPos()->BuildPath(MyVssd, a, vssd_folder::IS_FILE);
			}
			else
			{
				folder = MyVssd.GetGenius()->BuildPath(MyVssd, a, vssd_folder::IS_FILE);
			}    
		}
		else {
			if (folder->IsFile()) {
				//�����ļ��Ƿ񸲸ǻ���...������Ҫ����folderָ��
			}
			else if (folder->IsFolder()) {
				//�����ļ���      ������Ҫ����folderָ��
			}
			else if (folder->IsLink()) {

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
			folder->GetContent().push_back(ch);
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
		sjh::vssd_folder *folder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearSrc, a);

		std::wstring RealDes = rearDes.substr(1, rearDes.length() - 1);
		std::ofstream DesFile(RealDes, std::ios::binary);
		if (DesFile.is_open())
		{
			std::wstring data;
			//tools_vssd::GetStringAnd0(folder->Content, 0, folder->Content.size(), data);

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
		sjh::vssd_folder	* Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearSrc, a);
		sjh::vssd_folder	* disfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, b);
		if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2)
		{
			a.RealFolders.at(a.RealFolders.size() - 2)->UnloadOneSub(Srcfolder);
			disfolder->AddOneSub(Srcfolder);
		}
		else
		{
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
		}
	}



	
}