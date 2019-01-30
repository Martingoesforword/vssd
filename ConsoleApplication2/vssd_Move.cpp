#include "pch.h" 
void sjh::vssdMove::vMove(vssd_disk & MyVssd, std::wstring & Des)
{

	tool_path b;
	sjh::vssd_Inode * disInode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Des, b);
	if (disInode)
	{
		disInode->LoadOneSub(MyVssd.GetNooowPan()->GetNooowPos());
	}
	else
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}

}
//ÒÆ¶¯ÎÄ¼þ¼Ð
void sjh::vssdMove::vMove(vssd_disk & MyVssd, std::wstring & Src, std::wstring & Des)
{

	tool_path a;
	tool_path b;
	sjh::vssd_Inode * SrcInode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);
	sjh::vssd_Inode * disInode = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Des, b);
	if (!SrcInode)
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;  return;
	}
	if (!SrcInode)
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;  return;
	}
	if (SrcInode->IsFile())
	{
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vssdCopy::vCopy(MyVssd, Src, Des);
		return;
	}
	if (SrcInode && disInode && a.Inodes.size() >= 3 && b.Inodes.size() >= 2)
	{
		a.RealInodes.at(a.RealInodes.size() - 2)->UnloadOneSub(SrcInode);
		disInode->LoadOneSub(SrcInode);
	}
	else
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}



}
