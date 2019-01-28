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

	//��ʼ������ʾ���
	vssd_folder(std::wstring Name, int Code);
	void VssdFolderInit();      
	void ShowOffSub(sjh::vssd_disk & MyVssd, int pram, std::wstring now);
	void DeletOne(vssd_folder *DeletFolder);
	void OffOne(vssd_folder * DeletFolder);
	void DeleteEvery(); 
	void SetName(std::wstring &Name); 

	//Ѱ�ҽ������
	void Build(sjh::vssd_disk & MyVssd, sjh::tool_path & a);
	vssd_folder ** FindNext(); 
	vssd_folder *FindForFirst(std::wstring &Folder);//������Ŀ¼���ļ�
	vssd_folder *Find(sjh::tool_path * apath,int pathPos);//������Ŀ¼�°�����Ŀ¼�ļ�
	
	//�ļ��������
	std::vector<wchar_t> Content;		
	bool isFile();
	void SetContent(wchar_t Byte); 
	void SetContentString(std::wstring str);
	void PrintContent();  
	
	//���л����
	int  Serialize(std::vector<wchar_t>& Byte);
	void deSerialize(std::vector<wchar_t>& ByteVssd, int Pos); 

	//�������
	void DeleteLinks();
	void AddLink(sjh::vssd_folder * link);
	~vssd_folder();

	//������
	void SetCheck();
	bool GetCheck();
	void BackCheck();

	//�ļ��������
	static const int IS_FILE = 0;
	static const int IS_FOLDER = 1;
	static const int IS_LINK = 2;
	const std::wstring VssdTypeName[3] = { L"FILE",L"DIR", L"SYMLINKD" };
	unsigned int VssdTypeCode;
	
};
