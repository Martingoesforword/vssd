#pragma once
class tool_vcmd
{
private:

public:
	static void comein(vssd & myvssd, std::string &command); 
	static void vdir(vssd_foldertop* top);
	static void vrd(vssd & myvssd, std::string & dircommand);
	static void vdir(vssd & myvssd, std::string & dircommand);
	static void vcd(vssd & myvssd, std::string & command);
	static void vmd(vssd & myvssd, std::string & command); //����Ŀǰ�ļ��л��߸��ݾ���·������
	static void vcd(vssd_foldertop* top);
	static void vrd(vssd & myvssd); 
	static void vren(vssd & myvssd, std::string & command);
	static void vren(vssd & myvssd, tool_path & srccommand, std::string & discommand);
	static void vcls();
	static void vjump(vssd & myvssd, std::string & jumpto);
	static void vmove(vssd & myvssd, tool_path & dispath);
	
	tool_vcmd();
	~tool_vcmd();
};

