#pragma once 
class vssd_tool {
public:
	static void trim(std::string * s) {

		if (!s->empty())
		{
			s->erase(0, s->find_first_not_of(" "));
			s->erase(s->find_last_not_of(" ") + 1);
		}

	}
	static void trim(std::string & s) {

		if (!s.empty())
		{
			s.erase(0, s.find_first_not_of(" "));
			s.erase(s.find_last_not_of(" ") + 1);
		}

	}
	//输入：四字节整形数据 一个字节型vector引用   目的：将四字节整形数据按大端放入引用中
	static void push(unsigned int uint4, std::vector<unsigned char> &byte) {
		 
		byte.push_back((uint4 >> 24) && 0x0FF);
		byte.push_back((uint4 >> 16) && 0x0FF);
		byte.push_back((uint4 >> 8) && 0x0FF);
		byte.push_back((uint4) && 0x0FF); 
		return;
	}
};
