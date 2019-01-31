#include "vssd_manager.h"


namespace sjh { 
	vssd_manager::vssd_manager()
	{
		Vcmd = *(new vssd_vcmd());
	} 
	vssd_vcmd * vssd_manager::GetVcmd()
	{
		return &Vcmd;
	}
	void vssd_manager::CreateDisk()
	{

		vssd_inode *Genius = new vssd_inode(L"", vssd_inode::IS_FOLDER);
		vssd_inode *c_pan = new vssd_inode(L"C:", vssd_inode::IS_FOLDER);

		vssd_inode *Folder = new vssd_inode(L"sjh", vssd_inode::IS_FOLDER);
		vssd_inode *File = new vssd_inode(L"sjh.txt", vssd_inode::IS_FILE);
		c_pan->LoadOneSub(Folder);
		c_pan->LoadOneSub(File);
		vssd_pan *MyTopcpan = new vssd_pan(c_pan, Genius);//¼ÓÔØ¸ùÄ¿Â¼
		vssd_disk *MyVssd = new vssd_disk(MyTopcpan, Genius, L"firstVssd");

		MyVssd->AddNewPan(MyTopcpan);

		Genius->LoadOneSub(c_pan);
		disk = MyVssd;
	}

	void vssd_manager::ComeInVcmd()
	{
		Vcmd.TypeCode_UI(*disk);
		return;
	}

	vssd_manager::~vssd_manager()
	{
	}
}
 
