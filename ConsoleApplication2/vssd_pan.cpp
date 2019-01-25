#include "pch.h" 
  
sjh::vssd_folder * sjh::vssd_pan::GetNowPos()
{
	return NowPath.GetNow();
}

void sjh::vssd_pan::ShowNowPosForCmd() {
	std::cout << "VSSD : Now at " ;
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout << sjh::vssd_tool::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	}
	
	std::cout << " , you will say:";
}
void sjh::vssd_pan::ShowNowPos() {
	std::cout << "VSSD : Now at ";
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout<< sjh::vssd_tool::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	}
	std::cout << std::endl;
}
sjh::vssd_pan::vssd_pan(sjh::vssd_folder * aroot, sjh::vssd_folder * aGenius)
{
	root = aroot; 
	NowPath.GetPath(L" \\c:\\", 1);
	NowPath.SetRealpath(aGenius,0);
	NowPath.SetRealpath(aroot,1);

}
 
void sjh::vssd_pan::SetNewRoot(sjh::vssd_folder * aroot)
{
	root = aroot;
}
//����ĿǰĿ¼λ�ú����·������
sjh::vssd_folder * sjh::vssd_pan::FindForFirst(tool_path & apath)		
{
	sjh::vssd_folder * Nowfolder = GetNowPos();
	for (size_t i = 0; i < apath.Folders.size(); i++)
	{
		Nowfolder = Nowfolder->FindForFirst(apath.Folders[i]);
		if (!Nowfolder) {
			//��

			return nullptr;
		} 
	}
	return Nowfolder;


}
 
void sjh::vssd_pan::Serialize(std::vector<unsigned char> &Byte_Toptable)
{
	//Ԥ�����rootfolderָ�루index��
	sjh::vssd_tool::PushString(root->Name, Byte_Toptable);
	sjh::vssd_tool::Push0ToNSpace(4 - root->Name.size(), Byte_Toptable);

}

 

sjh::vssd_pan::~vssd_pan()
{
}