#pragma once 


class tool_path
{ 
private:
	int PathTypeCode = 0;	 
public: 
	 
	std::vector<std::wstring> Folders;
	std::vector<sjh::vssd_folder *> RealFolders;

	tool_path();
	void DeleteOneSub();
	void AddOne(sjh::vssd_folder * folder);
	void WstringToFolders(std::wstring path); //路径字符串到路径对象
	std::wstring FoldersToPath();
	int GetTypeCode();
	
	void GetPath(std::wstring path, int PathTypeCode);
	void SetRealpath(sjh::vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//未完成
	sjh::vssd_folder *GetNowFather();
	sjh::vssd_folder *GetNow();
	~tool_path();
	bool IsAbsolutePath() { return PathTypeCode == IS_ABSOLUTE_PATH; } 
	bool IsRelativePath() { return PathTypeCode == IS_RELATIVE_PATH; }

	static const int IS_ABSOLUTE_PATH = 1;
	static const int IS_RELATIVE_PATH = 2;
}; 
