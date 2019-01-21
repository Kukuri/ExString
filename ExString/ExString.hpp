/* codecvt が c++17 で非推奨になったので、Windows 専用に書き換える。
CString も追加する。
unix 系は utf-8 が標準になっているのであまり必要性は感じない。
*/

#pragma once
//#include "stdafx.h"
#include <Windows.h>
//#include <tchar.h>
#include <string>
//#include <string.h>
#include <vector>
#include <locale>
#include <algorithm>
#include <cwctype>
#include <memory>
#include <atlstr.h>
#include <atlconv.h>
#include <comutil.h>
#include <atlbase.h>

#pragma comment(lib, "comsuppw.lib")  
#pragma comment(lib, "kernel32.lib")  

typedef std::basic_string<TCHAR> tstring;

namespace ExString
{
	/* LPSTR   = char*
	* LPCSTR  = const char*
	* LPWSTR  = WCHAR*
	* LPCWSTR = const WCHAR*
	* LPTSTR  = TCHAR*
	* LPCTSTR = const TCHAR*
	*/
	//CString は LPCTSTR にキャストされるので、曖昧さ回避が必要
#pragma region ToChar
	/// <summary>const char* から char* へ変換</summary>
	/// <param name="str">変換する null終端の const char*</param>
	/// <returns>converted char*</returns>
	char* ToChar(const char* str, size_t size = 0) {
		if (str == nullptr)
			throw std::invalid_argument("str is null pointer!!");

		if (size == 0)
			size = strlen(str);

		auto c = new char[size + 1];
		//正常に実行されると、コピー先の文字列は常に NULL で終わります。
		auto no = strcpy_s(c, size + 1, str);
		if (no == 0)
			return c;
		throw std::runtime_error(std::to_string(no));
	}
	/// <summary>std::string から char* へ変換</summary>
	/// <param name="str">変換する std::string</param>
	/// <returns>converted char*</returns>
	char* ToChar(const std::string& str) {
		return ToChar(str.c_str(), str.size());

		//こっちは free で解放しないと駄目なので、没。
		//return _strdup(str.c_str());
	}

	/// <summary>wchar_t* から char* へ変換</summary>
	/// <param name="str">変換する wchar_t*</param>
	/// <param name="nCodePage">変換後の文字コード</param>
	/// <returns>converted char*</returns>
	char* ToChar(const wchar_t* str, UINT nCodePage = CP_ACP) {
		if (str == NULL)
			throw std::invalid_argument("str is null pointer!!");

		//null を含めた文字数
		int bufsize = WideCharToMultiByte(nCodePage, 0, str, -1, 0, 0, NULL, NULL);
		char* c = new char[bufsize];
		int len = WideCharToMultiByte(nCodePage, 0, str, -1, c, bufsize, NULL, NULL);

		return c;
	}
	/// <summary>std::wstring から char* へ変換</summary>
	/// <param name="str">変換する std::wstring</param>
	/// <param name="nCodePage">変換後の文字コード</param>
	/// <returns>converted char*</returns>
	char* ToChar(const std::wstring& str, UINT nCodePage = CP_ACP) {
		return ToChar(str.c_str(), nCodePage);
	}
	char* ToChar(const BSTR str) {
		return _com_util::ConvertBSTRToString(str);
	}
	char* ToChar(const _bstr_t& str) {
		return ToChar((const char*)str);
	}
	char* ToChar(const CComBSTR& str) {
		return ToChar(CW2A(str));
	}
	/// <summary>コードページの変換</summary>
	/// <param name="str">変換文字列</param>
	/// <param name="inCP">変換前のコードページ</param>
	/// <param name="outCP">変換後のコードページ</param>
	/// <returns>converted char*</returns>
	char* ChangeCodePage(const char* str, UINT inCP, UINT outCP) {
		CA2W w(str, inCP);
		return ToChar(w, outCP);
	}
	/// <summary>Local8bitからUtf8へ変換</summary>
	/// <param name="str">Local8bit char*</param>
	/// <returns>utf8 char*</returns>
	char* ToUtf8(const char* str) {
		return ChangeCodePage(str, CP_ACP, CP_UTF8);
	}
	/// <summary>Utf8からLocal8bitへ変換</summary>
	/// <param name="str">Utf8 char*</param>
	/// <returns>Local8bit char*</returns>
	char* ToLocal8bit(const char* str) {
		return ChangeCodePage(str, CP_UTF8, CP_ACP);
	}

