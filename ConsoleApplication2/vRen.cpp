#include "pch.h" 
//����--Ŀǰ·��
void sjh::tool_vcmd::vRen(vssd & MyVssd, std::wstring & renCommand) {




	if (!MyVssd.GetNowTop()->NowPath.RealFolders.at(MyVssd.GetNowTop()->NowPath.RealFolders.size() - 2)->FindForFirst(renCommand)) {
		if (MyVssd.GetNowTop()->GetNowPos()->GetName().compare(MyVssd.GetNowTop()->root->GetName()) != 0)
			MyVssd.GetNowTop()->GetNowPos()->SetName(renCommand);
	}
	else {
		std::cout << "VSSD ERROR : The folder has already existed! " << std::endl;

	}

}

void sjh::tool_vcmd::vRen(vssd & MyVssd, std::wstring & SrcCommand, std::wstring & DesName) {
	tool_path a;
	sjh::vssd_folder * folder = v_FindPathForFirst(MyVssd, SrcCommand, a);
	if (folder && a.Folders.size() > 2 && !(a.RealFolders.at(a.RealFolders.size() - 2)->FindForFirst(DesName))) {
		folder->SetName(DesName);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

