#include "pch.h" 
//当下文件夹下cd
void sjh::tool_vcmd::vCd(sjh::vssd_foldertop * MyTop)
{

	MyTop->ShowNowPos();
}
void sjh::tool_vcmd::vCd(vssd & MyVssd, std::wstring & CdCommand)
{
	tool_path a;
	sjh::vssd_folder * folder = v_FindPathForFirst(MyVssd, CdCommand, a);
	if (folder) folder->BackCheck();
	if (folder && folder->isFile()) {
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}

	if (folder && ((folder->VssdTypeCode != 2) || (folder->VssdTypeCode == 2 && folder->SubFolders[0]))) {
		MyVssd.GetNowTop()->NowPath = a;
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}




}