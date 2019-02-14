#include "pch.h"  
#include "vssd_manager.h"
 
namespace sjh { 
	vssd_manager::vssd_manager()
	{ 
		operators.push_back(new vssd_optcmd());
	}  
	void vssd_manager::CreateDiskDemo1()
	{

		vssd_inode *Genius = new vssd_inode(L"", vssd_inode::IS_FOLDER);
		vssd_inode *c_pan = new vssd_inode(L"C:", vssd_inode::IS_FOLDER);

		vssd_inode *Folder = new vssd_inode(L"sjh", vssd_inode::IS_FOLDER);
		vssd_inode *File = new vssd_inode(L"sjh.txt", vssd_inode::IS_FILE);
		vssd_inode *File1 = new vssd_inode(L"sjh1", vssd_inode::IS_FOLDER);
		vssd_inode *File2 = new vssd_inode(L"sjh2", vssd_inode::IS_FOLDER);
		c_pan->LoadOneSub(Folder);
		c_pan->LoadOneSub(File);

		Folder->LoadOneSub(File1);
		Folder->LoadOneSub(File2);
		vssd_pan *MyTopcpan = new vssd_pan(c_pan, Genius);//���ظ�Ŀ¼
		VirtualDisk *MyVssd = new VirtualDisk(MyTopcpan, Genius, L"firstVssd");

		MyVssd->AddNewPan(MyTopcpan);

		Genius->LoadOneSub(c_pan);
		disk = MyVssd;
	}

	int vssd_manager::ComeInOperaterByAccessWay(int OptType)
	{ 
		for (size_t i = 0; i < operators.size(); i++)
		{
			if(OptType == operators[i]->OptType) return operators[i]->ExeInterface(*disk);
		}  
		return 1; 
	}
	vssd_manager::~vssd_manager()
	{
		for (size_t i = 0; i < operators.size(); i++)
		{
			delete operators[i];
		}
		delete disk;
	}

	 
}
 
