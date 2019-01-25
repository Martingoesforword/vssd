#pragma once 
class vssd_disk
{
private:
	std::wstring Name;
	vssd_pan *NowTop;
	std::vector<vssd_pan *> Tops;  
	
	vssd_folder *Genius;
public: 
	std::vector<unsigned char> Serial;
	vssd_pan *GetNowTop();
	vssd_folder *GetGenius();
	void SetNowTop(vssd_pan * afolderTop); 
	void LinkTop(vssd_pan *aNowTop);
	vssd_disk(vssd_pan * Now, vssd_folder * aGenius, std::wstring aName);

	vssd_disk();
	vssd_pan *FindTop(std::wstring &aName);
	void PutToRealFile(FILE *d);
	void GetFromRealfile(FILE *d);

	void DeSerialize(std::vector<unsigned char>& ByteVssd);

	void Serialize(std::vector<unsigned char> &Byte);
	~vssd_disk();
};
 