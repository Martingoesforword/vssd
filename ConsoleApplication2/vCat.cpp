#include "pch.h" 
void sjh::tool_vcmd::vCat(vssd & MyVssd, std::wstring & Rear) {
	tool_path a;
	//�ҵ���Ҫָ����ļ���
	sjh::vssd_folder * Srcfolder = v_FindPathForFirst(MyVssd, Rear, a);
	if (Srcfolder) Srcfolder->PrintContent();
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}