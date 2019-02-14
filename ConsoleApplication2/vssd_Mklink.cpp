#include "pch.h"
#include "vssdMklink.h"
namespace sjh {
	void vssdMklink::vMklink(VirtualDisk & MyVssd, std::wstring & Src, std::wstring & LinkName)
	{

		//�ҵ���Ҫָ����ļ���
		tools_path a;
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Src, a);

		if (SrcInode && a.Inodes.size() >= 3)
		{
			//�ҵ�֮��
			size_t posq = LinkName.find_last_of(L"\\");
			size_t posp = LinkName.find_last_of(L"/");
			posp = posp > posq ? posp : posq;
			std::wstring InodeOfLinkPath = LinkName.substr(0, posp - 0);
			vssdMkdir taskMd;
			//vssd_inode *InodeOfLink = taskMd.vMd(MyVssd, InodeOfLinkPath);

			//����Link�ļ�
			vssd_inode *Link = new vssd_inode(L"", vssd_inode::IS_LINK);
			//InodeOfLink->LoadOneSub(Link);
			//�ҵ�������Link�ļ�
			Link->LoadOneSub(SrcInode);
			//��Link�ļ���һ�����ļ�����ָ���ļ� 

			//ͬʱ��·������
			Link->SetLinkPath(a);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}
	}
	void vssdMklink::Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}
}