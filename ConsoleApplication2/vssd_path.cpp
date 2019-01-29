
#include "pch.h"    

sjh::tool_path::tool_path()
{
	TypeCode = sjh::tool_path::IS_ABSOLUTE_PATH;
}

void sjh::tool_path::GetPath(std::wstring apath, int aType)
{
	TypeCode = aType;
	PathToFolders(apath);
}
void sjh::tool_path::SetRealpath(vssd_folder *apath, int Pos)
{

	RealFolders.push_back(apath);
}
void sjh::tool_path::TestPrint()
{
	for (size_t i = 0; i < Folders.size(); i++)
	{
		std::cout << sjh::tools_vssd::WStringToString(Folders.at(i)) << std::endl;
	}
}

bool sjh::tool_path::include(sjh::tool_path & path1)
{
	for (size_t i = 1; i < path1.Folders.size(); i++)
	{
		if (path1.Folders.at(i) == Folders[i]) continue;
		else
		{
			if (path1.Folders.size() == Folders.size())
			{
				return 0;
			}
		}
	}
	return 0;
}

sjh::vssd_folder * sjh::tool_path::GetNowFather()
{
	return RealFolders.at(RealFolders.size() - 2);
}

sjh::vssd_folder * sjh::tool_path::GetNow()
{
	return RealFolders.at(RealFolders.size() - 1);
}


void sjh::tool_path::PathToFolders(std::wstring path)
{
	tools_vssd::Trim(path);
	size_t Pos = 0;
	size_t beForePos = 0;
	std::wstring Nowstring;
	while (Folders.size() <= Folders.max_size() && Pos != std::wstring::npos)
	{
		if ((Pos = path.find('\\', beForePos)) != std::wstring::npos && beForePos <= Pos - 1)
		{ 
				Nowstring = path.substr(beForePos, Pos - beForePos);

				if (Nowstring != L"." && Nowstring != L"..")
				{
					tools_vssd::Trim(Nowstring);
					Folders.push_back(Nowstring);
				}
				else if (Nowstring == L".." &&Folders.size() > 0 && Folders.at(Folders.size() - 1) != L"..")
				{
					Folders.pop_back();
				}
				else if (Nowstring == L"..")
				{
					tools_vssd::Trim(Nowstring);
					Folders.push_back(Nowstring);
				} 
				 
		}
		else if ((Pos = path.find('/', beForePos)) != std::wstring::npos)
		{
			if (Pos != 0 && beForePos <= Pos - 1)
			{
				//找到beForePos+1到Pos-1的字符串放入Folders数组里，并更改记录
				Nowstring = path.substr(beForePos, Pos - beForePos);

				if (Nowstring != L"." && Nowstring != L"..")
				{
					tools_vssd::Trim(Nowstring);
					Folders.push_back(Nowstring);
				}
				else if (Nowstring == L".." &&Folders.size() > 0 && Folders.at(Folders.size() - 1) != L"..")
				{
					Folders.pop_back();
				}
			}
		}
		if (Pos != std::wstring::npos)
			beForePos = Pos + 1;
	}
	if (beForePos <= path.length() - 1)
	{
		Nowstring = path.substr(beForePos, path.length() - beForePos);
		tools_vssd::Trim(Nowstring);
		if (Nowstring != L"." && Nowstring != L"..")
		{
			tools_vssd::Trim(Nowstring);
			Folders.push_back(Nowstring);
		}
		else if (Nowstring == L".." && Folders.size() > 0 && Folders.at(Folders.size() - 1) != L"..")
		{
			Folders.pop_back();
		}
		else if (Nowstring == L"..")
		{
			Folders.push_back(L"..");
		}

	}



}
std::wstring sjh::tool_path::FoldersToPath()
{
	std::wstring Path;
	for (size_t i = 1; i < RealFolders.size(); i++)
	{ 
		Path.append(RealFolders[i]->GetName() + L"\\");
	}
	if (RealFolders.size() == 3) Path.append(L"\b");
	return Path;
}
int sjh::tool_path::GetTypeCode()
{
	return TypeCode;
}
void sjh::tool_path::DeleteOne()
{
	Folders.pop_back();
	RealFolders.pop_back();

}
void sjh::tool_path::AddOne(vssd_folder *folder)
{
	Folders.push_back(folder->GetName());
	RealFolders.push_back(folder);

}

sjh::tool_path::~tool_path()
{

}
