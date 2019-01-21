#pragma once
#include "ExString.hpp"
#include <iostream>

using namespace ExString;

int main()
{
	const char* c = "char";
	const wchar_t* wc = L"wchar";
	const TCHAR* tc = _T("tchar");
	std::string s("StdString");
	std::wstring ws(L"StdWString");
	CString cs("CString");
	BSTR bs = SysAllocString(L"BSTR");
	_bstr_t bt("_bstr_t");
	CComBSTR cb("CComBSTR");

	std::cout << "ToChar\n";
	char* C = ToChar(c);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(wc);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(tc);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(s);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(ws);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(cs);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(bs);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(bt);
	std::cout << C << std::endl;
	delete C;
	C = ToChar(cb);
	std::cout << C << std::endl;
	delete C;

	std::cout << "\ntoChar\n";
	std::cout << toChar(c).get() << std::endl;
	std::cout << toChar(wc).get() << std::endl;
	std::cout << toChar(tc).get() << std::endl;
	std::cout << toChar(s).get() << std::endl;
	std::cout << toChar(ws).get() << std::endl;
	std::cout << toChar(cs).get() << std::endl;
	std::cout << toChar(bs).get() << std::endl;
	std::cout << toChar(bt).get() << std::endl;
	std::cout << toChar(cb).get() << std::endl;

	std::cout << "\nToStdString\n";
	std::cout << ToStdString(c) << std::endl;
	std::cout << ToStdString(wc) << std::endl;
	std::cout << ToStdString(tc) << std::endl;
	std::cout << ToStdString(s) << std::endl;
	std::cout << ToStdString(ws) << std::endl;
	std::cout << ToStdString(cs) << std::endl;
	std::cout << ToStdString(bs) << std::endl;
	std::cout << ToStdString(bt) << std::endl;
	std::cout << ToStdString(cb) << std::endl;

	std::wcout << "\nToWchar_t\n";
	wchar_t* W = ToWchar_t(c);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(wc);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(tc);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(s);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(ws);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(cs);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(bs);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(bt);
	std::wcout << W << std::endl;
	delete W;
	W = ToWchar_t(cb);
	std::wcout << W << std::endl;
	delete W;

	std::wcout << "\ntoWchar_t\n";
	std::wcout << toWchar_t(c).get() << std::endl;
	std::wcout << toWchar_t(wc).get() << std::endl;
	std::wcout << toWchar_t(tc).get() << std::endl;
	std::wcout << toWchar_t(s).get() << std::endl;
	std::wcout << toWchar_t(ws).get() << std::endl;
	std::wcout << toWchar_t(cs).get() << std::endl;
	std::wcout << toWchar_t(bs).get() << std::endl;
	std::wcout << toWchar_t(bt).get() << std::endl;
	std::wcout << toWchar_t(cb).get() << std::endl;

	std::wcout << "\nToStdWString\n";
	std::wcout << ToStdWString(c) << std::endl;
	std::wcout << ToStdWString(wc) << std::endl;
	std::wcout << ToStdWString(tc) << std::endl;
	std::wcout << ToStdWString(s) << std::endl;
	std::wcout << ToStdWString(ws) << std::endl;
	std::wcout << ToStdWString(cs) << std::endl;
	std::wcout << ToStdWString(bs) << std::endl;
	std::wcout << ToStdWString(bt) << std::endl;
	std::wcout << ToStdWString(cb) << std::endl;

	std::wcout << "\nToTchar\n";
	TCHAR* T = ToTchar(c);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(wc);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(tc);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(s);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(ws);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(cs);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(bs);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(bt);
	std::wcout << T << std::endl;
	delete T;
	T = ToTchar(cb);
	std::wcout << T << std::endl;
	delete T;

	std::wcout << "\nToCString\n";
	std::wcout << (LPCTSTR)ToCString(c) << std::endl;
	std::wcout << (LPCTSTR)ToCString(wc) << std::endl;
	std::wcout << (LPCTSTR)ToCString(tc) << std::endl;
	std::wcout << (LPCTSTR)ToCString(s) << std::endl;
	std::wcout << (LPCTSTR)ToCString(ws) << std::endl;
	std::wcout << (LPCTSTR)ToCString(cs) << std::endl;
	std::wcout << (LPCTSTR)ToCString(bs) << std::endl;
	std::wcout << (LPCTSTR)ToCString(bt) << std::endl;
	std::wcout << (LPCTSTR)ToCString(cb) << std::endl;

	std::wcout << "\nToBSTR\n";
	BSTR B = ToBSTR(c);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(wc);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(tc);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(s);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(ws);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(cs);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(bs);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(bt);
	std::wcout << B << std::endl;
	SysFreeString(B);
	B = ToBSTR(cb);
	std::wcout << B << std::endl;
	SysFreeString(B);

	std::wcout << "\nTo_bstr_t\n";
	std::wcout << To_bstr_t(c) << std::endl;
	std::wcout << To_bstr_t(wc) << std::endl;
	std::wcout << To_bstr_t(tc) << std::endl;
	std::wcout << To_bstr_t(s) << std::endl;
	std::wcout << To_bstr_t(ws) << std::endl;
	std::wcout << To_bstr_t(cs) << std::endl;
	std::wcout << To_bstr_t(bs) << std::endl;
	std::wcout << To_bstr_t(bt) << std::endl;
	std::wcout << To_bstr_t(cb) << std::endl;

	std::wcout << "\nToCComBSTR\n";
	std::wcout << (LPCTSTR)ToCComBSTR(c) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(wc) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(tc) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(s) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(ws) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(cs) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(bs) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(bt) << std::endl;
	std::wcout << (LPCTSTR)ToCComBSTR(cb) << std::endl;

	std::cout << "\nSplit" << std::endl;
	s = "a,b,c,d,,,g,h,i";
	auto ss = Split(s);
	for (auto sp : ss) {
		std::cout << sp << std::endl;
	}
	std::cout << "\nSplit empty skip" << std::endl;
	ss = Split(s, ',', true);
	for (auto sp : ss) {
		std::cout << sp << std::endl;
	}

	std::wcout << L"\nSplit" << std::endl;
	ws = L"a,b, c, d,, , g, h,i,";
	auto wss = Split(ws);
	for (auto sp : wss) {
		std::wcout << sp << std::endl;
	}
	std::wcout << L"\nSplit empty skip" << std::endl;
	wss = Split(ws, L',', true);
	for (auto sp : wss) {
		std::wcout << sp << std::endl;
	}

	std::wcout << L"\nSplit is_skip = false is_string = true \n";
	std::wstring delim(L", ");
	wss = Split(ws, delim);
	for (auto sp : wss) {
		std::wcout << sp << std::endl;
	}

	std::wcout << L"\nSplit is_skip = true is_string = true \n";
	wss = Split(ws, delim, true);
	for (auto sp : wss) {
		std::wcout << sp << std::endl;
	}

	std::wcout << L"\nSplit is_skip = false is_string = false \n";
	wss = Split(ws, delim, false, false);
	for (auto sp : wss) {
		std::wcout << sp << std::endl;
	}

	std::wcout << L"\nSplit is_skip = true is_string = false \n";
	wss = Split(ws, delim, true, false);
	for (auto sp : wss) {
		std::wcout << sp << std::endl;
	}

	std::cout << "\nTrim" << std::endl;
	s = " trim   trim   ";
	Trim(s);
	std::cout << s << std::endl;
	ws = L"  Trim Trim   ";
	Trim(ws);
	std::wcout << ws << std::endl;

	std::cout << "\nRemove" << std::endl;
	Remove(s, ' ');
	std::cout << s << std::endl;
	Remove(s, std::string("rm"), false);
	std::cout << s << std::endl;
	Remove(ws, L' ');
	std::wcout << ws << std::endl;
	Remove(ws, std::wstring(L"Tr"));
	std::wcout << ws << std::endl;

	SysFreeString(bs);
	return 0;
}

