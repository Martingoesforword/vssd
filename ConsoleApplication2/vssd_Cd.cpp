#include "pch.h" 
//当下文件夹下cd
void sjh::vssdCd::vCd(sjh::vssd_disk & MyVssd)
{ 
	MyVssd.GetNooowPan()->PrintNowPath();
	std::wcout << "\n";
}
void sjh::vssdCd::vCd(vssd_disk & MyVssd, std::wstring & CdCommand)
{
	if (!CdCommand.size()) { vCd(MyVssd); return; }
	tool_path a;
	sjh::vssd_Inode * Inode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, CdCommand, a);
	 
	if (Inode && Inode->IsFile())
	{
		std::cout << "VSSD ERROR : This Inode is not exist!" << std::endl;
		return;
	}

	if (Inode && ((! Inode->IsLink() ) || (Inode->IsLink() && Inode->GetSubInodes()[0])))
	{
		MyVssd.GetNooowPan()->GetNowPath() = a;
	}
	else
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}




}