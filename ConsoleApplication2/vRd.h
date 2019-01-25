#include "pch.h" 
//当下文件夹下rd
void sjh::tool_vcmd::vRd(vssd_disk & MyVssd) {
	if (MyVssd.GetNowTop()->NowPath.RealFolders.size() >= 3) {
		MyVssd.GetNowTop()->GetNowPos()->DeleteLinks();
		MyVssd.GetNowTop()->NowPath.RealFolders.at(MyVssd.GetNowTop()->NowPath.RealFolders.size() - 2)->DeletOne(MyVssd.GetNowTop()->GetNowPos());

		MyVssd.GetNowTop()->NowPath.DeletOne();
		std::cout << "VSSD ERROR : NowPos folder is deleted just！" << std::endl;
	}
	else {
		std::cout << "VSSD ERROR : Root folder cannot be deleted！" << std::endl;
	}


}

void sjh::tool_vcmd::vRd(vssd_disk & MyVssd, std::wstring & RdCommand)
{

	tool_path a;
	sjh::vssd_folder * folder = v_FindPathForFirst(MyVssd, RdCommand, a);
	if (!folder) { std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return; }
	folder->DeleteLinks();
	if (folder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vDel(MyVssd, RdCommand);
		return;
	}
	if (folder && a.Folders.size() >= 3) {
		a.RealFolders.at(a.RealFolders.size() - 2)->DeletOne(folder);
	}



}
