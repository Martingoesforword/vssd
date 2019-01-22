#pragma once 
class vssd
{
private:
	std::string Name;
	vssd_foldertop *NowTop;
	std::vector<vssd_foldertop *> Tops;  
	
	vssd_folder *Genius;
public: 
	std::vector<unsigned char> Serial;
	vssd_foldertop *GetNowTop();
	vssd_folder *GetGenius();
	void SetNowTop(vssd_foldertop * afolderTop); 
	void LinkTop(vssd_foldertop *aNowTop);
	vssd(vssd_foldertop * Now, vssd_folder * aGenius, std::string aName);

	vssd();
	vssd_foldertop *FindTop(std::string &aName);
	void PutToRealFile(FILE *d);
	void GetFromRealfile(FILE *d);

	void DeSerialize(std::vector<unsigned char>& ByteVssd);

	void Serialize(std::vector<unsigned char> &Byte);
	~vssd();
};
 