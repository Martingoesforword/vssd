#include "pch.h" 
void sjh::vssdCat::vCat(vssd_disk & MyVssd, std::wstring & Rear)
{
	tool_path a;
	//�ҵ���Ҫָ����ļ���
	sjh::vssd_folder * Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, Rear, a);
	if (Srcfolder) Srcfolder->PrintContent();
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}