#include "pch.h"
void sjh::vssdCopy::vCopy(vssd_disk & MyVssd, std::wstring & rearSrc, std::wstring & rearDes)
{
	if (rearSrc.at(0) == L'@')
	{

		sjh::tool_path a;
		sjh::vssd_folder *folder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, a);
		if (!folder)
		{
			a.PathToFolders(rearDes);
			a.DeleteOne();
			if (a.Folders[0].size() > 1 && a.Folders[0].at(1) != L':')
			{
				MyVssd.GetNooowPan()->GetNooowPos()->Build(MyVssd, a);
			}
			else
			{
				MyVssd.GetGenius()->Build(MyVssd, a);
			} 
			folder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, a); 

			sjh::vssd_folder *newFile = new sjh::vssd_folder(L"", vssd_folder::IS_FILE);
			folder->LinkNewFolder(newFile);
			folder = newFile;
		}
		else {
			if (folder->GetTypeCode() == sjh::vssd_folder::IS_FILE) {
				//处理文件是否覆盖或是...但最终要产生folder指针
			}
			else if (folder->GetTypeCode() == sjh::vssd_folder::IS_FOLDER) {
				//处理文件夹      但最终要产生folder指针
			}
			else if (folder->GetTypeCode() == sjh::vssd_folder::IS_LINK) {

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
			folder->Content.push_back(ch); 
		}
		RealFile.close();
		//读并放入vector<std::wstring>
		//得到文件名
		//判断文件类型

		//建立目的虚拟文件rearSrc1
		//调用sjh::vssdCopy::vCopy(MyVssd, rearSrc1, reardis);

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

		//得到文件名
		//建立文件指针，
		//读content属性并写入文件中 
	}
	else
	{
		 
		tool_path		a;
		tool_path		b;
		sjh::vssd_folder	* Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearSrc, a);
		sjh::vssd_folder	* disfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, rearDes, b);
		if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2)
		{
			a.RealFolders.at(a.RealFolders.size() - 2)->OffOne(Srcfolder);
			disfolder->LinkNewFolder(Srcfolder);
		}
		else
		{
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
		}
	}



	
}