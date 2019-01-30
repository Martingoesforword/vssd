
#include "pch.h"    

int sjh::tool_path::Serialize(std::vector<wchar_t>& Byte_Toptable)
{
	int Start = Byte_Toptable.size();
	sjh::tools_vssd::PushLengthValue(PathTypeCode, Byte_Toptable);
	sjh::tools_vssd::PushLengthValue(Folders.size(), Byte_Toptable);
	for (size_t i = 0; i < Folders.size(); i++)
	{
		sjh::tools_vssd::PushString(Folders[i], Byte_Toptable);
	}
	return Start;
}

void sjh::tool_path::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
{ 
	Folders.clear();
	RealFolders.clear();
	PathTypeCode = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos); 
	int FoldersSize = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos);
	for (size_t i = 0; i < FoldersSize; i++)
	{
		Folders.push_back(sjh::tools_vssd::GetString(ByteVssd, Pos));
	}
}

sjh::tool_path::tool_path()
{
	PathTypeCode = sjh::tool_path::IS_ABSOLUTE_PATH;
}

 
 
 

sjh::vssd_folder * sjh::tool_path::GetNow()
{
	return RealFolders.at(RealFolders.size() - 1);
}

void sjh::tool_path::Clear()
{
	Folders.clear();
	RealFolders.clear();
}


void sjh::tool_path::SetFoldersByWstring(std::wstring pathString)
{
	tools_vssd::Trim(pathString);
	size_t Pos = 0;
	size_t beForePos = 0;
	std::wstring Nowstring; 

	while ( Pos != std::wstring::npos )
	{
		if ((Pos = pathString.find('\\', beForePos)) != std::wstring::npos && beForePos <= Pos - 1)
		{ 
				Nowstring = pathString.substr(beForePos, Pos - beForePos);

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
		else if ((Pos = pathString.find('/', beForePos)) != std::wstring::npos)
		{
			if (Pos != 0 && beForePos <= Pos - 1)
			{
				//找到beForePos+1到Pos-1的字符串放入Folders数组里，并更改记录
				Nowstring = pathString.substr(beForePos, Pos - beForePos);

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
	if (beForePos <= pathString.length() - 1)
	{
		Nowstring = pathString.substr(beForePos, pathString.length() - beForePos);
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
	if (Folders[0].size() && Folders[0].at(1) == ':') PathTypeCode = IS_ABSOLUTE_PATH;
	else PathTypeCode = IS_RELATIVE_PATH;
}
std::wstring sjh::tool_path::GetPathWstring()
{
	std::wstring Path;
	if (Folders.size() == 1)
	{
		Path.append( Folders.at(0) );
		Path.append(L"\\");
	}
	else
	{
		size_t i = 0;
		for (i = 0; i < Folders.size() - 1; i++)
		{
			Path.append(Folders.at(i));
			Path.append(L"\\"); 
		}
		Path.append(Folders.at(i)); 
	} 
	return Path;
}
int sjh::tool_path::GetTypeCode()
{
	return PathTypeCode;
}
void sjh::tool_path::DeleteOneSub()
{
	if (IsAbsolutePath() && Folders.size() < 2)
	{ 
		return;
	}
	else 
	{
		Folders.pop_back();
		RealFolders.pop_back();
	} 
}
void sjh::tool_path::AddOneSub(vssd_folder *folder)
{
	Folders.push_back(folder->GetName());
	RealFolders.push_back(folder);

}

sjh::tool_path::~tool_path()
{

}
