#include "pch.h" 
void sjh::vssdMove::vMove(vssd_disk & MyVssd, std::wstring & Des)
{

	tool_path b;
	sjh::vssd_folder * disfolder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Des, b);
	if (disfolder)
	{
		disfolder->AddOneSub(MyVssd.GetNooowPan()->GetNooowPos());
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}
//�ƶ��ļ���
void sjh::vssdMove::vMove(vssd_disk & MyVssd, std::wstring & Src, std::wstring & Des)
{

	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, Des, b);
	if (!Srcfolder)
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return;
	}
	if (!Srcfolder)
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return;
	}
	if (Srcfolder->IsFile())
	{
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vssdCopy::vCopy(MyVssd, Src, Des);
		return;
	}
	if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2)
	{
		a.RealFolders.at(a.RealFolders.size() - 2)->OffOneSub(Srcfolder);
		disfolder->AddOneSub(Srcfolder);
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}



}
