#include "pch.h"  

const std::wstring sjh::vssd_Inode::VssdTypeName[3] = { L"FILE",L"DIR", L"SYMLINKD" };

 
std::wstring sjh::vssd_Inode::GetTypeName()
{
	return VssdTypeName[InodeTypeCode];
}
 
sjh::vssd_Inode::vssd_Inode(std::wstring aName, int aCode) :base_namedable(aName)
{  
	InodeTypeCode = aCode;  
}


void sjh::vssd_Inode::LoadOneSub(sjh::vssd_Inode *LinktoSub)
{
	LinktoSub->SetFather(this);
	SubInodes.push_back(LinktoSub);

}

 



 

void sjh::vssd_Inode::PrintAllSub(sjh::vssd_disk& MyVssd, int pram, std::wstring now)//pram 1：tree  2：自己
{ 
	using namespace sjh;
	std::cout 
		<< " 驱动器 C 中的卷是 " << tools_vssd::WStringToString(MyVssd.GetName()) 
		<< "。\n 卷的序列号是 " << std::setfill('0') << std::setw(4) << std::setiosflags(std::ios::uppercase) << std::hex << (int)(&MyVssd) / 0x10000 << " - " << std::setfill('0') << std::setw(4) << std::hex << std::setiosflags(std::ios::uppercase) << (int)(&MyVssd) % 0x10000 
		<< "\n";
	
	int p = 0;
	 
	std::cout 
		<< "\n "<< tools_vssd::WStringToString(now) << " 的目录\n" 
		<< std::endl;
	std::cout
		<< tools_vssd::WStringToString(tools_vssd::GetTimeWString(GetCreateTime()))
		<< "    "
		<< std::setiosflags(std::ios::right) 
		<< "<" << tools_vssd::WStringToString(GetTypeName()) << ">"
		<< std::setfill(' ')  << std::setw(10) << " " 
		<< "." 
		<< std::endl; 
	std::cout
		<< tools_vssd::WStringToString(tools_vssd::GetTimeWString(GetFather()->GetCreateTime()))
		<< "    "
		<< std::setiosflags(std::ios::right)
		<< "<" << tools_vssd::WStringToString(GetFather()->GetTypeName()) << ">"
		<< std::setfill(' ')
		<< std::setw(10)
		<< " "
		<< ".."
		<< std::endl;


	for (size_t i = 0; i < SubInodes.size(); i++)
	{
		

	defeatInode:

		if (SubInodes.at(p) != NULL)
		{
			if(SubInodes.at(p)->IsFile())
			{
				std::cout
					<< tools_vssd::GetTimeString(SubInodes.at(p)->GetCreateTime())
					<< "    "
					<< std::setfill(' ') << std::setw(14) << tools_vssd::GetSizeString( SubInodes[p]->GetContent().size() * sizeof(unsigned char))
					<< " "<< tools_vssd::WStringToString(SubInodes.at(p)->GetName()) 
					<< std::endl;
			}
			else {
				std::cout
					<< tools_vssd::GetTimeString(SubInodes.at(p)->GetCreateTime()) << "    " 
					<< std::setiosflags(std::ios::right)
					<< "<" << tools_vssd::WStringToString(SubInodes[p]->GetTypeName()) << ">"
					<< std::setfill(' ') << std::setw(10) << " "
					<< tools_vssd::WStringToString(SubInodes.at(p)->GetName())
					<< std::endl;
			}
		}
		else
		{
			p++; goto defeatInode;
		}
		p++;
	}
	if (pram == 1) {
		for (size_t i = 0; i < SubInodes.size(); i++)
		{ 
			now.append(GetName());
			now.append(L"\\");
			SubInodes[i]->PrintAllSub(MyVssd,pram,now);
		}
	}

}

void sjh::vssd_Inode::DeleteOneSub(sjh::vssd_Inode * deletInode)
{
	size_t j = 0;
	for (size_t i = 0; i < SubInodes.size(); i++)
	{

		for (; j < SubInodes.max_size(); j++)
		{
			if (SubInodes.at(j) == NULL)
			{
				continue;
			}
			else
			{

				break;
			}
		}

		if (SubInodes.at(j)->GetName().compare(deletInode->GetName()) == IS_SAMESTRING)
		{
			SubInodes.at(j)->DeleteWholeTree();
			SubInodes.at(j)->~vssd_Inode();
			std::vector<sjh::vssd_Inode *>::iterator it = SubInodes.begin();

			SubInodes.erase(it + j);
			return;
		}
		else
		{
			j++;
		}

	}
}

