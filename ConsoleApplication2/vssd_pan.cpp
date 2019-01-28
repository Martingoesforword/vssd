#include "pch.h" 

sjh::vssd_folder * sjh::vssd_pan::GetNowPos()
{
	return NowPath.GetNow();
}

void sjh::vssd_pan::ShowNowPosForCmd()
{
	std::cout << "VSSD : Now at ";
	for (size_t i = 1; i < NowPath.Folders.size(); i++)
	{
		std::cout << sjh::tools_vssd::WStringToString(NowPath.RealFolders.at(i)->GetName()) << '/';
	}

	std::cout << " , you will say:";
}
void sjh::vssd_pan::ShowNowPos()
{
	std::cout << "VSSD : Now at ";
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

void sjh::vssd_pan::SetNewRoot(sjh::vssd_folder * aroot)
{
	root = aroot;
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

void sjh::vssd_pan::Serialize(std::vector<wchar_t> &Byte_Toptable)
{
	//预留存放rootfolder指针（index）
	sjh::tools_vssd::PushString(root->Name, Byte_Toptable);
	sjh::tools_vssd::Push0ToNSpace(4 - root->Name.size(), Byte_Toptable);

}



sjh::vssd_pan::~vssd_pan()
{
}
