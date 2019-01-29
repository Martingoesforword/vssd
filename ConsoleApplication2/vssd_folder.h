#pragma once 


class vssd_folder :public sjh::base_namedable,sjh::base_displayable,sjh::base_serializable
{
private: 
	bool mycheck = true;  
	unsigned int VssdTypeCode;
public: 
	void VssdFolderInit();
	vssd_folder(std::wstring Name, int Code);


	std::vector<vssd_folder *>SubFolders; 
	std::vector<vssd_folder *>LinkFolders;  

	std::wstring GetType();
	int GetTypeCode();

	void LinkNewFolder(vssd_folder * LinkToSub); 

	//初始化加显示相关

	
	     
	
	void DeleteOne(vssd_folder *DeletFolder);
	void OffOne(vssd_folder * DeletFolder);
	void DeleteEvery();  
	//寻找建立相关
	sjh::vssd_folder* Build(sjh::vssd_disk & MyVssd, sjh::tool_path & a);
	vssd_folder ** FindNext(); 
	vssd_folder *FindForFirst(std::wstring &Folder);//搜索本目录下文件
	vssd_folder *Find(sjh::tool_path * apath,int pathPos);//搜索本目录下包括子目录文件
	
	//文件内容相关
	std::vector<wchar_t> Content;		
	bool isFile();
	void SetContent(wchar_t Byte); 
	void SetContentString(std::wstring str);
	void PrintContent();  
	 
	
	void ShowOffSub(sjh::vssd_disk & MyVssd, int pram, std::wstring now);

	

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
	static const std::wstring VssdTypeName[3];

	
	virtual void Display();
	virtual size_t Serialize(std::vector<wchar_t>& Byte);  
	virtual  void DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos);
};
