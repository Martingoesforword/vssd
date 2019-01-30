#include "pch.h" 
sjh::vssd_folder * sjh::vssdMd::vMd(vssd_disk & MyVssd, std::wstring & mdCommand)
{
	tools_vssd::Trim(mdCommand);

	tool_path Path; 
	vssd_folder * folder = vssd_vcmd::v_FindPathForFirst(MyVssd, mdCommand, Path);
	
	if (nullptr == folder)
	{
		Path.SetFoldersByWstring(mdCommand);
		if (Path.IsRelativePath())
		{
			return MyVssd.GetNooowPan()->GetNooowPos()->BuildPath(MyVssd, Path, vssd_folder::IS_FOLDER);
		}
		else
		{
			return MyVssd.GetGenius()->BuildPath(MyVssd, Path, vssd_folder::IS_FOLDER);
		}  
	}
	else
	{
		std::wcout << L"子目录或文件 "  << folder->GetName() << " 已经存在。"; 
		return nullptr;
	}

}
