#include "pch.h" 
sjh::vssd_Inode * sjh::vssdMd::vMd(vssd_disk & MyVssd, std::wstring & mdCommand)
{
	tools_vssd::Trim(mdCommand);

	tool_path Path; 
	vssd_Inode * Inode = vssd_vcmd::v_FindPathForFirst(MyVssd, mdCommand, Path);
	
	if (nullptr == Inode)
	{
		Path.SetInodesByWstring(mdCommand);
		if (Path.IsRelativePath())
		{
			return MyVssd.BuildPath(MyVssd.GetGenius(), Path, vssd_Inode::IS_FOLDER);
		}
		else
		{
			return MyVssd.BuildPath(MyVssd.GetNooowPan()->GetNooowPos(), Path, vssd_Inode::IS_FOLDER);
		}  
	}
	else
	{
		std::wcout << L"子目录或文件 "  << Inode->GetName() << " 已经存在。"; 
		return nullptr;
	}

}