	std::unique_ptr<char[]> toChar(const char* str, size_t size = 0) {
		return std::unique_ptr<char[]>(ToChar(str, size));
	}
	std::unique_ptr<char[]>
		toChar(const std::string& str) {
		return toChar(str.c_str(), str.size());
	}
	std::unique_ptr<char[]>
		toChar(const wchar_t* str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<char[]> c(ToChar(str, nCodePage));
		return c;
	}
	std::unique_ptr<char[]>
		toChar(const std::wstring& str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<char[]> c(ToChar(str.c_str(), nCodePage));
		return c;
	}
	std::unique_ptr<char[]> toChar(const BSTR str) {
		return toChar(ToChar(str));
	}
	std::unique_ptr<char[]> toChar(const _bstr_t& str) {
		return toChar((const char*)str, str.length());
	}
	std::unique_ptr<char[]> toChar(const CComBSTR& str) {
		return toChar(CW2A(str));
	}
#pragma endregion

#pragma region ToStdString
	/// <summary>char* から std::string へ変換</summary>
	/// <param name="str">変換する char*</param>
	/// <returns>converted std::string</returns>
	std::string ToStdString(const char* str) {
		return std::string(str);
	}
	std::string ToStdString(const std::string& str) {
		return str;	//copy
	}
	/// <summary>wchar_t* から std::string へ変換</summary>
	/// <param name="str">変換する wchar_t*</param>
	/// <param name="nCodePage">変換後のコードページ</param>
	/// <returns>converted std::string</returns>
	std::string ToStdString(const wchar_t* str, UINT nCodePage = CP_ACP) {
		CW2A a(str, nCodePage);
		return std::string(a);
		//if (isUtf8) {
		//	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		//	return cv.to_bytes(str);
		//}
		//std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
		//	cvt(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(""));
		//return cvt.to_bytes(str);
	}
	/// <summary>std::wstring から std::string へ変換</summary>
	/// <param name="str">変換する std::wstring</param>
	/// <param name="nCodePage">変換後のコードページ</param>
	/// <returns>converted std::string</returns>
	std::string ToStdString(const std::wstring& str, UINT nCodePage = CP_ACP) {
		CW2A a(str.c_str(), nCodePage);
		return std::string(a);
		//if (isUtf8) {
		//	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
		//	return cv.to_bytes(str);
		//}
		//std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
		//	cvt(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(""));
		//return cvt.to_bytes(str);
	}
	/// <summary>CString から std::string へ変換</summary>
	/// <param name="str">変換する CString</param>
	/// <param name="nCodePage">変換後のコードページ</param>
	/// <returns>converted std::string</returns>
	//static std::string ToStdString(const CString& str, UINT nCodePage = CP_ACP) {
	//	CT2A a(str, nCodePage);
	//	return std::string(a);
	//}

