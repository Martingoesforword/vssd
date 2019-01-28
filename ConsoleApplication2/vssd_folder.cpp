#include "pch.h"   
void sjh::vssd_folder::VssdFolderInit()
{
}

std::wstring sjh::vssd_folder::GetType()
{
	return VssdTypeName[VssdTypeCode];
}

sjh::vssd_folder::vssd_folder(std::wstring aName, int aCode)
{
	Name = aName;
	VssdTypeCode = aCode;
	VssdFolderInit();

}


void sjh::vssd_folder::VssdFolderLink(sjh::vssd_folder *LinktoSub)
{

	SubFolders.push_back(LinktoSub);

}

std::wstring sjh::vssd_folder::GetName()
{
	return Name;
}

void sjh::vssd_folder::Build(sjh::vssd_disk & MyVssd, sjh::tool_path &a)
{

	if (VssdTypeCode == IS_LINK)
	{
		SubFolders[0]->Build(MyVssd, a);
		return;
	}
	sjh::vssd_folder *Now = this;
	int flag = 0;
	for (size_t i = 0; i < a.Folders.size(); i++)
	{
		if (flag || !Now->FindForFirst(a.Folders[i]))
		{
			sjh::vssd_folder *f1 = new sjh::vssd_folder(a.Folders[i], 1);
			Now->VssdFolderLink(f1);
			Now = f1;
			flag = 1;
		}
		else
		{
			Now = Now->FindForFirst(a.Folders[i]);
			while (Now->VssdTypeCode == IS_LINK) Now = Now->SubFolders[0];
		}


	}

}

void sjh::vssd_folder::SetName(std::wstring &aName)
{

	Name = aName;
}



void sjh::vssd_folder::ShowOffSub(sjh::vssd_disk& MyVssd, int pram, std::wstring now)//pram 1：tree  2：自己
{ 
	std::wcout << " 驱动器 C 中的卷是 " << MyVssd.GetName() << "。\n 卷的序列号是 ";
	std::cout << std::setfill('0') << std::setw(4) << std::setiosflags(std::ios::uppercase) << std::hex << (int)(&MyVssd) / 0x10000 << " - " << std::setfill('0') << std::setw(4) << std::hex << std::setiosflags(std::ios::uppercase) << (int)(&MyVssd) % 0x10000 << "\n";
	
	int p = 0;
	std::cout <<"\n "<< sjh::tools_vssd::WStringToString(now) << " 的目录\n" << std::endl;
	std::cout << "2019/01/22" << "  " << "20:26" << "    " << std::setiosflags(std::ios::right) << "<" << sjh::tools_vssd::WStringToString(SubFolders[p]->GetType()) << ">" << std::setfill(' ') << std::setw(10) << " " << std::setiosflags(std::ios::left) << "." << std::endl;
	std::cout << "2019/01/22" << "  " << "20:26" << "    " << std::setiosflags(std::ios::right) << "<" << sjh::tools_vssd::WStringToString(SubFolders[p]->GetType()) << ">" << std::setfill(' ') << std::setw(10) << " " << std::setiosflags(std::ios::left) << ".." << std::endl;


	for (size_t i = 0; i < SubFolders.size(); i++)
	{
		

	defeatfolder:

		if (SubFolders.at(p) != NULL)
		{
			if(VssdTypeCode == IS_FILE)
			{
				std::cout<< "2019/01/22"<<"  " << "20:26" << "    " << sjh::tools_vssd::WStringToString(SubFolders[p]->GetType()) << SubFolders[p]->Content.size() * sizeof(unsigned char) <<" "<< sjh::tools_vssd::WStringToString(SubFolders.at(p)->Name) << std::endl;
			}
			else {
				std::cout << "2019/01/22" << "  " << "20:26" << "    "  << std::setiosflags(std::ios::right) << "<"<<sjh::tools_vssd::WStringToString(SubFolders[p]->GetType())<<">" << std::setfill(' ') << std::setw(9)<<" " << sjh::tools_vssd::WStringToString(SubFolders.at(p)->Name) << std::endl;
			}
		}
		else
		{
			p++; goto defeatfolder;
		}
		p++;
	}


}

