#include "pch.h"  
#include "tools_path.h"
#include "vssd_inode.h" 
namespace sjh {

	size_t tools_path::Serialize(std::vector<wchar_t>& Byte_Toptable)
	{
		size_t Start = Byte_Toptable.size();
		tool::string::PushLengthValue(PathTypeCode, Byte_Toptable);
		tool::string::PushLengthValue(Inodes.size(), Byte_Toptable);
		for (size_t i = 0; i < Inodes.size(); i++)
		{
			tool::string::PushString(Inodes[i], Byte_Toptable);
		}
		return Start;
	}

	void tools_path::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
	{
		Inodes.clear();
		RealInodes.clear();
		PathTypeCode = tool::string::GetLengthValue(ByteVssd, Pos);
		int InodesSize = tool::string::GetLengthValue(ByteVssd, Pos);
		for (int i = 0; i < InodesSize; i++)
		{
			Inodes.push_back(tool::string::GetString(ByteVssd, Pos));
		}
	}

	tools_path::tools_path():PathTypeCode(tools_path::IS_ABSOLUTE_PATH)
	{ 
	}
	tools_path::tools_path(const std::wstring& pathString)
	{
		tools_path();
		SetInodesByWstring(pathString);
	}


	const vssd_inode * tools_path::GetNowPtr() const
	{
		return RealInodes.at(RealInodes.size() - 1);
	}

	std::wstring tools_path::GetNowWString()
	{
		return Inodes[Inodes.size() - 1];
	}

	void tools_path::Clear()
	{
		Inodes.clear();
		RealInodes.clear();
	}


	void tools_path::SetInodesByWstring(std::wstring pathString)
	{
		tool::string::Trim(pathString);
		size_t Pos = 0;
		size_t beForePos = 0;
		std::wstring Nowstring;
		if (pathString[0] == L'\\')
		{
			Inodes.push_back(L"\\");
			RealInodes.push_back(nullptr);
			beForePos += 1;
		}
		while (Pos != std::wstring::npos)
		{
			tool::string::CheckQuotation(Nowstring);
			if ((Pos = pathString.find('\\', beForePos)) != std::wstring::npos && beForePos <= Pos - 1)
			{
				Nowstring = pathString.substr(beForePos, Pos - beForePos);
				tool::string::CheckQuotation(Nowstring);
				if (Nowstring != L"." && Nowstring != L"..")
				{  
					Inodes.push_back(Nowstring);
					RealInodes.push_back(nullptr);
				}
				else if (Nowstring == L".." &&Inodes.size() > 0 && Inodes.at(Inodes.size() - 1) != L".." && Inodes.at(Inodes.size() - 1) != L"\\")
				{
					Inodes.pop_back();
					RealInodes.pop_back();
				}
				else if (Nowstring == L"..")
				{ 
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
		if (beForePos <= pathString.size() - 1)
		{
			Nowstring = pathString.substr(beForePos, pathString.size() - beForePos);
			tool::string::Trim(Nowstring);
			tool::string::CheckQuotation(Nowstring);
			if (Nowstring != L"." && Nowstring != L"..")
			{ 
				 
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
		if (Inodes.size() && Inodes[0].size() == 2 && Inodes[0].at(1) == ':') PathTypeCode = IS_ABSOLUTE_PATH;
		else PathTypeCode = IS_RELATIVE_PATH;
	}
	std::wstring tools_path::GetPathWstring()  const
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
			for (i = 0; i+1 < Inodes.size(); i++)
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
	void tools_path::LoadOneSub(const vssd_inode *Inode)
	{ 
		Inodes.push_back(Inode->GetName());
		RealInodes.push_back(const_cast<vssd_inode *>(Inode));
	}

	tools_path::~tools_path()
	{

	}
}