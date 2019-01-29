#include "pch.h" 
void sjh::vssdMklink::vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	tool_path a;
	//�ҵ���Ҫָ����ļ���
	sjh::vssd_folder * Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

	if (Srcfolder && a.Folders.size() >= 3)
	{
		//�ҵ�֮��
		int posq = LinkName.find_last_of(L"\\");
		int posp = LinkName.find_last_of(L"/");
		posp = posp > posq ? posp : posq;
		std::wstring FolderOfLinkPath = LinkName.substr(0, posp-0);
		sjh::vssd_folder *FolderOfLink = vssdMd::vMd(MyVssd, FolderOfLinkPath);
		
		//����Link�ļ�
		sjh::vssd_folder *Link = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_LINK); 
		FolderOfLink->LinkNewFolder(Link); 
		//�ҵ�������Link�ļ�
		Link->LinkNewFolder(Srcfolder);
		//��Link�ļ���һ�����ļ�����ָ���ļ�
		Srcfolder->AddLink(Link);
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}
