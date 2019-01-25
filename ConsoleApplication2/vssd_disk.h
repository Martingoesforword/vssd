#pragma once 
class vssd_disk
{
private:
	std::wstring Name;
	sjh::vssd_pan *NowTop;
	std::vector<sjh::vssd_pan *> Tops;
	
	sjh::vssd_folder *Genius;
public: 
	std::vector<unsigned char> Serial;
	sjh::vssd_pan *GetNowTop();
	sjh::vssd_folder *GetGenius();
	void SetNowTop(sjh::vssd_pan * afolderTop);
	void LinkTop(sjh::vssd_pan *aNowTop);
	vssd_disk(sjh::vssd_pan * Now, sjh::vssd_folder * aGenius, std::wstring aName);

	vssd_disk();
	sjh::vssd_pan *FindTop(std::wstring &aName);
	void PutToRealFile(FILE *d);
	void GetFromRealfile(FILE *d);

	void DeSerialize(std::vector<unsigned char>& ByteVssd);

	void Serialize(std::vector<unsigned char> &Byte);
	~vssd_disk();
};
 