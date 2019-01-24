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
	 
	
	if (SubFolders.size() < SubFolders.max_size()) {
		SubFolders.push_back(LinktoSub); 
		 
	}  
	else std::cout << "This folder had overflowed for Folders!" << std::endl;
}
 
std::wstring sjh::vssd_folder::GetName()
{
	return Name;
}

void sjh::vssd_folder::Build(sjh::vssd & MyVssd, sjh::tool_path &a) {
	 
	 
	sjh::vssd_folder *Now = this;
	int flag = 0;
	for (size_t i = 0; i < a.Folders.size(); i++)
	{	
		if (flag || !Now->FindForFirst(a.Folders[i])) {
			sjh::vssd_folder *f1 = new sjh::vssd_folder(a.Folders[i],1);
			Now->VssdFolderLink(f1);
			Now = f1;
			flag = 1;
		}
		else {
			Now = Now->FindForFirst(a.Folders[i]);
		}
		

	}

}

void sjh::vssd_folder::SetName(std::wstring &aName) {

	Name = aName;
}

 
//pram 1：tree  2：自己
void sjh::vssd_folder::ShowOffSub(int pram, std::wstring now) {
	 

	int p = 0; 
	std::cout<< sjh::vssd_tool::WStringToString(now) << "文件夾下：" << std::endl;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{
		
	defeatfolder:
		
		if (SubFolders.at(p) != NULL) {
			
			std::cout << sjh::vssd_tool::WStringToString(SubFolders.at(p)->Name) <<"\t\t<"<< sjh::vssd_tool::WStringToString(SubFolders [p]->GetType())<< ">\t" << SubFolders[p]->Content.size()* sizeof(unsigned char)<< "Byte\t"<< std::endl;
		}
		else { p++; goto defeatfolder;}
		p++;
	}
	if (pram == 1) {
		for (size_t i = 0; i < SubFolders.size(); i++)
		{
			SubFolders[i]->ShowOffSub(pram,now+ SubFolders[i]->Name+L"\\");
		}
		
	}
	 
}

void sjh::vssd_folder::DeletOne(sjh::vssd_folder * deletfolder)
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		for (; j < SubFolders.max_size(); j++)
		{
			if (SubFolders.at(j) == NULL) {
				continue;
			}
			else {

				break;
			}
		}

		if (SubFolders.at(j)->GetName().compare(deletfolder->GetName()) == 0) {
			SubFolders.at(j)->DeleteEvery();
			SubFolders.at(j)->~vssd_folder();
			std::vector<sjh::vssd_folder *>::iterator it = SubFolders.begin();
			 
			SubFolders.erase(it + j);
			return;
		}
		else {
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
			if (SubFolders.at(j) == NULL) {
				continue;
			}
			else { 
				break;
			}
		}

		if (SubFolders.at(j)->GetName().compare(deletfolder->GetName()) == 0) {
			std::vector<sjh::vssd_folder*>::iterator it = SubFolders.begin(); 
			SubFolders.erase(it + j); 
			return;
		}
		else {
			j++;
		}

	}
}

void sjh::vssd_folder::DeleteEvery() {
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{

		for (; j < SubFolders.max_size(); j++)
		{
			if (SubFolders.at(j) == NULL) {
				continue;
			}
			else {
				SubFolders.at(j)->DeleteEvery();
				SubFolders.at(j)->~vssd_folder();
				break;
			}
		}

		 
		j++;
		 

	}
}

 

sjh::vssd_folder ** sjh::vssd_folder::FindNext() {
	if (SubFolders.size() < SubFolders.max_size()) {
		for (size_t i = 0; i < SubFolders.max_size(); i++)
		{
			if (SubFolders.at(i) == nullptr) {
				return &SubFolders.at(i);
			}

		}
		return nullptr;
	}
	else {
		return nullptr;
	}
	
	 
}

