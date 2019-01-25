#include "pch.h" 
void sjh::vssdCopy::vCopy(vssd_disk & MyVssd, std::wstring & Src, std::wstring & Des)
{
	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = vssd_vcmd::vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, Des, b);
	if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2) {
		a.RealFolders.at(a.RealFolders.size() - 2)->OffOne(Srcfolder);
		disfolder->VssdFolderLink(Srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}