void sjh::vssd_folder::DeletOne(sjh::vssd_folder * deletfolder)
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

		if (SubFolders.at(j)->GetName().compare(deletfolder->GetName()) == 0)
		{
			SubFolders.at(j)->DeleteEvery();
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

void sjh::vssd_folder::OffOne(sjh::vssd_folder * deletfolder)
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

		if (SubFolders.at(j)->GetName().compare(deletfolder->GetName()) == 0)
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

void sjh::vssd_folder::DeleteEvery()
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
				SubFolders.at(j)->DeleteEvery();
				SubFolders.at(j)->~vssd_folder();
				break;
			}
		}


		j++;


	}
}



sjh::vssd_folder ** sjh::vssd_folder::FindNext()
{
	if (SubFolders.size() < SubFolders.max_size())
	{
		for (size_t i = 0; i < SubFolders.max_size(); i++)
		{
			if (SubFolders.at(i) == nullptr)
			{
				return &SubFolders.at(i);
			}

		}
		return nullptr;
	}
	else
	{
		return nullptr;
	}


}

sjh::vssd_folder * sjh::vssd_folder::FindForFirst(std::wstring & folder)
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		if (SubFolders.at(j) != NULL)
		{

			if (SubFolders.at(j)->GetCheck() && sjh::tools_vssd::WStringMatch(SubFolders.at(j)->GetName(), folder) != 0)
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

sjh::vssd_folder * sjh::vssd_folder::Find(tool_path * apath, int pathPos)
{

	sjh::vssd_folder* reserchout;
	reserchout = FindForFirst(apath->Folders[0]);

	return nullptr;

}

bool sjh::vssd_folder::isFile()
{
	if (!VssdTypeCode) return true;
	else return false;


}

void sjh::vssd_folder::SetContent(wchar_t Byte)		//追加字符
{
	if (isFile())
	{
		Content.push_back(Byte);
	}
	else
	{
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}
void sjh::vssd_folder::SetContentString(std::wstring str)		//追加字符
{
	if (isFile())
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			Content.push_back(*((unsigned char*)&str[i] + 0));
			Content.push_back(*((unsigned char*)&str[i] + 1));
		}

	}
	else
	{
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}
void sjh::vssd_folder::PrintContent()			//返回NULL 和 下一个字符
{
	static int index = -1;
	if (isFile())
	{
		for (size_t i = 0; i < Content.size(); i++)
		{
			std::cout << Content[i];
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
	sjh::tools_vssd::PushString(Name, Bytes);
	sjh::tools_vssd::PushLengthValue(VssdTypeCode, Bytes);
	sjh::tools_vssd::PushWcharVector(Content, Bytes);
	sjh::tools_vssd::PushLengthValue(SubFolders.size(), Bytes);
	if (VssdTypeCode == IS_FOLDER) {
		for (size_t i = 0; i < SubFolders.size(); i++)
		{
			SubFolders.at(i)->Serialize(Bytes);
		}
	}
	return Start;
}
void sjh::vssd_folder::deSerialize(std::vector<wchar_t>& ByteVssd, int Pos)
{

	Name = tools_vssd::GetString(ByteVssd, Pos);
	VssdTypeCode = tools_vssd::GetLengthValue(ByteVssd, Pos);
	tools_vssd::GetWcharVector(Content, ByteVssd, Pos);
	int SubSize = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos);

	if (VssdTypeCode == IS_FOLDER) {
		for (int i = 0; i < SubSize; i++)
		{
			sjh::vssd_folder *sub = new sjh::vssd_folder(L"", IS_FOLDER);
			VssdFolderLink(sub);
			sub->deSerialize(ByteVssd, Pos);
		}
	}


}
void sjh::vssd_folder::DeleteLinks()
{
	for (size_t i = 0; i < LinkFolders.size(); i++)
	{
		LinkFolders[i]->SubFolders[0] = nullptr;
	}
}
void sjh::vssd_folder::AddLink(sjh::vssd_folder * link)
{
	LinkFolders.push_back(link);
}
sjh::vssd_folder::~vssd_folder()
{
}

void sjh::vssd_folder::SetCheck()
{
	mycheck = false;
}

bool sjh::vssd_folder::GetCheck()
{
	return mycheck;
}

void sjh::vssd_folder::BackCheck()
{
	mycheck = true;
}
