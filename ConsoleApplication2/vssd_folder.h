#pragma once 


class vssd_folder  
{
private:
	
	 

public: 
	std::string Name ; 
	std::vector<vssd_folder *>SubFolders;   
	std::vector<vssd_folder *>LinkFolders;
	 
	virtual std::string GetType();
	vssd_folder(std::string Name, int Code); 
	void VssdFolderLink(vssd_folder * LinkToSub);
	std::string GetName();
	void Build(vssd & MyVssd, tool_path & a); 
	void VssdFolderInit();  
	void ShowOffSub();
	void DeletOne(vssd_folder *DeletFolder);
	void OffOne(vssd_folder * DeletFolder);
	void DeleteEvery(); 
	void SetName(std::string &Name); 
	vssd_folder ** FindNext(); 
	vssd_folder *Find(std::string &Folder);//搜索本目录下文件
	vssd_folder *Find(tool_path * apath,int pathPos);//搜索本目录下包括子目录文件
	std::string VssdTypeName[3] = { "FILE","FOLDER", "LINK" };
	unsigned int VssdTypeCode;    //0 file 1 folder 2 Link
	std::vector<unsigned char> Content;		//文件内容 
	bool isFile();
	void SetContent(unsigned char Byte);
	void SetContentString(std::string Str);
	unsigned char readcontent(); 
	int Serialize(std::vector<unsigned char>& Byte_foldertable, std::vector<unsigned char>& Byte_contenttable, int & indexInit);
	void deSerialize(std::vector<unsigned char>& ByteVssd, int Pos);
	void parmsave(std::vector<unsigned char>& Byte_foldertable, int a);
	void contentsave(std::vector<unsigned char>& Byte_foldertable, int a);
	void DeleteLinks();
	void AddLink(sjh::vssd_folder * link);
	~vssd_folder();
};
