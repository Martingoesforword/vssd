#pragma once 


class vssd_folder  
{
private:
	
	bool mycheck = true;

public: 
	std::wstring Name ; 
	std::vector<vssd_folder *>SubFolders;   
	std::vector<vssd_folder *>LinkFolders;
	 
	virtual std::wstring GetType();
	vssd_folder(std::wstring Name, int Code); 
	void VssdFolderLink(vssd_folder * LinkToSub);
	std::wstring GetName();
	void Build(vssd_disk & MyVssd, tool_path & a); 
	void VssdFolderInit();     
	void ShowOffSub(int pram, std::wstring now);
	void DeletOne(vssd_folder *DeletFolder);
	void OffOne(vssd_folder * DeletFolder);
	void DeleteEvery(); 
	void SetName(std::wstring &Name); 
	vssd_folder ** FindNext(); 
	vssd_folder *FindForFirst(std::wstring &Folder);//搜索本目录下文件
	vssd_folder *Find(tool_path * apath,int pathPos);//搜索本目录下包括子目录文件
	std::wstring VssdTypeName[3] = { L"FILE",L"FOLDER", L"LINK" };
	unsigned int VssdTypeCode;    //0 file 1 folder 2 Link
	std::vector<unsigned char> Content;		//文件内容 
	bool isFile();
	void SetContent(unsigned char Byte);
	void SetContentString(std::wstring str);
	void PrintContent(); 
	int Serialize(std::vector<unsigned char>& Byte_foldertable, std::vector<unsigned char>& Byte_contenttable, int & indexInit);
	void deSerialize(std::vector<unsigned char>& ByteVssd, int Pos);
	void parmsave(std::vector<unsigned char>& Byte_foldertable, int a);
	void contentsave(std::vector<unsigned char>& Byte_foldertable, int a);
	void DeleteLinks();
	void AddLink(sjh::vssd_folder * link);
	~vssd_folder();
	void SetCheck();
	bool GetCheck();
	void BackCheck();
};
