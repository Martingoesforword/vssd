#include "pch.h" 
void sjh::tool_vcmd::vMove(vssd & MyVssd, std::wstring & Des) {

	tool_path b;
	sjh::vssd_folder * disfolder = v_FindPathForFirst(MyVssd, Des, b);
	if (disfolder) {
		disfolder->VssdFolderLink(MyVssd.GetNowTop()->GetNowPos());
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}
//�ƶ��ļ���
void sjh::tool_vcmd::vMove(vssd & MyVssd, std::wstring & Src, std::wstring & Des) {

	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = v_FindPathForFirst(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = v_FindPathForFirst(MyVssd, Des, b);
	if (!Srcfolder) { std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return; }
	if (!Srcfolder) { std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return; }
	if (Srcfolder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vCopy(MyVssd, Src, Des);
		return;
	}
	if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2) {
		a.RealFolders.at(a.RealFolders.size() - 2)->OffOne(Srcfolder);
		disfolder->VssdFolderLink(Srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}



}