	std::string ToStdString(const BSTR str) {
		auto c = _com_util::ConvertBSTRToString(str);
		std::string s(c);
		delete[] c;
		return s;
	}
	std::string ToStdString(const _bstr_t& str) {
		return std::string((const char*)str);
	}
	std::string ToStdString(const CComBSTR& str) {
		return std::string(CW2A(str));
	}
	/// <summary>コードページの変換</summary>
	/// <param name="str">変換文字列</param>
	/// <param name="inCP">変換前のコードページ</param>
	/// <param name="outCP">変換後のコードページ</param>
	/// <returns>converted char*</returns>
	std::string ChangeCodePage(const std::string& str, UINT inCP, UINT outCP) {
		CA2W w(str.c_str(), inCP);
		return std::string(CW2A(w, outCP));
	}
	/// <summary>Local8bitからUtf8へ変換</summary>
	/// <param name="str">Local8bit std::string</param>
	/// <returns>utf8 std::string</returns>
	std::string ToUtf8(const std::string& str) {
		return ChangeCodePage(str, CP_ACP, CP_UTF8);
	}
	/// <summary>Utf8からLocal8bitへ変換</summary>
	/// <param name="str">Utf8 std::string</param>
	/// <returns>Local8bit std::string</returns>
	std::string ToLocal8bit(const std::string& str) {
		return ChangeCodePage(str, CP_UTF8, CP_ACP);
	}
#pragma endregion

#pragma region ToWchar_t
	/// <summary>char* から wchar_t* へ変換</summary>
	/// <param name="str">変換する char*</param>
	/// <param name="nCodePage">変換元のコードページ</param>
	/// <returns>converted wchar_t*</returns>
	wchar_t* ToWchar_t(const char* str, UINT nCodePage = CP_ACP) {
		if (str == NULL) {
			throw std::invalid_argument("str is null pointer!!");
		}
		int bufsize = MultiByteToWideChar(nCodePage, MB_PRECOMPOSED, str, -1, NULL, 0);
		wchar_t* wc = new wchar_t[bufsize + 1];
		int len = MultiByteToWideChar(nCodePage, MB_PRECOMPOSED, str, -1, wc, bufsize);
		wc[bufsize] = NULL;
		return wc;

		//CA2W w(str, nCodePage);
		//return _wcsdup(w);
		//		if (isUtf8) {
		//			std::wstring ws = ToStdWString(str);
		//			return ToWchar_t(ws);
		//		}
		//#ifdef _WIN32
		//		//utf8の場合、ラップすると文字化けする。
		//		//auto codePage = isUtf8 ? CP_UTF8 : CP_ACP;
		//		int bufsize = MultiByteToWideChar(
		//			CP_ACP,       // コードページ
		//			MB_PRECOMPOSED, // 文字の種類を指定するフラグ
		//			str,			// マップ元文字列のアドレス
		//			-1,				// ?1 を指定すると、文字列は NULL で終わっていると見なされ、長さが自動的に計算されます。
		//			NULL,			// マップ先ワイド文字列を入れるバッファのアドレス
		//			0				// 0 を指定すると、必要なバッファのサイズ（ワイド文字数）が返り、lpWideCharStr が指すバッファは使われません。
		//		);
		//		wchar_t* wc = new wchar_t[bufsize];
		//		int len = MultiByteToWideChar(
		//			CP_ACP,				// コードページ
		//			MB_PRECOMPOSED,         // 文字の種類を指定するフラグ
		//			str,					// マップ元文字列のアドレス
		//			-1,						// マップ元文字列のバイト数
		//			wc,						// マップ先ワイド文字列を入れるバッファのアドレス
		//			bufsize					// バッファのサイズ
		//		);
		//		wc[bufsize - 1] = NULL;		//これ入れんとごみが出る。
		//		return wc;
		//#else
		//		std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
		//			cvt(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(""));
		//		auto ws = cvt.from_bytes(str);
		//		return ToWchar_t(ws);
		//
		//		//std::mbstate_t state = std::mbstate_t();
		//		//int len = 1 + std::mbsrtowcs(NULL, &str, 0, &state);
		//		//wchar_t* wc = new wchar_t[len];
		//		//std::mbsrtowcs(wc, &str, len, &state);
		//		//return wc;
		//		//wchar_t* wc = new wchar_t[len + 1];
		//		//size_t converted = 0;
		//		//mbstowcs_s(&converted, wc, len + 1, str, _TRUNCATE);
		//#endif
	}
	/// <summary>std::string から wchar_t* へ変換</summary>
	/// <param name="str">変換する std::string</param>
	/// <param name="nCodePage">変換元のコードページ</param>
	/// <returns>converted wchar_t*</returns>
	wchar_t* ToWchar_t(const std::string& str, UINT nCodePage = CP_ACP) {
		return ToWchar_t(str.c_str(), nCodePage);
	}
	wchar_t* ToWchar_t(const wchar_t* str, size_t size = 0) {
		if (str == NULL) {
			throw std::invalid_argument("str is null pointer!!");
		}
		if (size == 0)
			size = wcslen(str);

		auto wc = new wchar_t[size + 1];
		auto no = wcscpy_s(wc, size + 1, str);
		if (no == 0)
			return wc;

		throw std::runtime_error(std::to_string(no));
	}
	/// <summary>std::wstring から wchar_t* へ変換</summary>
	/// <param name="str">変換する std::wstring</param>
	/// <returns>converted wchar_t*</returns>
	wchar_t* ToWchar_t(const std::wstring& str) {
		return ToWchar_t(str.c_str(), str.size());

		//こっちは free で解放しないと駄目なので、没。
		//return _wcsdup(str.c_str());
	}
	wchar_t* ToWchar_t(const BSTR str) {
		return ToWchar_t((const wchar_t*)str, SysStringLen(str));
	}
	wchar_t* ToWchar_t(const _bstr_t& str) {
		return ToWchar_t((const wchar_t*)str);
	}
	wchar_t* ToWchar_t(const CComBSTR& str) {
		return ToWchar_t((const wchar_t*)str);
	}

