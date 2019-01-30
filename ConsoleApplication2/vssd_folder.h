#pragma once 


class vssd_folder :public sjh::base_namedable, public  sjh::base_displayable, public sjh::base_serializable, public sjh::base_contentable
{
private:  
	std::time_t CreateTime;
	unsigned int FolderTypeCode;
	std::vector<vssd_folder *> SubFolders;

public: 
	virtual void Display();
	virtual int  Serialize(std::vector<wchar_t>& aByte);
	virtual void DeSerialize(std::vector<wchar_t>& aByteVssd, int & aPos);
	 
	vssd_folder(std::wstring aName, int aCode); 
	~vssd_folder(); 
	
	//修改相关 
	void AddContent(wchar_t aByte);
	void AddOneSub(vssd_folder * aLinkToSub); 
	void UnloadOneSub(vssd_folder * aOffFolder); 
	void SetContentString(std::wstring aStr); 
	void DeleteWholeTree();
	void DeleteOneSub(vssd_folder *aDeletFolder);
	sjh::vssd_folder* BuildPath(sjh::vssd_disk & aMyVssd, sjh::tool_path & aPath, int aType);


	
	//获取相关  
	std::wstring				GetTypeName();
	std::vector<vssd_folder *>& GetSubFolders();
	vssd_folder *				FindForFirst(std::wstring Folder);//搜索本目录下文件
	vssd_folder *				FindTree(sjh::tool_path * apath, int pathPos);//搜索本目录下包括子目录文件 
	void						PrintContent();
	void						PrintAllSub(sjh::vssd_disk & MyVssd, int pram, std::wstring now);
	 
	
	//检查相关 
	bool IsFile() { return  FolderTypeCode == IS_FILE; }
	bool IsFolder() { return  FolderTypeCode == IS_FOLDER; }
	bool IsLink() { return  FolderTypeCode == IS_LINK; }
	  

	//文件类型相关 
	static const int IS_FILE = 0;
	static const int IS_FOLDER = 1;
	static const int IS_LINK = 2;
	static const std::wstring VssdTypeName[3];
};
