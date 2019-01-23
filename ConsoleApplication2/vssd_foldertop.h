#pragma once 
class vssd_foldertop
{
private:
	
public:
	tool_path NowPath; 
	vssd_folder* root;
	vssd_folder* GetNowPos();  
	void ShowNowPosForCmd();
	void ShowNowPos();
	vssd_foldertop(vssd_folder* root, vssd_folder * Genius);
	void SetNewRoot(vssd_folder* root);
	vssd_folder* Find(tool_path &apath);
	void Serialize(std::vector<unsigned char> &Byte_Toptable);



	~vssd_foldertop();
}; 
