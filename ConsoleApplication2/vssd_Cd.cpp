#include "pch.h" 
//当下文件夹下cd
void sjh::vssdCd::vCd(sjh::vssd_disk & MyVssd)
{ 
	MyVssd.GetNowTop()->ShowNowPos();
}
void sjh::vssdCd::vCd(vssd_disk & MyVssd, std::wstring & CdCommand)
{
	if (!CdCommand.size()) { vCd(MyVssd); return; }
	tool_path a;
	sjh::vssd_folder * folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, CdCommand, a);
	if (folder) folder->BackCheck();
	if (folder && folder->isFile())
	{
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}

	if (folder && ((folder->VssdTypeCode != 2) || (folder->VssdTypeCode == 2 && folder->SubFolders[0])))
	{
		MyVssd.GetNowTop()->NowPath = a;
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}




}