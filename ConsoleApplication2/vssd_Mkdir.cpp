#include "pch.h" 
sjh::vssd_folder * sjh::vssdMd::vMd(vssd_disk & MyVssd, std::wstring & mdCommand)
{
	tool_path a; 
	sjh::vssd_folder * folder = sjh::vssd_vcmd::v_FindPathForFirst(MyVssd, mdCommand, a); 
	tools_vssd::Trim(mdCommand);
	if (!folder)
	{
		a.PathToFolders(mdCommand);
		if (a.Folders[0].length() > 1 && a.Folders[0].at(1) != ':')
		{
			return MyVssd.GetNooowPan()->GetNooowPos()->Build(MyVssd, a);
		}
		else
		{
			return MyVssd.GetGenius()->Build(MyVssd, a);
		} 

	}
	else
	{
		return nullptr;
	}

}
