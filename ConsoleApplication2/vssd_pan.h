#pragma once 
class vssd_pan
{
private:
	
public:
	sjh::tool_path NowPath;
	sjh::vssd_folder* root;
	sjh::vssd_folder* GetNowPos();
	void ShowNowPosForCmd();
	void ShowNowPos();
	vssd_pan(sjh::vssd_folder* root, sjh::vssd_folder * Genius);
	void SetNewRoot(sjh::vssd_folder* root);
	sjh::vssd_folder* FindForFirst(sjh::tool_path &apath);
	void Serialize(std::vector<unsigned char> &Byte_Toptable);



	~vssd_pan();
}; 
