#pragma once
#include "pch.h"   
class vssd_foldertop
{
private:
	
public:
	tool_path nowpath; 
	vssd_folder* root;
	vssd_folder* getnowposition();  
	void shownowpositionforcmd();
	void shownowposition();
	vssd_foldertop(vssd_folder* root, vssd_folder * genius);
	void newroot(vssd_folder* root);
	vssd_folder* find(tool_path &apath);
	void serialize(std::vector<unsigned char> &byte_toptable);



	~vssd_foldertop();
}; 
