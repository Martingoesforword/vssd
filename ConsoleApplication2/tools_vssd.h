#pragma once 
class tools_vssd
{
public:
	static void split(std::wstring str, std::vector<std::wstring> &ret, std::wstring pattern)
	{

		if (pattern.empty())
		{
		}
		size_t start = 0, index = str.find_first_of(pattern, 0);
		while (index != str.npos)
		{
			if (start != index)
				ret.push_back(str.substr(start, index - start));
			start = index + 1;
			index = str.find_first_of(pattern, start);
		}
		if (!str.substr(start).empty())
			ret.push_back(str.substr(start));

	}
	static void Trim(std::wstring & s)
	{ 
		if (!s.empty())
		{
			s.erase(0, s.find_first_not_of(L" "));
			s.erase(s.find_last_not_of(L" ") + 1);
		} 
	} 
	static size_t PushLengthValue(unsigned int Uint4, std::vector<wchar_t> &Byte)
	{
		size_t Start= Byte.size();
		Byte.push_back((Uint4 >> 16) & 0x0FFFF);
		Byte.push_back((Uint4) & 0x0FFFF);
		return Start;
	}
	static void PushString(std::wstring Str, std::vector<wchar_t> &Byte)
	{
		PushLengthValue(Str.size(), Byte);
		for (size_t i = 0; i < Str.size(); i++)
		{
			Byte.push_back(Str[i]); 
		}
		return;
	}
	static void PushWcharVector(std::vector<wchar_t> &StringArray, std::vector<wchar_t> &Byte)
	{
		PushLengthValue(StringArray.size(), Byte);
		for (size_t i = 0; i < StringArray.size(); i++)
		{
			Byte.push_back(StringArray[i]);
		}
		return;
	}



	static unsigned int GetLengthValue(const std::vector<wchar_t>& ByteVssd, int &Pos)
	{
		unsigned int LengthValue = 0;
		LengthValue += ByteVssd.at(Pos) * 256 * 256;  Pos++;
		LengthValue += ByteVssd.at(Pos);				Pos++;
		 
		return LengthValue;
	}
	static std::wstring GetString(const std::vector<wchar_t>& ByteVssd, int &Pos)
	{
		unsigned int LengthValue = GetLengthValue(ByteVssd, Pos);

		std::wstring ws;
		 
		for (int i = 0; i < LengthValue; i++)
		{
			ws.push_back(ByteVssd[Pos++]); 
		} 
		return ws;
	}
	static void GetWcharVector(std::vector<wchar_t> &WcharVector, std::vector<wchar_t> &ByteVssd, int &Pos)
	{
		unsigned int LengthValue = GetLengthValue(ByteVssd, Pos); 
		for (size_t i = 0; i < LengthValue; i++)
		{ 
			WcharVector.push_back(ByteVssd[Pos + i]);
			Pos++;
		}
		return;
	}



	


	static std::string WStringToString(const std::wstring &wstrSrc)
	{
		int nLen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstrSrc.c_str(), -1, NULL, 0, NULL, NULL);
		if (nLen <= 0) return std::string("");

		char* pszDst = new char[nLen + 1];
		if (NULL == pszDst) return std::string("");
		memset(pszDst, 0, nLen + 1);

		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstrSrc.c_str(), -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen] = 0;

		std::string strTemp(pszDst);
		delete[] pszDst;
		pszDst = NULL;
		return strTemp;

	}

	static std::wstring StringToWString(const std::string &strSrc)
	{
		int nLen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strSrc.c_str(), strSrc.length(), 0, 0);
		if (nLen <= 0) return std::wstring(L"");

		WCHAR *pwszDst = new WCHAR[nLen + 1];
		if (NULL == pwszDst) return std::wstring(L"");
		memset(pwszDst, 0, nLen + 1);

		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strSrc.c_str(), strSrc.length(), pwszDst, nLen);
		pwszDst[nLen] = 0;

		std::wstring wstrTemp(pwszDst);
		delete pwszDst;
		pwszDst = NULL;
		return wstrTemp;
	}
	static wchar_t WStringMatch(std::wstring str1, std::wstring str2)
	{
		int slen1 = str1.size();
		int slen2 = str2.size();

		//实际使用时根据strl的长度来动态分配表的内存
		wchar_t matchmap[128][128];
		memset(matchmap, 0, 128 * 128);
		matchmap[0][0] = 1;
		int i, j, k;
		//遍历目标字符串符串
		for (i = 1; i <= slen1; ++i)
		{
			//遍历通配符串
			for (j = 1; j <= slen2; ++j)
			{
				//当前字符之前的字符是否已经得到匹配
				if (matchmap[i - 1][j - 1])
				{
					//匹配当前字符
					if (str1[i - 1] == str2[j - 1] || str2[j - 1] == '?')
					{
						matchmap[i][j] = 1;
						//考虑星号在末尾的情况
						if (i == slen1 && j < slen2)
						{
							for (k = j + 1; k <= slen2; ++k)
							{
								if ('*' == str2[k - 1])
								{
									matchmap[i][k] = 1;
								}
								else
								{
									break;
								}
							}
						}
					}
					else if (str2[j - 1] == '*')
					{
						//遇到星号，目标字符串到末尾都能得到匹配
						for (k = i - 1; k <= slen1; ++k)
						{
							matchmap[k][j] = 1;
						}
					}
				}
			}
			//如果当前字符得到了匹配则继续循环，否则匹配失败
			for (k = 1; k <= slen2; ++k)
			{
				if (matchmap[i][k])
				{
					break;
				}
			}
			if (k > slen2)
			{
				return 0;
			}
		}
		return matchmap[slen1][slen2];
	}

};