void sjh::vssd_Inode::UnloadOneSub(sjh::vssd_Inode * deletInode)
{
	size_t j = 0;
	for (size_t i = 0; i < SubInodes.size(); i++)
	{

		for (; j < SubInodes.max_size(); j++)
		{
			if (SubInodes.at(j) == NULL)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		if (SubInodes.at(j)->GetName().compare(deletInode->GetName()) == IS_SAMESTRING)
		{
			std::vector<sjh::vssd_Inode*>::iterator it = SubInodes.begin();
			SubInodes.erase(it + j);
			return;
		}
		else
		{
			j++;
		}

	}
}

void sjh::vssd_Inode::DeleteWholeTree()
{
	size_t j = 0;
	for (size_t i = 0; i < SubInodes.size(); i++)
	{

		for (; j < SubInodes.max_size(); j++)
		{
			if (SubInodes.at(j) == NULL)
			{
				continue;
			}
			else
			{
				SubInodes.at(j)->DeleteWholeTree();
				SubInodes.at(j)->~vssd_Inode();
				break;
			}
		}


		j++;


	}
}



 

int sjh::vssd_Inode::FindSelfSubForFirst(std::wstring Inode, int StartIndex)
{  
	for (size_t i = StartIndex; i < SubInodes.size(); i++)
	{ 
		if (SubInodes.at(i) != NULL)
		{ 
			if (sjh::tools_vssd::WStringMatch(SubInodes.at(i)->GetName(), Inode) != 0)
			{ 
				return i;
			} 
			if (i > SubInodes.size())
			{
				break;
			}
		} 
	}
	return NOT_FINDED;
}

void sjh::vssd_Inode::FindSelfSubForAll(std::wstring Inode, std::vector<vssd_Inode*>& AllInode)
{ 
	 size_t Result = 0; 
	//循环体内语句控制循环的进行，非线性控制
	while (1)	
	{
		Result = FindSelfSubForFirst(Inode, Result);
		if (Result != NOT_FINDED)
		{
			AllInode.push_back(SubInodes[Result]);
			Result++;
		}
		else {
			break;
		}
	}
	return;
}

sjh::vssd_Inode * sjh::vssd_Inode::FindFolderByLink()
{
	vssd_Inode *Inode = this;
	while (Inode->IsLink())
	{
		Inode = Inode->SubInodes[0];
	}
	return Inode;
}

 
 

sjh::vssd_Inode *  sjh::vssd_Inode::GetFather()
{
	return Father;
}
void sjh::vssd_Inode::SetFather(vssd_Inode * aFather)
{
	Father = aFather;
}

void sjh::vssd_Inode::AddContent(wchar_t Byte)		//追加字符
{
	if (IsFile())
	{
		GetContent().push_back(Byte);
	}
	else
	{
		std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
	}
}
void sjh::vssd_Inode::SetContentString(std::wstring str)		//追加字符
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
		std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
	}
}
std::vector<sjh::vssd_Inode*>& sjh::vssd_Inode::GetSubInodes()
{
	return SubInodes;
}
void sjh::vssd_Inode::PrintContent()			//返回NULL 和 下一个字符
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
		std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
	}
}

int sjh::vssd_Inode::Serialize(std::vector<wchar_t>& Bytes)
{
	int Start = Bytes.size();
	sjh::tools_vssd::PushString(GetName(), Bytes);
	sjh::tools_vssd::PushLengthValue(InodeTypeCode, Bytes);
	sjh::tools_vssd::PushWcharVector(GetContent(), Bytes);
	sjh::tools_vssd::PushLengthValue(SubInodes.size(), Bytes);
	if (InodeTypeCode == IS_FOLDER) {
		for (size_t i = 0; i < SubInodes.size(); i++)
		{
			SubInodes.at(i)->Serialize(Bytes);
		}
	}
	return Start;
}
 
void sjh::vssd_Inode::DeSerialize(std::vector<wchar_t>& ByteVssd, int& Pos)
{
	SetName(tools_vssd::GetString(ByteVssd, Pos)); 
	InodeTypeCode = tools_vssd::GetLengthValue(ByteVssd, Pos);
	tools_vssd::GetWcharVector(GetContent(), ByteVssd, Pos);
	int SubSize = sjh::tools_vssd::GetLengthValue(ByteVssd, Pos);

	if (InodeTypeCode == IS_FOLDER) {
		for (int i = 0; i < SubSize; i++)
		{
			sjh::vssd_Inode *sub = new sjh::vssd_Inode(L"", IS_FOLDER);
			LoadOneSub(sub);
			sub->DeSerialize(ByteVssd, Pos);
		}
	}


} 
 
sjh::vssd_Inode::~vssd_Inode()
{
}
 
void sjh::vssd_Inode::Display()
{
	std::wcout << L"<vssd_Inode class>" << std::endl;
	std::wcout << L"\tName = " << Name << std::endl;
}
 
