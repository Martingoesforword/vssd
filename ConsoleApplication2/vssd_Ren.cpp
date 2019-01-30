#include "pch.h" 
 
void sjh::vssdRen::vRen(vssd_disk & MyVssd, std::wstring & SrcCommand, std::wstring & DesName)
{
	tool_path a;
	sjh::vssd_Inode * Inode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, SrcCommand, a);
	if (Inode && a.Inodes.size() > 2 && !(a.RealInodes.at(a.RealInodes.size() - 2)->FindSelfSubForFirst(DesName, 0)))
	{
		Inode->SetName(DesName);
	}
	else
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}

}

