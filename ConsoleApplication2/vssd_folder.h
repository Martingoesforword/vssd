#pragma once 
class vssd_folder :public vssd_canbelinked
{
private:
	
	 

public: 
	std::string name; 
	std::vector<vssd_folder *>subfolders;   
	 
	 
	virtual std::string gettype();
	vssd_folder(std::string name, int code); 
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
	vssd_folder *find(std::string &folder);//������Ŀ¼���ļ�
	vssd_folder *find(tool_path * apath,int pathpos);//������Ŀ¼�°�����Ŀ¼�ļ�
	std::string vssdtypename[3] = { "FILE","FOLDER", "LINK" };
	int vssdtypecode;    //0 file 1 folder 2 link
	std::vector<unsigned char> content;		//�ļ����� 
	bool isFile() {
		if (!vssdtypecode) return true;
		else return false;
	}
	void setcontent(unsigned char byte);
	unsigned char readcontent();
	~vssd_folder();
};
