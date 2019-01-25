#include "pch.h" 
void sjh::vssdMklink::vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	tool_path a;
	//�ҵ���Ҫָ����ļ���
	sjh::vssd_folder * Srcfolder = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

	if (Srcfolder && a.Folders.size() >= 3)
	{
		//�ҵ�֮��
		if (vssdMd::vMd(MyVssd, LinkName))
		{
			return;
		}



		//����Link�ļ�
		sjh::vssd_folder *Link = MyVssd.GetNowTop()->GetNowPos()->FindForFirst(LinkName);

		Link->VssdTypeCode = 2;
		//�ҵ�������Link�ļ�
		Link->VssdFolderLink(Srcfolder);
		//��Link�ļ���һ�����ļ�����ָ���ļ�
		Srcfolder->AddLink(Link);
	}
	else
	{
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}
