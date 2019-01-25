#pragma once 


class tool_path
{ 
private:
	int Type;		//2相对 1绝对（genius开头） 
public: 
	

	std::vector<std::wstring> Folders;
	std::vector<vssd_folder *> RealFolders;

	tool_path();
	void DeletOne();
	void AddOne(vssd_folder * folder);
	void PathToFolders(std::wstring path); //路径字符串到路径对象
	std::wstring FoldersToPath();
	 
	
	void GetPath(std::wstring path, int Type);
	void SetRealpath(vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//未完成
	vssd_folder *GetNowFather();
	vssd_folder *GetNow();
	~tool_path();
}; 
