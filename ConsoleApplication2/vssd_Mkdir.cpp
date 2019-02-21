#include "pch.h" 
#include "vssdMkdir.h"  
namespace sjh {
	vssd_inode* vssdMkdir::vMd(VirtualDisk & MyVssd, const std::wstring & Command)
	{
		std::wstring mdCommand(Command);
		tool::string::Trim(mdCommand);


		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, mdCommand);

		if (nullptr == Inode)
		{
			tools_path Path;
			Path.SetInodesByWstring(mdCommand);
			if (Path.IsAbsolutePath())
			{
				return MyVssd.BuildPath(MyVssd,MyVssd.GetGenius(), Path, vssd_inode::IS_FOLDER);
			}
			else
			{
				return MyVssd.BuildPath(MyVssd,MyVssd.GetNooowPan()->GetNooowPos(), Path, vssd_inode::IS_FOLDER);
			}
		}
		else
		{
			std::wcout << L"子目录或文件 " << Inode->GetName() << " 已经存在。";
			return nullptr;
		}

	} 
	
	int vssdMkdir::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		for (size_t i = 1; i < Rear.size(); i++)
		{
			vMd(MyVssd, Rear[i]);
		}
		
		return EXE_OK;
	}
}