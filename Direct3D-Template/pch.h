#ifndef PCH_H
#define PCH_H

//预编译
#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")

//COM接口封装类ComPtr
#include <wrl.h>

//C++运行时文件
#include <string>
#include <array>
#include <vector>
#include <iostream>

using namespace std;

struct Utility 
{
	static wstring GetModulePath(HMODULE hModule = nullptr)
	{
		wchar_t filename[MAX_PATH];
		GetModuleFileName(hModule, filename, _countof(filename));
		wchar_t *lastSlash = wcsrchr(filename, L'\\');
		if (lastSlash)
		{
			*(lastSlash + 1) = L'\0';
		}
		return { filename };
	}
};

#endif //PCH_H
