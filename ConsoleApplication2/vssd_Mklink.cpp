#include "pch.h" 
void sjh::vssdMklink::vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	tool_path a;
	//找到需要指向的文件夹
	sjh::vssd_folder * Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

	if (Srcfolder && a.Folders.size() >= 3)
	{
		//找到之后
		int posq = LinkName.find_last_of(L"\\");
		int posp = LinkName.find_last_of(L"/");
		posp = posp > posq ? posp : posq;
		std::wstring FolderOfLinkPath = LinkName.substr(0, posp-0);
		sjh::vssd_folder *FolderOfLink = vssdMd::vMd(MyVssd, FolderOfLinkPath);
		
		//创建Link文件
		sjh::vssd_folder *Link = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_LINK); 
		FolderOfLink->LinkNewFolder(Link); 
		//找到创建的Link文件
		Link->LinkNewFolder(Srcfolder);
		//将Link文件第一个子文件放入指向文件
		Srcfolder->AddLink(Link);
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}
