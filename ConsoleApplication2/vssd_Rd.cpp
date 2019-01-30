#include "pch.h" 
//当下文件夹下rd
 
void sjh::vssdRd::vRd(vssd_disk & MyVssd, std::wstring & RdCommand)
{

	tool_path a;
	sjh::vssd_Inode * Inode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, RdCommand, a);
	if (!Inode)
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;  return;
	} 
	if (Inode->IsFile())
	{
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vssdDel::vDel(MyVssd, RdCommand);
		return;
	}
	if (Inode && a.Inodes.size() >= 3)
	{
		a.RealInodes.at(a.RealInodes.size() - 2)->DeleteOneSub(Inode);
	}



}
