#pragma once 
class vssd_disk:public sjh::base_namedable, public sjh::base_displayable, public sjh::base_serializable
{
private: 
	sjh::vssd_pan *NowPan; 
	sjh::vssd_folder *Genius; 
	std::vector<sjh::vssd_pan *> Pans;  
public: 
	static sjh::vssd_disk* CreatVssd();		//¹¤³§º¯Êý
	vssd_disk(sjh::vssd_pan * aNow, sjh::vssd_folder * aGenius, std::wstring aName);
	~vssd_disk();
	virtual void Display();
	virtual int Serialize(std::vector<wchar_t>& aByteVssd);
	virtual void DeSerialize(std::vector<wchar_t>& aByteVssd, int &aPos);
	 
	sjh::vssd_pan *		GetNooowPan();
	sjh::vssd_folder *	GetGenius();
	void SetNooowPan(sjh::vssd_pan * afolderTop);
	void AddNewPan(sjh::vssd_pan *aNowTop); 
	
	sjh::vssd_pan *FindPanFromName(std::wstring &aName); 
	  
	void PutToRealFile(std::wstring aJumpTo, std::vector<wchar_t> aSerial);
	void GetFromRealfile(std::wstring aGetFrom, std::vector<wchar_t> aSerial);
}; 