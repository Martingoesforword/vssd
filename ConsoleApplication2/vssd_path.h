#pragma once 


class tool_path
{ 
private:
	int Type;		//2��� 1���ԣ�genius��ͷ�� 
public: 
	

	std::vector<std::wstring> Folders;
	std::vector<sjh::vssd_folder *> RealFolders;

	tool_path();
	void DeletOne();
	void AddOne(sjh::vssd_folder * folder);
	void PathToFolders(std::wstring path); //·���ַ�����·������
	std::wstring FoldersToPath();
	 
	
	void GetPath(std::wstring path, int Type);
	void SetRealpath(sjh::vssd_folder * apath,int Pos);
	void TestPrint();
	bool include(tool_path & path1);			//δ���
	sjh::vssd_folder *GetNowFather();
	sjh::vssd_folder *GetNow();
	~tool_path();
}; 
