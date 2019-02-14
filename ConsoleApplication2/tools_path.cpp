#include "pch.h"  
#include "tools_path.h"
namespace sjh {

	size_t tools_path::Serialize(std::vector<wchar_t>& Byte_Toptable)
	{
		size_t Start = Byte_Toptable.size();
		tool::stringtools::PushLengthValue(PathTypeCode, Byte_Toptable);
		tool::stringtools::PushLengthValue(Inodes.size(), Byte_Toptable);
		for (size_t i = 0; i < Inodes.size(); i++)
		{
			tool::stringtools::PushString(Inodes[i], Byte_Toptable);
		}
		return Start;
	}

	void tools_path::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
	{
		Inodes.clear();
		RealInodes.clear();
		PathTypeCode = tool::stringtools::GetLengthValue(ByteVssd, Pos);
		int InodesSize = tool::stringtools::GetLengthValue(ByteVssd, Pos);
		for (int i = 0; i < InodesSize; i++)
		{
			Inodes.push_back(tool::stringtools::GetString(ByteVssd, Pos));
		}
	}

	tools_path::tools_path()
	{
		PathTypeCode = tools_path::IS_ABSOLUTE_PATH;
	}





	vssd_inode * tools_path::GetNow()
	{
		return RealInodes.at(RealInodes.size() - 1);
	}

	void tools_path::Clear()
	{
		Inodes.clear();
		RealInodes.clear();
	}


	void tools_path::SetInodesByWstring(std::wstring pathString)
	{
		tool::stringtools::Trim(pathString);
		size_t Pos = 0;
		size_t beForePos = 0;
		std::wstring Nowstring;

		while (Pos != std::wstring::npos)
		{
			if ((Pos = pathString.find('\\', beForePos)) != std::wstring::npos && beForePos <= Pos - 1)
			{
				Nowstring = pathString.substr(beForePos, Pos - beForePos);

				if (Nowstring != L"." && Nowstring != L"..")
				{
					tool::stringtools::Trim(Nowstring);
					Inodes.push_back(Nowstring);
					RealInodes.push_back(nullptr);
				}
				else if (Nowstring == L".." &&Inodes.size() > 0 && Inodes.at(Inodes.size() - 1) != L"..")
				{
					Inodes.pop_back();
				}
				else if (Nowstring == L"..")
				{
					tool::stringtools::Trim(Nowstring);
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
						tool::stringtools::Trim(Nowstring);
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
			tool::stringtools::Trim(Nowstring);
			if (Nowstring != L"." && Nowstring != L"..")
			{
				tool::stringtools::Trim(Nowstring);
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
	std::wstring tools_path::GetPathWstring()
	{
		std::wstring Path;
		if (Inodes.size() == 1)
		{
			Path.append(Inodes.at(0));
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
	int tools_path::GetTypeCode()
	{
		return PathTypeCode;
	}
	void tools_path::DeleteOneSub()
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
	void tools_path::LoadOneSub(vssd_inode *Inode)
	{
		Inodes.push_back(Inode->GetName());
		RealInodes.push_back(Inode);

	}

	tools_path::~tools_path()
	{

	}
}