#pragma once 


class tool_path :public sjh::base_serializable
{ 
private:
	int PathTypeCode = 0;	 
public: 
	tool_path();
	~tool_path();

	virtual int	Serialize(std::vector<wchar_t> &Byte_Toptable);
	virtual void DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);
	 

	std::vector<std::wstring> Inodes;
	std::vector<sjh::vssd_Inode *> RealInodes;

	int					GetTypeCode();
	std::wstring		GetPathWstring();
	sjh::vssd_Inode *	GetNow();

	void LoadOneSub(sjh::vssd_Inode * Inode);
	void SetInodesByWstring(std::wstring pathString); //路径字符串到路径对象  
	void DeleteOneSub();
	void Clear(); 


	bool IsAbsolutePath() { return PathTypeCode == IS_ABSOLUTE_PATH; } 
	bool IsRelativePath() { return PathTypeCode == IS_RELATIVE_PATH; } 
	static const int IS_ABSOLUTE_PATH = 1;
	static const int IS_RELATIVE_PATH = 2;
}; 
