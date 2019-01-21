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
	std::cout << ToChar(tc) << std::endl;
	std::cout << ToChar(s) << std::endl;
	std::cout << ToChar(ws) << std::endl;
	std::cout << ToChar(cs) << std::endl;
	std::cout << ToChar(bs) << std::endl;
	std::cout << ToChar(bt) << std::endl;
	std::cout << ToChar(cb) << std::endl;

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
	std::wcout << ToWchar_t(c) << std::endl;
	std::wcout << ToWchar_t(wc) << std::endl;
	std::wcout << ToWchar_t(tc) << std::endl;
	std::wcout << ToWchar_t(s) << std::endl;
	std::wcout << ToWchar_t(ws) << std::endl;
	std::wcout << ToWchar_t(cs) << std::endl;
	std::wcout << ToWchar_t(bs) << std::endl;
	std::wcout << ToWchar_t(bt) << std::endl;
	std::wcout << ToWchar_t(cb) << std::endl;

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
	std::wcout << ToTchar(c) << std::endl;
	std::wcout << ToTchar(wc) << std::endl;
	std::wcout << ToTchar(tc) << std::endl;
	std::wcout << ToTchar(s) << std::endl;
	std::wcout << ToTchar(ws) << std::endl;
	std::wcout << ToTchar(cs) << std::endl;
	std::wcout << ToTchar(bs) << std::endl;
	std::wcout << ToTchar(bt) << std::endl;
	std::wcout << ToTchar(cb) << std::endl;

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
	std::wcout << ToBSTR(c) << std::endl;
	std::wcout << ToBSTR(wc) << std::endl;
	std::wcout << ToBSTR(tc) << std::endl;
	std::wcout << ToBSTR(s) << std::endl;
	std::wcout << ToBSTR(ws) << std::endl;
	std::wcout << ToBSTR(cs) << std::endl;
	std::wcout << ToBSTR(bs) << std::endl;
	std::wcout << ToBSTR(bt) << std::endl;
	std::wcout << ToBSTR(cb) << std::endl;

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

