#pragma once    

#include "pch.h"  
#include "tools_vssd.h"
#include "base_namedable.h"
#include "base_displayable.h"
#include "base_serializable.h"
#include "base_timeable.h"  

#include "tools_path.h"
#include "vssd_pan.h" 
#include "vssd_inode.h" 
#include "vssd_optcmd.h" 


namespace sjh {
	
	class VirtualDisk :public base_namedable, public base_displayable, public base_serializable, public base_timeable
	{
	private:
		vssd_pan *NowPan;
		vssd_inode *Genius;
		std::vector <vssd_pan *> Pans; 
		
	public:
		
		VirtualDisk(vssd_pan * aNow, vssd_inode * aGenius, std::wstring aName);
		~VirtualDisk();
		

		virtual void	Display();
		virtual size_t  Serialize(std::vector<wchar_t>& aByteVssd);
		virtual void	DeSerialize(std::vector<wchar_t>& aByteVssd, int &aPos);

		//修改相关
		void SetNooowPan(vssd_pan * aInodeTop);
		void AddNewPan(vssd_pan *aNowTop);
		vssd_inode * BuildPath(vssd_inode *NowFolder, tools_path & aPath, int aType);
		//获取相关 
		vssd_pan *			FindPanFromName(std::wstring &aName);
		vssd_pan *			GetNooowPan();
		vssd_inode *		GetGenius(); 
	};
}