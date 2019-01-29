#pragma once 
class vssd_pan :public sjh::base_serializable
{
private:
	sjh::tool_path NowPath;
	sjh::vssd_folder* root;
	
public: 
	sjh::vssd_folder*	GetRoot();
	sjh::tool_path&		GetNowPath();
	sjh::vssd_folder*	GetNooowPos();
	
	sjh::vssd_folder* FindForFirst(sjh::tool_path &apath);

	void ShowNowPathForCmd(); 
	void PrintNowPath(); 

	virtual int Serialize(std::vector<wchar_t> &Byte_Toptable);
	virtual void DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);
	vssd_pan(sjh::vssd_folder* root, sjh::vssd_folder * Genius);
	~vssd_pan();

	virtual void Display();
}; 
