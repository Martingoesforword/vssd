#pragma once 


class tool_path
{ 

public: 
	int type;		//2��� 1���ԣ�root��ͷ�� 
	void pathtofolders(std::string path); //·���ַ�����·������
	 
	std::vector<std::string> folders; 
	std::vector<vssd_folder *>realfolders; 
	void deletone();
	void addone(vssd_folder * folder); 
	tool_path();
	void getpath(std::string path, int type);
	void setrealpath(vssd_folder * apath,int pos);
	void testprint();
	bool include(tool_path & path1);			//δ���
	vssd_folder *getnowfather();
	vssd_folder *getnow();
	~tool_path();
}; 
