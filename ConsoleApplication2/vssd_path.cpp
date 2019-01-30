
#include "pch.h"    

int sjh::tool_path::Serialize(std::vector<wchar_t>& Byte_Toptable)
{
	int Start = Byte_Toptable.size();
	sjh::tools_vssd::PushLengthValue(PathTypeCode, Byte_Toptable);
	sjh::tools_vssd::PushLengthValue(Inodes.size(), Byte_Toptable);
	for (size_t i = 0; i < Inodes.size(); i++)
	{
		sjh::tools_vssd::PushString(Inodes[i], Byte_Toptable);
	}
	return Start;
}

void sjh::tool_path::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
{ 
	Inodes.clear();
	RealInodes.clear();
	PathTypeCode = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos); 
	int InodesSize = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos);
	for (int i = 0; i < InodesSize; i++)
	{
		Inodes.push_back(sjh::tools_vssd::GetString(ByteVssd, Pos));
	}
}

sjh::tool_path::tool_path()
{
	PathTypeCode = sjh::tool_path::IS_ABSOLUTE_PATH;
}

 
 
 

sjh::vssd_Inode * sjh::tool_path::GetNow()
{
	return RealInodes.at(RealInodes.size() - 1);
}

void sjh::tool_path::Clear()
{
	Inodes.clear();
	RealInodes.clear();
}


void sjh::tool_path::SetInodesByWstring(std::wstring pathString)
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
					Inodes.push_back(Nowstring);
					RealInodes.push_back(nullptr);
				}
				else if (Nowstring == L".." &&Inodes.size() > 0 && Inodes.at(Inodes.size() - 1) != L"..")
				{
					Inodes.pop_back();
				}
				else if (Nowstring == L"..")
				{
					tools_vssd::Trim(Nowstring);
					Inodes.push_back(Nowstring);
					RealInodes.push_back(nullptr);
				} 
				 
		}
		else if ((Pos = pathString.find('/', beForePos)) != std::wstring::npos)
		{
			if (Pos != 0 && beForePos <= Pos - 1)
			{
				//找到beForePos+1到Pos-1的字符串放入Inodes数组里，并更改记录
				Nowstring = pathString.substr(beForePos, Pos - beForePos);

				if (Nowstring != L"." && Nowstring != L"..")
				{
					tools_vssd::Trim(Nowstring);
					Inodes.push_back(Nowstring);
					RealInodes.push_back(nullptr);
				}
				else if (Nowstring == L".." &&Inodes.size() > 0 && Inodes.at(Inodes.size() - 1) != L"..")
				{
					Inodes.pop_back();
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
			Inodes.push_back(Nowstring);
			RealInodes.push_back(nullptr);
		}
		else if (Nowstring == L".." && Inodes.size() > 0 && Inodes.at(Inodes.size() - 1) != L"..")
		{
			Inodes.pop_back();
		}
		else if (Nowstring == L"..")
		{
			Inodes.push_back(L"..");
			RealInodes.push_back(nullptr);
		}

	} 
	if (Inodes[0].size() && Inodes[0].at(1) == ':') PathTypeCode = IS_ABSOLUTE_PATH;
	else PathTypeCode = IS_RELATIVE_PATH;
}
std::wstring sjh::tool_path::GetPathWstring()
{
	std::wstring Path;
	if (Inodes.size() == 1)
	{
		Path.append( Inodes.at(0) );
		Path.append(L"\\");
	}
	else
	{
		size_t i = 0;
		for (i = 0; i < Inodes.size() - 1; i++)
		{
			Path.append(Inodes.at(i));
			Path.append(L"\\"); 
		}
		Path.append(Inodes.at(i)); 
	} 
	return Path;
}
int sjh::tool_path::GetTypeCode()
{
	return PathTypeCode;
}
void sjh::tool_path::DeleteOneSub()
{
	if (IsAbsolutePath() && Inodes.size() < 2)
	{ 
		return;
	}
	else 
	{
		Inodes.pop_back();
		RealInodes.pop_back();
	} 
}
void sjh::tool_path::LoadOneSub(vssd_Inode *Inode)
{
	Inodes.push_back(Inode->GetName());
	RealInodes.push_back(Inode);

}

sjh::tool_path::~tool_path()
{

}