	std::unique_ptr<wchar_t[]>
		toWchar_t(const char* str, UINT nCodePage = CP_ACP) {
		return std::unique_ptr<wchar_t[]>(ToWchar_t(str, nCodePage));
	}
	std::unique_ptr<wchar_t[]>
		toWchar_t(const std::string& str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<wchar_t[]> wc(ToWchar_t(str.c_str(), nCodePage));
		return wc;
	}
	std::unique_ptr<wchar_t[]>
		toWchar_t(const wchar_t* str, size_t size = 0) {
		std::unique_ptr<wchar_t[]> wc(ToWchar_t(str, size));
		return wc;
	}
	std::unique_ptr<wchar_t[]>
		toWchar_t(const std::wstring& str) {
		std::unique_ptr<wchar_t[]> wc(ToWchar_t(str.c_str(), str.size()));
		return wc;

	}
	std::unique_ptr<wchar_t[]> toWchar_t(const BSTR str) {
		return std::unique_ptr<wchar_t[]>(ToWchar_t(str));
	}
	std::unique_ptr<wchar_t[]> toWchar_t(const _bstr_t& str) {
		return toWchar_t((LPCWSTR)str, str.length());
	}
	std::unique_ptr<wchar_t[]> toWchar_t(const CComBSTR& str) {
		return toWchar_t((LPCWSTR)str, str.Length());
	}
#pragma endregion

#pragma region ToStdWString
	/// <summary>char* から std::wstring へ変換</summary>
	/// <param name="str">変換する char*</param>
	/// <param name="nCodePage">変換元のコードページ</param>
	/// <returns>converted std::wstring</returns>
	std::wstring ToStdWString(const char* str, UINT nCodePage = CP_ACP) {
		return std::wstring(CA2W(str, nCodePage));
		//if (isUtf8) {
		//	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8conv;
		//	return utf8conv.from_bytes(str);
		//}
		//else {
		//	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
		//		cvt(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(""));
		//	return cvt.from_bytes(str);
		//}
	}
	/// <summary>std::string から std::wstring へ変換</summary>
	/// <param name="str">変換する std::string</param>
	/// <param name="nCodePage">変換元のコードページ</param>
	/// <returns>converted std::wstring</returns>
	std::wstring ToStdWString(const std::string& str, UINT nCodePage = CP_ACP) {
		return std::wstring(CA2W(str.c_str(), nCodePage));
		//if (isUtf8) {
		//	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8conv;
		//	return utf8conv.from_bytes(str);
		//}
		//else {
		//	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
		//		cvt(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(""));
		//	return cvt.from_bytes(str);
		//}
	}
	/// <summary>wchar_t* から std::wstring へ変換</summary>
	/// <param name="str">変換する wchar_t*</param>
	/// <returns>converted std::wstring</returns>
	std::wstring ToStdWString(const wchar_t* str) {
		return std::wstring(str);
	}
	std::wstring ToStdWString(const std::wstring& str) {
		return str;	//copy
	}
	/// <summary>CString から std::wstring へ変換</summary>
	/// <param name="str">変換する CString</param>
	/// <param name="nCodePage">変換後のコードページ</param>
	/// <returns>converted std::wstring</returns>
	//static std::wstring ToStdWString(const CString& str) {
	//	return std::wstring(CT2W((LPCTSTR)str));
	//}

