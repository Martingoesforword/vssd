#pragma once 


class tool_path
{ 
private:
	int TypeCode;	 
public: 
	 
	std::vector<std::wstring> Folders;
	std::vector<sjh::vssd_folder *> RealFolders;

	tool_path();
	void DeletOne();
	void AddOne(sjh::vssd_folder * folder);
	void PathToFolders(std::wstring path); //·���ַ�����·������
	std::wstring FoldersToPath();
	 
	
	void GetPath(std::wstring path, int TypeCode);
	void SetRealpath(sjh::vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//δ���
	sjh::vssd_folder *GetNowFather();
	sjh::vssd_folder *GetNow();
	~tool_path();



	static const int IS_ABSOLUTE_PATH = 1;
	static const int IS_RELATIVE_PATH = 2;
}; 
