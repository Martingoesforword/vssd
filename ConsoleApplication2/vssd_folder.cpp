#include "pch.h"  

const std::wstring sjh::vssd_folder::VssdTypeName[3] = { L"FILE",L"DIR", L"SYMLINKD" };

 
std::wstring sjh::vssd_folder::GetTypeName()
{
	return VssdTypeName[FolderTypeCode];
}
 
sjh::vssd_folder::vssd_folder(std::wstring aName, int aCode) :base_namedable(aName)
{  
	FolderTypeCode = aCode;  
}


void sjh::vssd_folder::AddOneSub(sjh::vssd_folder *LinktoSub)
{

	SubFolders.push_back(LinktoSub);

}

 

sjh::vssd_folder *sjh::vssd_folder::BuildPath(sjh::vssd_disk & MyVssd, sjh::tool_path &aPath,int aType)
{ 
	if (aPath.IsAbsolutePath()) 
	{
		return MyVssd.GetGenius()->BuildPath(MyVssd, aPath,aType);
	}
	else if (IsLink())
	{ 
		return SubFolders[0]->BuildPath(MyVssd, aPath,aType);
	}
	else if (IsFolder()) 
	{
		sjh::vssd_folder *Now = this;
		bool CheckedFlag = true;  

		for (size_t i = 0; i < aPath.Folders.size(); i++)
		{
			sjh::vssd_folder *Change;
			if(CheckedFlag && (Change = Now->FindForFirst(aPath.Folders[i])))
			{  
				Now = Change;
				while (Now->IsLink())
				{
					Now = Now->SubFolders[0];
				}
				CheckedFlag = false;
			}
			else 
			{
				sjh::vssd_folder *f1 = new sjh::vssd_folder(aPath.Folders[i], aType);
				Now->AddOneSub(f1);
				Now = f1; 
			}
			
		}
		return Now;
	}
	else {
		return nullptr;
	}
	

}

 

void sjh::vssd_folder::PrintAllSub(sjh::vssd_disk& MyVssd, int pram, std::wstring now)//pram 1：tree  2：自己
{ 
	using namespace sjh;
	std::cout << " 驱动器 C 中的卷是 " << tools_vssd::WStringToString(MyVssd.GetName()) << "。\n 卷的序列号是 ";
	std::cout << std::setfill('0') << std::setw(4) << std::setiosflags(std::ios::uppercase) << std::hex << (int)(&MyVssd) / 0x10000 << " - " << std::setfill('0') << std::setw(4) << std::hex << std::setiosflags(std::ios::uppercase) << (int)(&MyVssd) % 0x10000 << "\n";
	
	int p = 0;
	 
	std::cout << "\n "<< tools_vssd::WStringToString(now) << " 的目录\n" << std::endl;
	std::cout << tools_vssd::WStringToString(tools_vssd::GetTimeString(GetCreateTime()) )<< "    " << std::setiosflags(std::ios::right)  << std::setfill(' ') << std::setw(10) << " " << std::setiosflags(std::ios::left) << "." << std::endl;
	 

	for (size_t i = 0; i < SubFolders.size(); i++)
	{
		

	defeatfolder:

		if (SubFolders.at(p) != NULL)
		{
			if(FolderTypeCode == IS_FILE)
			{
				std::cout<< tools_vssd::WStringToString(tools_vssd::GetTimeString(SubFolders.at(p)->GetCreateTime())) << "    " << tools_vssd::WStringToString(SubFolders[p]->GetTypeName()) << SubFolders[p]->GetContent().size() * sizeof(unsigned char) << " "<< tools_vssd::WStringToString(SubFolders.at(p)->GetName()) << std::endl;
			}
			else {
				std::cout << tools_vssd::WStringToString(tools_vssd::GetTimeString(SubFolders.at(p)->GetCreateTime())) << "    "  << std::setiosflags(std::ios::right) << "<"<< tools_vssd::WStringToString(SubFolders[p]->GetTypeName()) << ">" << std::setfill(' ') << std::setw(9)<< " " << tools_vssd::WStringToString(SubFolders.at(p)->GetName() )<< std::endl;
			}
		}
		else
		{
			p++; goto defeatfolder;
		}
		p++;
	}


}