	//wchar_t* と被るのでボツ
	//static std::wstring ToStdWString(const BSTR str) {
	//	auto w = ToWchar_t(str);
	//	std::wstring ws(w);
	//	delete[] w;
	//	return ws;
	//}
	std::wstring ToStdWString(const _bstr_t& str) {
		return std::wstring((LPCWSTR)str, str.length());
	}
	std::wstring ToStdWString(const CComBSTR& str) {
		return std::wstring((LPCWSTR)str, str.Length());
	}

	std::vector<std::wstring>
		ToStdWString(const std::vector<std::string>& vs, UINT nCodePage = CP_ACP) {
		std::vector<std::wstring> vw;
		vw.reserve(vs.size());

		for (size_t i = 0; i < vs.size(); i++) {
			vw.push_back(CA2W(vs[i].c_str(), nCodePage).m_psz);
		}

		return vw;
	}
#pragma endregion

#pragma region ToTchar
	/// <summary>char* から TCHAR* へ変換</summary>
	/// <param name="str">変換する char*</param>
	/// <param name="nCodePage">変換元のコードページ</param>
	/// <returns>converted TCHAR*</returns>
	TCHAR* ToTchar(const char* str, UINT nCodePage = CP_ACP) {
#ifdef UNICODE
		return ToWchar_t(str, nCodePage);
#else
		return ToChar(str);
#endif
	}
	/// <summary>std::string から TCHAR* へ変換</summary>
	/// <param name="str">変換する std::string</param>
	/// <param name="nCodePage">変換元のコードページ</param>
	/// <returns>converted TCHAR*</returns>
	TCHAR* ToTchar(const std::string& str, UINT nCodePage = CP_ACP) {
#ifdef UNICODE
		return ToWchar_t(str.c_str(), nCodePage);
#else
		return ToChar(str.c_str());
#endif
	}
	/// <summary>wchar_t* から TCHAR* へ変換</summary>
	/// <param name="str">変換する wchar_t*</param>
	/// <param name="nCodePage">変換後のコードページ</param>
	/// <returns>converted TCHAR*</returns>
	TCHAR* ToTchar(const wchar_t* str, UINT nCodePage = CP_ACP) {
#ifdef UNICODE
		return ToWchar_t(str);
#else
		return ToChar(str, nCodePage);
#endif
	}
	/// <summary>std::wstring から TCHAR* へ変換</summary>
	/// <param name="str">変換する std::wstring</param>
	/// <param name="nCodePage">変換後のコードページ</param>
	/// <returns>converted TCHAR*</returns>
	TCHAR* ToTchar(const std::wstring& str, UINT nCodePage = CP_ACP) {
#ifdef UNICODE
		return ToWchar_t(str.c_str());
#else
		return ToChar(str, nCodePage);
#endif
	}
	TCHAR* ToTchar(const _bstr_t& str, UINT nCodePage = CP_ACP) {
		return ToTchar((LPCTSTR)str, nCodePage);
	}

