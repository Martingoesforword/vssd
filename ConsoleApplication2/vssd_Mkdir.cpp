#include "pch.h" 
#include "vssdMkdir.h" 
namespace sjh {
	vssd_inode * vssdMkdir::vMd(VirtualDisk & MyVssd, std::wstring & mdCommand)
	{
		tool::stringtools::Trim(mdCommand);

		tools_path Path;
		vssd_inode * Inode = vssd_optcmd::v_FindPathForFirst(MyVssd, mdCommand, Path);

		if (nullptr == Inode)
		{
			Path.SetInodesByWstring(mdCommand);
			if (Path.IsRelativePath())
			{
				return MyVssd.BuildPath(MyVssd.GetGenius(), Path, vssd_inode::IS_FOLDER);
			}
			else
			{
				return MyVssd.BuildPath(MyVssd.GetNooowPan()->GetNooowPos(), Path, vssd_inode::IS_FOLDER);
			}
		}
		else
		{
			std::wcout << L"子目录或文件 " << Inode->GetName() << " 已经存在。";
			return nullptr;
		}

	}
	void vssdMkdir::Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}
}