#include "pch.h"
#include "vssdMklink.h"
#include "vssdMkdir.h" 
namespace sjh {
	//vssd_inode *(*vssdMklink::friendfunc(vssdMkdir & taskMd))(VirtualDisk &MyVssd, const std::wstring &mdCommand)
	//{
	//	return taskMd.vMd;
	//}
	void vssdMklink::vMklink(VirtualDisk & MyVssd, const std::wstring & Src, const std::wstring & LinkName)
	{

		//�ҵ���Ҫָ����ļ���
		tools_path a;
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Src, a);

		if (SrcInode && a.Inodes.size() >= 2)
		{
			//�ҵ�֮��
			size_t posq = LinkName.find_last_of(L"\\");
			size_t posp = LinkName.find_last_of(L"/");
			posp = posp > posq ? posp : posq;
			std::wstring InodeOfLinkPath = LinkName.substr(0, posp - 0);
			vssdMkdir taskMd;
			//����Link�ļ�
			vssd_inode *Inode = taskMd.vMd(MyVssd, LinkName);
			Inode->SetTypeName(vssd_inode::IS_LINKD);
			//vssd_inode *Link = new vssd_inode(L"", vssd_inode::IS_LINKD);
			//InodeOfLink->LoadOneSub(Link);
			//�ҵ�������Link�ļ�
			Inode->LoadOneSub(SrcInode);
			//��Link�ļ���һ�����ļ�����ָ���ļ� 

			//ͬʱ��·������
			Inode->SetLinkPath(a);
		}
		else
		{
			std::cout << "VSSD ERROR : This Inode is not exist! " << std::endl;
		}
	}
	void vssdMklink::vMklinkF(VirtualDisk & MyVssd, const std::wstring & Src, const std::wstring & LinkName)
	{

		//�ҵ���Ҫָ����ļ���
		tools_path a;
		vssd_inode * SrcInode = vssd_optcmd::v_FindPathForFirst(MyVssd, Src, a);

		if (SrcInode && a.Inodes.size() >= 2)
		{
			//�ҵ�֮��
			size_t posq = LinkName.find_last_of(L"\\");
			size_t posp = LinkName.find_last_of(L"/");
			posp = posp > posq ? posp : posq;
			std::wstring InodeOfLinkPath = LinkName.substr(0, posp - 0);
			vssdMkdir taskMd; 
			vssd_inode *InodeOfLink = taskMd.vMd(MyVssd, LinkName);
			//����Link�ļ�
			vssd_inode *Link = new vssd_inode(L"", vssd_inode::IS_LINKD);
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
	void vssdMklink::vMklinkSwitch(VirtualDisk & MyVssd, std::vector<std::wstring> Dirs)
	{ 
		using namespace tool::string;
		if (HasSwitch(Dirs[1]))
		{
			if (IsThisSwitch(Dirs[1], L"d") || IsThisSwitch(Dirs[1], L"D"))
			{
				if (Dirs.size() == 4)
				{
					vMklink(MyVssd, Dirs[3], Dirs[2]);
				} 
			}  
		}
		else
		{
			//�޿���
			vMklinkF(MyVssd, Dirs[3], Dirs[2]);
		}
		 
	}
	 
	int vssdMklink::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{

		vMklinkSwitch(MyVssd, Rear);
		return EXE_OK;
	}
}