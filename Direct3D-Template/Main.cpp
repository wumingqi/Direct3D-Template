//Main.cpp	程序入口点

#include "pch.h"
#include "Application.h"

_Use_decl_annotations_
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
	return Application(L"Direct3D-Template",hInstance).Run(nCmdShow);
}