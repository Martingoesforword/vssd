#include "pch.h" 
void sjh::vssdMklink::vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	
	//�ҵ���Ҫָ����ļ���
	tool_path a;
	sjh::vssd_Inode * SrcInode = vssd_vcmd::v_FindPathForFirst(MyVssd, Src, a);

	if (SrcInode && a.Inodes.size() >= 3)
	{
		//�ҵ�֮��
		int posq = LinkName.find_last_of(L"\\");
		int posp = LinkName.find_last_of(L"/");
		posp = posp > posq ? posp : posq;
		std::wstring InodeOfLinkPath = LinkName.substr(0, posp-0);
		sjh::vssd_Inode *InodeOfLink = vssdMd::vMd(MyVssd, InodeOfLinkPath);
		
		//����Link�ļ�
		sjh::vssd_Inode *Link = new sjh::vssd_Inode(L"", sjh::vssd_Inode::IS_LINK); 
		InodeOfLink->LoadOneSub(Link); 
		//�ҵ�������Link�ļ�
		Link->LoadOneSub(SrcInode);
		//��Link�ļ���һ�����ļ�����ָ���ļ� 
	}
	else
	{
		std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
	}
}
