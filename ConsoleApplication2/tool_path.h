#pragma once 


class tool_path
{ 

public: 
	int Type;		//2相对 1绝对（root开头） 
	void PathToFolders(std::string path); //路径字符串到路径对象
	std::string FoldersToPath();
	std::vector<std::string> Folders; 
	std::vector<vssd_folder *>RealFolders; 
	void DeletOne();
	void AddOne(vssd_folder * folder); 
	tool_path();
	void GetPath(std::string path, int Type);
	void SetRealpath(vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//未完成
	vssd_folder *GetNowFather();
	vssd_folder *GetNow();
	~tool_path();
}; 
