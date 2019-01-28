#include "pch.h" 

sjh::vssd_folder * sjh::vssd_pan::GetNowPos()
{
	return NowPath.GetNow();
}

void sjh::vssd_pan::ShowNowPosForCmd()
{
	 
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout << sjh::tools_vssd::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	} 
	 
}
void sjh::vssd_pan::ShowNowPos()
{
 
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout << sjh::tools_vssd::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	}
	std::cout << std::endl;
}
sjh::vssd_pan::vssd_pan(sjh::vssd_folder * aroot, sjh::vssd_folder * aGenius)
{
	root = aroot;
	NowPath.GetPath(L" \\c:\\", sjh::tool_path::IS_ABSOLUTE_PATH);
	NowPath.SetRealpath(aGenius, sjh::tool_path::IS_RELATIVE_PATH);
	NowPath.SetRealpath(aroot, sjh::tool_path::IS_ABSOLUTE_PATH); 
}

 
//根据目前目录位置和相对路径查找
sjh::vssd_folder * sjh::vssd_pan::FindForFirst(tool_path & apath)
{
	sjh::vssd_folder * Nowfolder = GetNowPos();
	for (size_t i = 0; i < apath.Folders.size(); i++)
	{
		Nowfolder = Nowfolder->FindForFirst(apath.Folders[i]);
		if (!Nowfolder)
		{
			//无 
			return nullptr;
		}
	}
	return Nowfolder; 
}
 



sjh::vssd_pan::~vssd_pan()
{
}
