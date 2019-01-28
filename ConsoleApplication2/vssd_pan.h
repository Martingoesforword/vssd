#pragma once 
class vssd_pan
{
private:
	
public:
	sjh::tool_path NowPath;
	sjh::vssd_folder* root;
	
	
	sjh::vssd_folder* GetNowPos();
	sjh::vssd_folder* FindForFirst(sjh::tool_path &apath);

	void ShowNowPosForCmd();
	void ShowNowPos();

	void Serialize(std::vector<wchar_t> &Byte_Toptable);

	vssd_pan(sjh::vssd_folder* root, sjh::vssd_folder * Genius);
	~vssd_pan();
}; 
