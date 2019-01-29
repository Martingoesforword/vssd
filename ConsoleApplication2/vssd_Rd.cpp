#include "pch.h" 
//当下文件夹下rd
 
void sjh::vssdRd::vRd(vssd_disk & MyVssd, std::wstring & RdCommand)
{

	tool_path a;
	sjh::vssd_folder * folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, RdCommand, a);
	if (!folder)
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return;
	} 
	if (folder->IsFile())
	{
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vssdDel::vDel(MyVssd, RdCommand);
		return;
	}
	if (folder && a.Folders.size() >= 3)
	{
		a.RealFolders.at(a.RealFolders.size() - 2)->DeleteOneSub(folder);
	}



}
