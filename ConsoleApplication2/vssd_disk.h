#pragma once    

#include "pch.h"  
#include "tools_vssd.h"
#include "vssd_name.h"
#include "base_displayable.h"
#include "base_serializable.h"
#include "vssd_time.h"  

#include "tools_path.h"
#include "vssd_pan.h" 
#include "vssd_inode.h" 
#include "vssd_optcmd.h" 


namespace sjh {
	
	class VirtualDisk : public base_displayable, public base_serializable 
	{
	private:
		vssd_pan *		NowPan;
		vssd_inode *	Genius;
		std::vector <vssd_pan *>	Pans;  
		vssd_name					Name; 
	public: 
		//原始构造
		VirtualDisk(vssd_pan * aNow, vssd_inode * aGenius, std::wstring aName);
		~VirtualDisk(); 

		//基类相关
		virtual void	Display();
		virtual size_t  Serialize(std::vector<wchar_t>& aByteVssd);
		virtual void	DeSerialize(std::vector<wchar_t>& aByteVssd, int &aPos);

		//NowPan相关
		void	SetNooowPan(vssd_pan * aInodeTop);

		//Genius相关 
		vssd_inode *	GetGenius() const;
		vssd_inode *	BuildPath(vssd_inode *NowFolder, tools_path & aPath, int aType);  
		
		//Pans相关
		vssd_pan *		GetNooowPan() const;
		void			AddNewPan(vssd_pan *aNowTop);
		vssd_pan *		FindPanFromName(const std::wstring &aName);

		//Name相关
		void				SetName(std::wstring aName);
		const std::wstring&	GetName();

		//Time相关

	};
}