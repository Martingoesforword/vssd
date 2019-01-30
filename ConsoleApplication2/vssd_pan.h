#pragma once 
class vssd_pan :public sjh::base_serializable, public sjh::base_timeable
{
private:
	sjh::tool_path NowPath;
	sjh::vssd_Inode* root;
	
public: 
	vssd_pan(sjh::vssd_Inode* root, sjh::vssd_Inode * Genius);
	~vssd_pan();

	virtual void Display();
	virtual int Serialize(std::vector<wchar_t> &Byte_Toptable);
	virtual void DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);

	sjh::vssd_Inode*	GetRoot();
	sjh::tool_path&		GetNowPath();
	sjh::vssd_Inode*	GetNooowPos(); 

	void PrintNowPathForCmd(); 
	void PrintNowPath(); 

	
	


}; 
