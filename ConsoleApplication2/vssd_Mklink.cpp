#include "pch.h" 
void sjh::vssdMklink::vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	tool_path a;
	//找到需要指向的文件夹
	sjh::vssd_folder * Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

	if (Srcfolder && a.Folders.size() >= 3)
	{
		//找到之后
		if (vssdMd::vMd(MyVssd, LinkName))
		{
			return;
		}



		//创建Link文件
		sjh::vssd_folder *Link = MyVssd.GetNowTop()->GetNowPos()->FindForFirst(LinkName);

		Link->VssdTypeCode = 2;
		//找到创建的Link文件
		Link->VssdFolderLink(Srcfolder);
		//将Link文件第一个子文件放入指向文件
		Srcfolder->AddLink(Link);
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}
