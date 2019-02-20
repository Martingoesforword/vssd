#pragma once   
#include "pch.h"
namespace sjh {
	const int IS_SAMESTRING = 0;
	namespace tool {
		namespace string {
			void				Split(std::wstring str, std::vector<std::wstring> &ret, std::wstring pattern);
			int					SameTimes(std::wstring str, std::wstring pattern, int Start, int End);
			void				Trim(std::wstring & s);
			wchar_t				WStringMatch(std::wstring str1, std::wstring str2);
			std::string			WStringToString(const std::wstring &wstrSrc);
			std::wstring		StringToWString(const std::string &strSrc);

			void				PushString(std::wstring Str, std::vector<wchar_t> &Byte);
			void				PushWcharVector(std::vector<wchar_t> &StringArray, std::vector<wchar_t> &Byte);
			size_t				PushLengthValue(size_t Uint4, std::vector<wchar_t> &Byte);
			void				PushToRealFile(std::wstring JumpTo, std::vector<wchar_t> aSerial);

			std::wstring		GetString(const std::vector<wchar_t>& ByteVssd, int &Pos);
			void				GetWcharVector(std::vector<wchar_t> &WcharVector, std::vector<wchar_t> &ByteVssd, int &Pos);
			unsigned int		GetLengthValue(const std::vector<wchar_t>& ByteVssd, int &Pos);
			void				GetFromRealfile(std::wstring GetFrom, std::vector<wchar_t> aSerial);
			std::wstring		GetTimeWString(time_t tm);
			std::wstring		GetSizeWString(size_t Size);
			std::string			GetTimeString(time_t tm);
			std::string			GetSizeString(size_t Size);

			void		CheckQuotation(  std::wstring& Str);
			bool		IsThisSwitch(const std::wstring & Str, const std::wstring& Pram);
			bool		HasSwitch(const std::wstring & Str);
		}
		namespace math 
		{
			bool	IsOuShu(int);
			bool	IsJiShu(int);
		}
	}
	
}