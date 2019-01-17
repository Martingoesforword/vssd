#pragma once 
class vssd
{
private:
	std::string name;
	vssd_foldertop *nowtop;
	std::vector<vssd_foldertop *> tops;  
	vssd_folder *genius;
public: 
	vssd_foldertop *getnowtop();
	vssd_folder *getgenius();
	void setnowtop(vssd_foldertop * afoldertop);
	void linktop(vssd_foldertop *anowtop);
	vssd(vssd_foldertop * Now, vssd_folder * agenius, std::string aname);

	vssd();
	vssd_foldertop *findtop(std::string &aname);
	void puttorealfile(FILE *d);
	void getfromrealfile(FILE *d);

	void serialize(std::vector<unsigned char> &byte);
	~vssd();
};
 