#pragma once 
class vssd_disk
{
private:
	std::wstring Name;
	sjh::vssd_pan *NowTop; 
	sjh::vssd_folder *Genius; 
	std::vector<sjh::vssd_pan *> Tops; 

public: 
	std::vector<wchar_t> Serial;

	std::wstring GetName();
	sjh::vssd_pan *GetNowTop();
	sjh::vssd_folder *GetGenius();

	sjh::vssd_pan *FindTop(std::wstring &aName);
	void SetNowTop(sjh::vssd_pan * afolderTop);
	void LinkTop(sjh::vssd_pan *aNowTop);

	void PutToRealFile(std::wstring JumpTo);
	void GetFromRealfile(std::wstring GetFrom);
	void DeSerialize(std::vector<wchar_t>& ByteVssd); 
	void Serialize(std::vector<wchar_t> &Byte);

	static sjh::vssd_disk* CreatVssd();
	vssd_disk(sjh::vssd_pan * Now, sjh::vssd_folder * aGenius, std::wstring aName);
	vssd_disk();
	~vssd_disk();
};
 