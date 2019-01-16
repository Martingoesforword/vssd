#pragma once 
class vssd_folder :public vssd_canbelinked
{
private:
	
	 

public: 
	std::string name; 
	std::vector<vssd_folder *>subfolders;   
	 
	 
	virtual std::string gettype();
	vssd_folder(std::string name); 
	void vssd_folder_link(vssd_folder * linktosub);
	std::string getname();
	void build(tool_path & a); 
	void vssd_folder_init();  
	void showoffsub();
	void deletone(vssd_folder *deletfolder);
	void offone(vssd_folder * deletfolder);
	void deletevery(); 
	void setname(std::string &name); 
	vssd_folder ** findnext(); 
	vssd_folder *find(std::string &folder);//搜索本目录下文件
	vssd_folder *find(tool_path * apath,int pathpos);//搜索本目录下包括子目录文件
	std::string vssdtypename = "FOLDER";
	int vssdtypecode;    //0 file 1 folder 2 link
	~vssd_folder();
};
