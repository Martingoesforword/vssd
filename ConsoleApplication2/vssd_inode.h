#pragma once 


class vssd_Inode :public sjh::base_namedable, public  sjh::base_displayable, public sjh::base_serializable, public sjh::base_contentable,public sjh::base_timeable
{
private:  
	unsigned int InodeTypeCode;
	std::vector<vssd_Inode *> SubInodes; 
	vssd_Inode* Father;
public: 
	virtual void Display();
	virtual int  Serialize(std::vector<wchar_t>& aByte);
	virtual void DeSerialize(std::vector<wchar_t>& aByteVssd, int & aPos);
	 
	vssd_Inode(std::wstring aName, int aCode); 
	~vssd_Inode(); 
	
	

	//修改相关 
	void SetFather(vssd_Inode * aFather);
	void AddContent(wchar_t aByte);
	void LoadOneSub(vssd_Inode * aLinkToSub); 
	void UnloadOneSub(vssd_Inode * aOffInode); 
	void SetContentString(std::wstring aStr); 
	void DeleteWholeTree();
	void DeleteOneSub(vssd_Inode *aDeletInode); 
	
	//获取相关  
	vssd_Inode *				GetFather();
	std::wstring				GetTypeName();
	std::vector<vssd_Inode *>&	GetSubInodes();
	int							FindSelfSubForFirst(std::wstring Inode,int StartIndex); 
	void						FindSelfSubForAll(std::wstring Inode,std::vector<vssd_Inode *> & AllInode); 
	vssd_Inode *				FindFolderByLink();
	void						PrintContent();
	void						PrintAllSub(sjh::vssd_disk & MyVssd, int pram, std::wstring now);
	 
	
	//检查相关 
	bool IsFile() { return  InodeTypeCode == IS_FILE; }
	bool IsFolder() { return  InodeTypeCode == IS_FOLDER; }
	bool IsLink() { return  InodeTypeCode == IS_LINK; }
	  

	//文件类型相关 
	static const int IS_FILE = 0;
	static const int IS_FOLDER = 1;
	static const int IS_LINK = 2;
	static const std::wstring VssdTypeName[3];

	static const int NOT_FINDED = -1;
};