	std::unique_ptr<TCHAR[]>
		toTchar(const char* str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<TCHAR[]> tc(ToTchar(str, nCodePage));
		return tc;
	}
	std::unique_ptr<TCHAR[]>
		toTchar(const std::string& str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<TCHAR[]> tc(ToTchar(str.c_str(), nCodePage));
		return tc;
	}
	std::unique_ptr<TCHAR[]>
		toTchar(const wchar_t* str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<TCHAR[]> tc(ToTchar(str, nCodePage));
		return tc;
	}
	std::unique_ptr<TCHAR[]>
		toTchar(const std::wstring& str, UINT nCodePage = CP_ACP) {
		std::unique_ptr<TCHAR[]> tc(ToTchar(str.c_str(), nCodePage));
		return tc;
	}
#pragma endregion

#pragma region ToCString
	CString ToCString(const char* str, UINT nCodePage = CP_ACP) {
		if (nCodePage == CP_ACP) {
			return CString(str);
		}
		CA2W w(str, nCodePage);
		return CString(w);
	}
	CString ToCString(const std::string& str, UINT nCodePage = CP_ACP) {
		return ToCString(str.c_str(), nCodePage);
	}
	CString ToCString(const wchar_t* str) {
		return CString(str);
	}
	CString ToCString(const std::wstring& str) {
		return CString(str.c_str());
	}
	CString ToCString(const CString& str) {
		return str;	//copy
	}
	CString ToCString(const BSTR str) {
		return CString(str);
	}
	CString ToCString(_bstr_t& str) {
		return CString(str.GetBSTR());
	}
	CString ToCString(const CComBSTR& str) {
		return CString(str);
	}
#pragma endregion

#pragma region BSTR 解放は SysFreeString で
	BSTR ToBSTR(const char* str) {
		return _com_util::ConvertStringToBSTR(str);
	}
	BSTR ToBSTR(const std::string& str) {
		return _com_util::ConvertStringToBSTR(str.c_str());
	}
	BSTR ToBSTR(const wchar_t* str) {
		return SysAllocString(str);
	}
	BSTR ToBSTR(const std::wstring& str) {
		return SysAllocString(str.c_str());
	}
	BSTR ToBSTR(const BSTR str) {
		if (str != NULL) {
			return ::SysAllocStringByteLen((char*)str, ::SysStringByteLen(str));
		}
		else {
			return ::SysAllocStringByteLen(NULL, 0);
		}
	}
	BSTR ToBSTR(const _bstr_t& str) {
		return str.copy();
	}
	BSTR ToBSTR(const CComBSTR& str) {
		return str.Copy();
	}
#pragma endregion

#pragma region _bstr_t 
	_bstr_t To_bstr_t(const char* str) {
		return _bstr_t(str);
	}
	_bstr_t To_bstr_t(const std::string& str) {
		return _bstr_t(str.c_str());
	}
	_bstr_t To_bstr_t(const wchar_t* str) {
		return _bstr_t(str);
	}
	_bstr_t To_bstr_t(const std::wstring& str) {
		return _bstr_t(str.c_str());
	}
	_bstr_t To_bstr_t(const BSTR str) {
		return _bstr_t(str);
	}
	_bstr_t To_bstr_t(const _bstr_t& str) {
		return str;	//copy
	}
	_bstr_t To_bstr_t(const CComBSTR& str) {
		return _bstr_t(str);
	}
#pragma endregion

#pragma region CComBSTR  
	CComBSTR ToCComBSTR(const char* str) {
		return CComBSTR(str);
	}
	CComBSTR ToCComBSTR(const std::string& str) {
		return CComBSTR(str.c_str());
	}
	CComBSTR ToCComBSTR(const wchar_t* str) {
		return CComBSTR(str);
	}
	CComBSTR ToCComBSTR(const std::wstring& str) {
		return CComBSTR(str.c_str());
	}
	CComBSTR ToCComBSTR(const BSTR str) {
		return CComBSTR(str);
	}
	CComBSTR ToCComBSTR(const _bstr_t& str) {
		return CComBSTR((wchar_t*)str);
	}
	CComBSTR ToCComBSTR(const CComBSTR& str) {
		return str;	//copy
	}
#pragma endregion

#pragma region Split
	/// <summary>文字列分割</summary>
	/// <param name="s">文字列</param>
	/// <param name="delim">分割文字</param>
	/// <param name="is_skip">空文字列の場合スキップするかどうか</param>
	/// <returns>分割された文字列</returns>
	std::vector<std::string>
		Split(const std::string& s, const char delim = ',', bool is_skip = false) {
		assert(!s.empty());
		assert(delim);

		std::vector<std::string> elems;
		std::string item;
		for (char ch : s) {
			if (ch == delim) {
				if (is_skip && item.empty())
					continue;
				elems.push_back(item);
				item.clear();
			}
			else {
				item += ch;
			}
		}
		if (!item.empty())
			elems.push_back(item);
		return elems;
	}
	std::vector<std::wstring>
		Split(const std::wstring& s, const wchar_t delim = L',', bool is_skip = false) {
		assert(!s.empty());
		assert(delim);

		std::vector<std::wstring> elems;
		std::wstring item;
		for (wchar_t ch : s) {
			if (ch == delim) {
				if (is_skip && item.empty())
					continue;
				elems.push_back(item);
				item.clear();
			}
			else {
				item += ch;
			}
		}
		if (!item.empty())
			elems.push_back(item);
		return elems;
	}
	/// <summary>文字列分割</summary>
	/// <param name="s">文字列</param>
	/// <param name="delim">分割文字</param>
	/// <param name="is_skip">空文字列の場合スキップするかどうか</param>
	/// <param name="is_string">delimを文字列として処理する場合は true
	/// 文字単位で処理する場合は false</param>
	/// <returns>分割された文字列</returns>
	template<class T>
	std::vector<std::basic_string<T>>
		Split(
			const std::basic_string<T>& s,
			const std::basic_string<T>& delim,
			bool is_skip = false,
			bool is_string = true)
	{
		assert(!s.empty() || !delim.empty());

		std::vector<std::basic_string<T>> elems;
		size_t p1 = 0;
		if (is_string) {
			for (size_t p2 = s.find(delim); p2 != s.npos; p2 = s.find(delim, p1)) {
				if (p1 < p2 || !is_skip)
					elems.push_back(s.substr(p1, p2 - p1));
				p2 += delim.size();
				p1 = p2;
			}
			if (p1 < s.size())
				elems.push_back(s.substr(p1));
		}
		else {
			for (size_t p2 = s.find_first_of(delim); p2 != s.npos; p2 = s.find_first_of(delim, p1)) {
				if (p1 < p2 || !is_skip)
					elems.push_back(s.substr(p1, p2 - p1));
				p2++;
				p1 = p2;
			}
			if (p1 < s.size())
				elems.push_back(s.substr(p1));
		}
		return elems;
	}

#pragma endregion

#pragma region Trim
	// trim from start (in place)
	inline void LTrim(std::string& s, std::locale& loc = std::locale("")) {
		auto f = [&](const char c) { return !std::isspace(c, loc); };
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), f));
	}
	inline void LTrim(std::wstring& s) {
		auto f = [&](const wchar_t c) { return !std::iswspace(c); };
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), f));
	}

	// trim from end (in place)
	inline void RTrim(std::string& s, std::locale& loc = std::locale("")) {
		auto f = [&](const char c) { return !std::isspace(c, loc); };
		s.erase(std::find_if(s.rbegin(), s.rend(), f).base(), s.end());
	}
	inline void RTrim(std::wstring& s/*, std::locale &loc = std::locale("")*/) {
		auto f = [&](const wchar_t c) { return !std::iswspace(c); };
		s.erase(std::find_if(s.rbegin(), s.rend(), f).base(), s.end());
	}

	// trim from both ends (in place)
	inline void Trim(std::string& s, std::locale& loc = std::locale("")) {
		LTrim(s, loc);
		RTrim(s, loc);
	}
	inline void Trim(std::wstring& s/*, std::locale &loc = std::locale("")*/) {
		LTrim(s);
		RTrim(s);
	}
#pragma endregion

#pragma region Remove
	/// <summary>文字列から指定文字の全削除</summary>
	/// <param name="s">対象の文字列</param>
	/// <param name="del">削除文字</param>
	template<typename CharT>
	void Remove(std::basic_string<CharT>& s, const CharT del) {
		if (!del)
			return;
		std::basic_string<CharT> tmp;
		for (auto c : s) {
			if (c != del)
				tmp += c;
		}
		s = tmp;
	}
	/// <summary>文字列から指定文字の全削除</summary>
	/// <param name="s">対象の文字列</param>
	/// <param name="del">削除文字</param>
	/// <param name="isString">文字列を削除する場合は true
	/// 含まれている文字すべて削除する場合は false</param>
	template<typename CharT> void Remove(
		std::basic_string<CharT>& s,
		const std::basic_string<CharT>& del,
		bool is_string = true)
	{
		if (del.empty())
			return;

		if (is_string) {
			for (size_t c = s.find(del); c != s.npos; c = c = s.find(del)) {
				s.erase(c, del.size());
			}
		}
		else {
			for (size_t c = s.find_first_of(del); c != s.npos; c = c = s.find_first_of(del)) {
				s.erase(c, 1);
			}
		}
	}
#pragma endregion

};

