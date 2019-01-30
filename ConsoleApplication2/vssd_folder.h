#pragma once 


class vssd_folder :public sjh::base_namedable, public  sjh::base_displayable, public sjh::base_serializable, public sjh::base_contentable
{
private:  
	unsigned int FolderTypeCode;
	std::vector<vssd_folder *> SubFolders;

public: 
	virtual void Display();
	virtual int  Serialize(std::vector<wchar_t>& Byte);
	virtual void DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos);
	 
	vssd_folder(std::wstring Name, int Code); 
	~vssd_folder(); 
	
	//�޸���� 
	void AddContent(wchar_t Byte);
	void AddOneSub(vssd_folder * LinkToSub); 
	void UnloadOneSub(vssd_folder * OffFolder); 
	void SetContentString(std::wstring str); 
	void DeleteWholeTree();
	void DeleteOneSub(vssd_folder *DeletFolder);
	sjh::vssd_folder* BuildPath(sjh::vssd_disk & MyVssd, sjh::tool_path & Path, int Type);


	
	//��ȡ���  
	std::wstring				GetTypeName();
	std::vector<vssd_folder *>& GetSubFolders();
	vssd_folder *				FindForFirst(std::wstring Folder);//������Ŀ¼���ļ�
	vssd_folder *				FindTree(sjh::tool_path * apath, int pathPos);//������Ŀ¼�°�����Ŀ¼�ļ� 
	void						PrintContent();
	void						PrintAllSub(sjh::vssd_disk & MyVssd, int pram, std::wstring now);
	 
	
	//������ 
	bool IsFile() { return  FolderTypeCode == IS_FILE; }
	bool IsFolder() { return  FolderTypeCode == IS_FOLDER; }
	bool IsLink() { return  FolderTypeCode == IS_LINK; }
	  

	//�ļ�������� 
	static const int IS_FILE = 0;
	static const int IS_FOLDER = 1;
	static const int IS_LINK = 2;
	static const std::wstring VssdTypeName[3];
};
