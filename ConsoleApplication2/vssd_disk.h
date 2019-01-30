#pragma once 
class vssd_disk:public sjh::base_namedable, public sjh::base_displayable, public sjh::base_serializable
{
private: 
	sjh::vssd_pan *NowPan; 
	sjh::vssd_folder *Genius; 
	std::vector<sjh::vssd_pan *> Pans; 

public:  
	vssd_disk(sjh::vssd_pan * aNow, sjh::vssd_folder * aGenius, std::wstring aName);
	~vssd_disk();

	virtual void Display();
	virtual int  Serialize(std::vector<wchar_t>& aByteVssd);
	virtual void DeSerialize(std::vector<wchar_t>& aByteVssd, int &aPos);  

	//修改相关
	void SetNooowPan(sjh::vssd_pan * afolderTop);
	void AddNewPan(sjh::vssd_pan *aNowTop);

	//获取相关 
	sjh::vssd_pan *			FindPanFromName(std::wstring &aName);
	sjh::vssd_pan *			GetNooowPan();
	sjh::vssd_folder *		GetGenius();
	static sjh::vssd_disk*	CreateVssd();		//工厂函数

	
}; 