sjh::vssd_folder * sjh::vssd_folder::FindForFirst(std::wstring & folder)
{
	size_t j = 0;
	for (size_t i = 0; i < SubFolders.size(); i++)
	{  
		 
		if (SubFolders.at(j) != NULL) {
			 
			if (SubFolders.at(j)->GetCheck() && sjh::vssd_tool::WStringMatch(SubFolders.at(j)->GetName(), folder) != 0) {

				return SubFolders.at(j);
			}
			else {
				j++;
			}
			if (j > SubFolders.max_size()) {
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

void sjh::vssd_folder::SetContent(unsigned char Byte)		//追加字符
{
	if (isFile()) {
		Content.push_back(Byte);
	}
	else {
		std::cout << "Can not write to or read From a folder or a Link" << std:: endl;
	}
}
void sjh::vssd_folder::SetContentString(std::wstring str)		//追加字符
{
	if (isFile()) {
		for (size_t i = 0; i < str.length(); i++)
		{
			Content.push_back(*((unsigned char*)&str[i] + 0));
			Content.push_back(*((unsigned char*)&str[i] + 1));
		}
		
	}
	else {
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}
void sjh::vssd_folder::PrintContent()			//返回NULL 和 下一个字符
{
	static int index = -1;
	if (isFile()) {
		for (size_t i = 0; i < Content.size(); i++)
		{
			std::cout << Content[i];
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "Can not write to or read From a folder or a Link" << std::endl;
	}
}

int sjh::vssd_folder::Serialize(std::vector<unsigned char>& Byte_foldertable, std::vector<unsigned char>& Byte_contenttable,int &indexInit)
{
	
	int p = Byte_foldertable.size();
	indexInit++;
	//存属性
	parmsave(Byte_foldertable, indexInit);
	//存文件内容
	contentsave(Byte_contenttable, indexInit);
	
	//预留4+子文件夹个数的空间
	vssd_tool::Push4BUint(SubFolders.size(), Byte_foldertable);
	vssd_tool::Push0ToNSpace(SubFolders.size() * 4, Byte_foldertable);
	
	//递归存
	for (size_t i = 0;VssdTypeCode != 2 && i < SubFolders.size(); i++)
	{ 
		int ps = SubFolders.at(i)->Serialize(Byte_foldertable, Byte_contenttable, indexInit);
		std::vector<unsigned char>::iterator it = Byte_foldertable.begin();
		it = it + p + 48 + i*4;
		vssd_tool::Set4BUint(it, ps+52); 
	}


	return p;

}
void sjh::vssd_folder::deSerialize(std::vector<unsigned char>& ByteVssd, int Pos)
{
	 
	vssd_tool::GetString(ByteVssd, Pos, 32, Name);   Pos += 32; 
	vssd_tool::Get4BUint(ByteVssd, Pos, VssdTypeCode);   Pos += 4;

	
	if (VssdTypeCode != 0) {
		Pos += 4 * 2;  //跳过文件内容描述 
		unsigned int Subnum;
		vssd_tool::Get4BUint(ByteVssd, Pos, Subnum);    Pos += 4;
		for (size_t i = 0; i < Subnum; i++)
		{
			sjh::vssd_folder *f1 = new sjh::vssd_folder(L"", 0);
			VssdFolderLink(f1);
			unsigned int SubPos = 0;
			vssd_tool::Get4BUint(ByteVssd, Pos, SubPos);
			f1->deSerialize(ByteVssd, SubPos);
			Pos += 4;
		}
	}
	//连接content
	else {

		unsigned int contentlength = 0;
		vssd_tool::Get4BUint(ByteVssd, Pos, contentlength);  Pos += 4;
		unsigned int contentindex = 0;
		vssd_tool::Get4BUint(ByteVssd, Pos, contentindex);

		unsigned int contentpoint = 0;
		vssd_tool::Get4BUint(ByteVssd, 48, contentpoint);  //content指针

		int contentindexx = 0;
		for (int  i = 0; i < FILEMAXSIZE; i++)
		{
			 
			unsigned int contentindex1 = 0;
			vssd_tool::Get4BUint(ByteVssd, contentpoint, contentindex1);
			if (contentindex1 == contentindex) {
				//读文件
				std::wstring str1;
				vssd_tool::GetStringAnd0(ByteVssd, contentpoint+4, contentlength, str1);
				SetContentString(str1); 
				break;
			}
		}

		
	}


}
void sjh::vssd_folder::parmsave(std::vector<unsigned char>& Byte_foldertable,int index) 
{
	//需要32+4+4+4 = 44B
	 
	vssd_tool::PushString(Name, Byte_foldertable);
	vssd_tool::Push0ToNSpace(32-Name.length(), Byte_foldertable);

	vssd_tool::Push4BUint(VssdTypeCode, Byte_foldertable);

	vssd_tool::Push4BUint(Content.size(),Byte_foldertable);
	//内容指针（index）
	if (VssdTypeCode != 0) {
		vssd_tool::Push4BUint(0xffffffff, Byte_foldertable);
	} 
	else {
		vssd_tool::Push4BUint(index, Byte_foldertable);
	}


}
void sjh::vssd_folder::contentsave(std::vector<unsigned char>& Byte_contenttable, int index)
{
	if (VssdTypeCode != 0) return;


	
	vssd_tool::Push4BUint(index, Byte_contenttable);
	//需要4+4+content.size()长度 
	
 
	//存放内容
	for (size_t i = 0; i < Content.size(); i++)
	{
		Byte_contenttable.push_back(Content.at(i));
	}
 

}
void sjh::vssd_folder::DeleteLinks()
{
	for (size_t  i = 0; i < LinkFolders.size(); i++)
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
