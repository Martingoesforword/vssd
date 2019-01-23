#include "pch.h" 
  
sjh::vssd_folder * sjh::vssd_foldertop::GetNowPos()
{
	return NowPath.GetNow();
}

void sjh::vssd_foldertop::ShowNowPosForCmd() {
	std::cout << "VSSD : Now at " ;
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout << sjh::vssd_tool::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	}
	
	std::cout << " , you will say:";
}
void sjh::vssd_foldertop::ShowNowPos() {
	std::cout << "VSSD : Now at ";
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout<< sjh::vssd_tool::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	}
	std::cout << std::endl;
}
sjh::vssd_foldertop::vssd_foldertop(sjh::vssd_folder * aroot, sjh::vssd_folder * aGenius)
{
	root = aroot; 
	NowPath.GetPath(L" \\c:\\", 1);
	NowPath.SetRealpath(aGenius,0);
	NowPath.SetRealpath(aroot,1);

}
 
void sjh::vssd_foldertop::SetNewRoot(sjh::vssd_folder * aroot)
{
	root = aroot;
}
//根据目前目录位置和相对路径查找
sjh::vssd_folder * sjh::vssd_foldertop::Find(tool_path & apath)		
{
	sjh::vssd_folder * Nowfolder = GetNowPos();
	for (int i = 0; i < apath.Folders.size(); i++)
	{
		Nowfolder = Nowfolder->Find(apath.Folders[i]);
		if (!Nowfolder) {
			//无

			return nullptr;
		} 
	}
	return Nowfolder;


}
 
void sjh::vssd_foldertop::Serialize(std::vector<unsigned char> &Byte_Toptable)
{
	//预留存放rootfolder指针（index）
	sjh::vssd_tool::PushString(root->Name, Byte_Toptable);
	sjh::vssd_tool::Push0ToNSpace(4 - root->Name.size(), Byte_Toptable);

}

 

sjh::vssd_foldertop::~vssd_foldertop()
{
}
