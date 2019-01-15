
#include "pch.h"   

tool_path::tool_path()
{
	type = 1;
	foldersize = 100;
	folderlength = 0;
	realfolderlength = 0;
	realfoldersize = 100;
}

void tool_path::getpath(std::string apath, int atype)
{
	type = atype;
	foldersize = 100;
	folderlength = 0;
	realfolderlength = 0;
	realfoldersize = 100;
	pathtofolders(apath);
}
void tool_path::getrealpath(vssd_folder *apath)
{
	realfolders[realfolderlength++] = apath;
}
void tool_path::testprint()
{
	for (int i = 0; i < folderlength; i++)
	{
		std::cout << folders[i] << std::endl;
	}
}


void tool_path::pathtofolders(std::string path)
{
									   


	//��·��׼��Ϊfolders����ֵ��folders
	std::string::size_type pos = 0;
	std::string::size_type beforepos = 0;
	std::string nowstring;
	while (folderlength <= foldersize && pos != std::string::npos) {
		if ((pos = path.find('\\', beforepos)) != std::string::npos) {
			if (pos != 0 && beforepos <= pos - 1) {
				//�ҵ�beforepos+1��pos-1���ַ�������folders����������ļ�¼
				nowstring = path.substr(beforepos, pos - beforepos);
				if (nowstring != "." && nowstring != "..") {
					vssd_tool::trim(&nowstring);
					folders[folderlength++] = nowstring;
				}
				else if (nowstring == ".." &&folderlength > 0 && folders[folderlength - 1] != "..") {
					folderlength--;
				}
				else if (nowstring == "..") {
					vssd_tool::trim(&nowstring);
					folders[folderlength++] = nowstring;
				}

			}
		}
		else if ((pos = path.find('/', beforepos)) != std::string::npos) {
			if (pos != 0 && beforepos <= pos - 1) {
				//�ҵ�beforepos+1��pos-1���ַ�������folders����������ļ�¼
				nowstring = path.substr(beforepos, pos - beforepos);

				if (nowstring != "." && nowstring != "..") {
					vssd_tool::trim(&nowstring);
					folders[folderlength++] = nowstring;
				}
				else if (nowstring == ".." && folders[folderlength - 1] != "..") {
					folderlength--;
				}
			}
		}
		if (pos != std::string::npos)
			beforepos = pos + 1;
	}
	if (beforepos <= path.length() - 1) {
		nowstring = path.substr(beforepos, path.length() - beforepos);
		vssd_tool::trim(&nowstring);
		if (nowstring != "." && nowstring != "..") {
			vssd_tool::trim(&nowstring);
			folders[folderlength++] = nowstring;
		}
		else if (nowstring == ".." && folders[folderlength - 1] != "..") {
			folderlength--;
		}

	}



}
void tool_path::deletone() {
	folderlength--;
	realfolderlength--;

}
void tool_path::addone(vssd_folder *folder) {
	folders[folderlength++] = folder->getname();
	realfolders[realfolderlength++] = folder;
}

tool_path::~tool_path()
{

}
