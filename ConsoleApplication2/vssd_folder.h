#pragma once 


class vssd_folder  
{
private:
	
	bool mycheck = true;

public: 
	std::wstring Name; 
	std::vector<vssd_folder *>SubFolders;   
	std::vector<vssd_folder *>LinkFolders;
	 
	virtual std::wstring GetType();
	
	void VssdFolderLink(vssd_folder * LinkToSub);
	std::wstring GetName();

	//初始化加显示相关
	vssd_folder(std::wstring Name, int Code);
	void VssdFolderInit();      
	void ShowOffSub(sjh::vssd_disk & MyVssd, int pram, std::wstring now);
	void DeletOne(vssd_folder *DeletFolder);
	void OffOne(vssd_folder * DeletFolder);
	void DeleteEvery(); 
	void SetName(std::wstring &Name); 

	//寻找建立相关
	void Build(sjh::vssd_disk & MyVssd, sjh::tool_path & a);
	vssd_folder ** FindNext(); 
	vssd_folder *FindForFirst(std::wstring &Folder);//搜索本目录下文件
	vssd_folder *Find(sjh::tool_path * apath,int pathPos);//搜索本目录下包括子目录文件
	
	//文件内容相关
	std::vector<wchar_t> Content;		
	bool isFile();
	void SetContent(wchar_t Byte); 
	void SetContentString(std::wstring str);
	void PrintContent();  
	
	//序列化相关
	int  Serialize(std::vector<wchar_t>& Byte);
	void deSerialize(std::vector<wchar_t>& ByteVssd, int Pos); 

	//链接相关
	void DeleteLinks();
	void AddLink(sjh::vssd_folder * link);
	~vssd_folder();

	//检查相关
	void SetCheck();
	bool GetCheck();
	void BackCheck();

	//文件类型相关
	static const int IS_FILE = 0;
	static const int IS_FOLDER = 1;
	static const int IS_LINK = 2;
	const std::wstring VssdTypeName[3] = { L"FILE",L"DIR", L"SYMLINKD" };
	unsigned int VssdTypeCode;
	
};
