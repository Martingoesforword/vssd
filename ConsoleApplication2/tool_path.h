#pragma once 


class tool_path
{ 

public: 
	int Type;		//2��� 1���ԣ�root��ͷ�� 
	void PathToFolders(std::wstring path); //·���ַ�����·������
	std::wstring FoldersToPath();
	std::vector<std::wstring> Folders; 
	std::vector<vssd_folder *>RealFolders; 
	void DeletOne();
	void AddOne(vssd_folder * folder); 
	tool_path();
	void GetPath(std::wstring path, int Type);
	void SetRealpath(vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//δ���
	vssd_folder *GetNowFather();
	vssd_folder *GetNow();
	~tool_path();
}; 
