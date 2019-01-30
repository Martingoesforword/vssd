#pragma once 
class vssd_disk:public sjh::base_namedable, public sjh::base_displayable, public sjh::base_serializable,public sjh::base_timeable
{
private: 
	sjh::vssd_pan *NowPan; 
	sjh::vssd_Inode *Genius; 
	std::vector<sjh::vssd_pan *> Pans; 

public:  
	vssd_disk(sjh::vssd_pan * aNow, sjh::vssd_Inode * aGenius, std::wstring aName);
	~vssd_disk();

	virtual void Display(); 
	virtual int  Serialize(std::vector<wchar_t>& aByteVssd);
	virtual void DeSerialize(std::vector<wchar_t>& aByteVssd, int &aPos);  

	//修改相关
	void SetNooowPan(sjh::vssd_pan * aInodeTop);
	void AddNewPan(sjh::vssd_pan *aNowTop);
	sjh::vssd_Inode * BuildPath(sjh::vssd_Inode *NowFolder , sjh::tool_path & aPath, int aType);
	//获取相关 
	sjh::vssd_pan *			FindPanFromName(std::wstring &aName);
	sjh::vssd_pan *			GetNooowPan();
	sjh::vssd_Inode *		GetGenius();
	static sjh::vssd_disk*	CreateVssd();		//工厂函数

	
}; 