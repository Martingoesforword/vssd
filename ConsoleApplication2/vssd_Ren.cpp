#include "pch.h" 
 
void sjh::vssdRen::vRen(vssd_disk & MyVssd, std::wstring & SrcCommand, std::wstring & DesName)
{
	tool_path a;
	sjh::vssd_folder * folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, SrcCommand, a);
	if (folder && a.Folders.size() > 2 && !(a.RealFolders.at(a.RealFolders.size() - 2)->FindForFirst(DesName)))
	{
		folder->SetName(DesName);
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