void sjh::vssd_folder::DeleteOneSub(sjh::vssd_folder * deletfolder)
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		for (; j < SubFolders.max_size(); j++)
		{
			if (SubFolders.at(j) == NULL)
			{
				continue;
			}
			else
			{

				break;
			}
		}

		if (SubFolders.at(j)->GetName().compare(deletfolder->GetName()) == IS_SAMESTRING)
		{
			SubFolders.at(j)->DeleteWholeTree();
			SubFolders.at(j)->~vssd_folder();
			std::vector<sjh::vssd_folder *>::iterator it = SubFolders.begin();

			SubFolders.erase(it + j);
			return;
		}
		else
		{
			j++;
		}

	}
}

void sjh::vssd_folder::UnloadOneSub(sjh::vssd_folder * deletfolder)
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		for (; j < SubFolders.max_size(); j++)
		{
			if (SubFolders.at(j) == NULL)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		if (SubFolders.at(j)->GetName().compare(deletfolder->GetName()) == IS_SAMESTRING)
		{
			std::vector<sjh::vssd_folder*>::iterator it = SubFolders.begin();
			SubFolders.erase(it + j);
			return;
		}
		else
		{
			j++;
		}

	}
}

void sjh::vssd_folder::DeleteWholeTree()
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		for (; j < SubFolders.max_size(); j++)
		{
			if (SubFolders.at(j) == NULL)
			{
				continue;
			}
			else
			{
				SubFolders.at(j)->DeleteWholeTree();
				SubFolders.at(j)->~vssd_folder();
				break;
			}
		}


		j++;


	}
}



 

sjh::vssd_folder * sjh::vssd_folder::FindForFirst(std::wstring folder)
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		if (SubFolders.at(j) != NULL)
		{

			if (sjh::tools_vssd::WStringMatch(SubFolders.at(j)->GetName(), folder) != 0)
			{

				return SubFolders.at(j);
			}
			else
			{
				j++;
			}
			if (j > SubFolders.max_size())
			{
				break;
			}
		}

	}
	return nullptr;
}

 

sjh::vssd_folder * sjh::vssd_folder::FindTree(tool_path * apath, int pathPos)
{

	sjh::vssd_folder* reserchout;
	reserchout = FindForFirst(apath->Folders[0]);

	return nullptr;

}

 
void sjh::vssd_folder::AddContent(wchar_t Byte)		//追加字符
{
	if (IsFile())
	{
		GetContent().push_back(Byte);
	}
	else
	{
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}
void sjh::vssd_folder::SetContentString(std::wstring str)		//追加字符
{
	if (IsFile())
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			GetContent().push_back(*((unsigned char*)&str[i] + 0));
			GetContent().push_back(*((unsigned char*)&str[i] + 1));
		}

	}
	else
	{
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}
std::vector<sjh::vssd_folder*>& sjh::vssd_folder::GetSubFolders()
{
	return SubFolders;
}
void sjh::vssd_folder::PrintContent()			//返回NULL 和 下一个字符
{
	static int index = -1;
	if (IsFile())
	{
		for (size_t i = 0; i < GetContent().size(); i++)
		{
			std::cout << GetContent()[i];
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}

int sjh::vssd_folder::Serialize(std::vector<wchar_t>& Bytes)
{
	int Start = Bytes.size();
	sjh::tools_vssd::PushString(GetName(), Bytes);
	sjh::tools_vssd::PushLengthValue(FolderTypeCode, Bytes);
	sjh::tools_vssd::PushWcharVector(GetContent(), Bytes);
	sjh::tools_vssd::PushLengthValue(SubFolders.size(), Bytes);
	if (FolderTypeCode == IS_FOLDER) {
		for (size_t i = 0; i < SubFolders.size(); i++)
		{
			SubFolders.at(i)->Serialize(Bytes);
		}
	}
	return Start;
}
 
void sjh::vssd_folder::DeSerialize(std::vector<wchar_t>& ByteVssd, int& Pos)
{
	SetName(tools_vssd::GetString(ByteVssd, Pos)); 
	FolderTypeCode = tools_vssd::GetLengthValue(ByteVssd, Pos);
	tools_vssd::GetWcharVector(GetContent(), ByteVssd, Pos);
	int SubSize = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos);

	if (FolderTypeCode == IS_FOLDER) {
		for (int i = 0; i < SubSize; i++)
		{
			sjh::vssd_folder *sub = new sjh::vssd_folder(L"", IS_FOLDER);
			AddOneSub(sub);
			sub->DeSerialize(ByteVssd, Pos);
		}
	}


} 
 
sjh::vssd_folder::~vssd_folder()
{
}
 
void sjh::vssd_folder::Display()
{
	std::wcout << L"<vssd_folder class>" << std::endl;
	std::wcout << L"\tName = " << Name << std::endl;
}
 
