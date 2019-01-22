
#include "pch.h"   

sjh::tool_path::tool_path()
{
	Type = 1;   
}

void sjh::tool_path::GetPath(std::string apath, int aType)
{
	Type = aType;   
	PathToFolders(apath);
}
void sjh::tool_path::SetRealpath(vssd_folder *apath, int Pos)
{
	 
	RealFolders.push_back(apath);
}
void sjh::tool_path::TestPrint()
{
	for (int i = 0; i < Folders.size(); i++)
	{
		std::cout << Folders.at(i)<< std::endl;
	}
}

bool sjh::tool_path::include(sjh::tool_path & path1)
{
	for (int i = 1; i < path1.Folders.size(); i++)
	{
		if (path1.Folders.at(i)== Folders[i]) continue;
		else {
			if (path1.Folders.size() == Folders.size()) {
				return 0;
			}
		}
	}
}

sjh::vssd_folder * sjh::tool_path::GetNowFather()
{
	return RealFolders.at(RealFolders.size() - 2); 
}

sjh::vssd_folder * sjh::tool_path::GetNow()
{
	return RealFolders.at(RealFolders.size() - 1);
}


void sjh::tool_path::PathToFolders(std::string path)
{
									   
	 

	//将路径准换为Folders并赋值给Folders
	int Pos = 0;
	int beForePos = 0;
	std::string Nowstring;
	while (Folders.size() <= Folders.max_size() && Pos != std::string::npos) {
		if ((Pos = path.find('\\', beForePos)) != std::string::npos) {
			if (Pos != 0 && beForePos <= Pos - 1) {
				//找到beForePos+1到Pos-1的字符串放入Folders数组里，并更改记录
				Nowstring = path.substr(beForePos, Pos - beForePos);
				if (Nowstring != "." && Nowstring != "..") {
					vssd_tool::Trim(&Nowstring);
					Folders.push_back(Nowstring) ; 
				}
				else if (Nowstring == ".." &&Folders.size() > 0 && Folders.at(Folders.size() - 1)!= "..") {
					Folders.pop_back();
				}
				else if (Nowstring == "..") {
					vssd_tool::Trim(&Nowstring);
					Folders.push_back(Nowstring); 
				}

			}
		}
		else if ((Pos = path.find('/', beForePos)) != std::string::npos) {
			if (Pos != 0 && beForePos <= Pos - 1) {
				//找到beForePos+1到Pos-1的字符串放入Folders数组里，并更改记录
				Nowstring = path.substr(beForePos, Pos - beForePos);

				if (Nowstring != "." && Nowstring != "..") {
					vssd_tool::Trim(&Nowstring);
					Folders.push_back(Nowstring); 
				}
				else if (Nowstring == ".." && Folders.at(Folders.size() - 1)!= "..") {
					Folders.pop_back();
				}
			}
		}
		if (Pos != std::string::npos)
			beForePos = Pos + 1;
	}
	if (beForePos <= path.length() - 1) {
		Nowstring = path.substr(beForePos, path.length() - beForePos);
		vssd_tool::Trim(&Nowstring);
		if (Nowstring != "." && Nowstring != "..") {
			vssd_tool::Trim(&Nowstring);
			Folders.push_back(Nowstring); 
		}
		else if (Nowstring == ".." &&Folders.size()>1&& Folders.at(Folders.size() - 1)!= "..") {
			Folders.pop_back();
		}
		else if (Nowstring == "..") {
			Folders.push_back(".."); 
		}

	}



}
void sjh::tool_path::DeletOne() {
	Folders.pop_back();
	RealFolders.pop_back(); 

}
void sjh::tool_path::AddOne(vssd_folder *folder) {
	Folders.push_back(folder->GetName()); 
	RealFolders.push_back(folder); 
	
}

sjh::tool_path::~tool_path()
{

}
