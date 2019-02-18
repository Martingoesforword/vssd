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
		//ԭʼ����
		VirtualDisk(vssd_pan * aNow, vssd_inode * aGenius, std::wstring aName);
		~VirtualDisk(); 

		//�������
		virtual void	Display();
		virtual size_t  Serialize(std::vector<wchar_t>& aByteVssd);
		virtual void	DeSerialize(std::vector<wchar_t>& aByteVssd, int &aPos);

		//NowPan���
		void	SetNooowPan(vssd_pan * aInodeTop);

		//Genius��� 
		vssd_inode *	GetGenius() const;
		vssd_inode *	BuildPath(vssd_inode *NowFolder, tools_path & aPath, int aType);  
		
		//Pans���
		vssd_pan *		GetNooowPan() const;
		void			AddNewPan(vssd_pan *aNowTop);
		vssd_pan *		FindPanFromName(const std::wstring &aName);

		//Name���
		void				SetName(std::wstring aName);
		const std::wstring&	GetName();

		//Time���

	};
}