#pragma once 


class tool_path
{ 

public: 
	int Type;		//2相对 1绝对（root开头） 
	void PathToFolders(std::wstring path); //路径字符串到路径对象
	std::wstring FoldersToPath();
	std::vector<std::wstring> Folders; 
	std::vector<vssd_folder *>RealFolders; 
	void DeletOne();
	void AddOne(vssd_folder * folder); 
	tool_path();
	void GetPath(std::wstring path, int Type);
	void SetRealpath(vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//未完成
	vssd_folder *GetNowFather();
	vssd_folder *GetNow();
	~tool_path();
}; 
