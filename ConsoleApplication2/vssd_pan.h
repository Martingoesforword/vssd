#pragma once 
class vssd_pan
{
private:
	
public:
	tool_path NowPath; 
	vssd_folder* root;
	vssd_folder* GetNowPos();  
	void ShowNowPosForCmd();
	void ShowNowPos();
	vssd_pan(vssd_folder* root, vssd_folder * Genius);
	void SetNewRoot(vssd_folder* root);
	vssd_folder* FindForFirst(tool_path &apath);
	void Serialize(std::vector<unsigned char> &Byte_Toptable);



	~vssd_pan();
}; 