#pragma once 
class vssd_disk:public sjh::base_namedable, public  sjh::base_displayable, public sjh::base_serializable
{
private: 
	sjh::vssd_pan *NowPan; 
	sjh::vssd_folder *Genius; 
	std::vector<sjh::vssd_pan *> Pans;  
public: 
	static sjh::vssd_disk* CreatVssd();
	vssd_disk(sjh::vssd_pan * Now, sjh::vssd_folder * aGenius, std::wstring aName);
	~vssd_disk();
	virtual void Display();
	virtual size_t Serialize(std::vector<wchar_t>& ByteVssd);
	virtual void DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);


	sjh::vssd_pan *GetNooowPan();
	void SetNooowPan(sjh::vssd_pan * afolderTop);
	void AddNewPan(sjh::vssd_pan *aNowTop); 
	sjh::vssd_folder *GetGenius();  
	sjh::vssd_pan *FindPanFromName(std::wstring &aName);
	  

	void PutToRealFile(std::wstring JumpTo, std::vector<wchar_t> aSerial);
	void GetFromRealfile(std::wstring GetFrom, std::vector<wchar_t> aSerial);
};
 