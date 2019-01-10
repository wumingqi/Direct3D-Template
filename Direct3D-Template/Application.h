#pragma once
#include "D3D12Instance.h"
	class Application
	{
	private:
		HINSTANCE m_hInstance;
		HWND m_hWnd;
		UINT m_width, m_height;
		wstring m_title;

		D3D12Instance instance;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		LRESULT Handle_WM_PAINT(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_SIZE(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_LBUTTONDOWN(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_LBUTTONUP(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_MOUSEMOVE(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_MOUSEWHEEL(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_KEYDOWN(WPARAM wParam, LPARAM lParam);
		LRESULT Handle_WM_DESTROY(WPARAM wParam, LPARAM lParam);
	public:
		Application(wstring title, HINSTANCE hInstance = nullptr, UINT width = 1280, UINT height = 720);
		int Run(int nCmdShow)
		{
			WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
			wc.lpfnWndProc = WndProc;
			wc.lpszClassName = TEXT("MainWindow");
			wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
			wc.style = CS_VREDRAW | CS_HREDRAW;

			RegisterClassEx(&wc);

			//��������λ�ã��ô���λ����Ļ����
			RECT rc = { 0,0,static_cast<decltype(rc.right)>(m_width),static_cast<decltype(rc.bottom)>(m_height) };
			auto dwStyle = WS_OVERLAPPEDWINDOW;
			AdjustWindowRect(&rc, dwStyle, FALSE);
			auto cx = GetSystemMetrics(SM_CXSCREEN);		//��Ļ���
			auto cy = GetSystemMetrics(SM_CYFULLSCREEN);	//��Ļ�߶ȣ�������������
			auto w = rc.right - rc.left;					//���ڵĿ��
			auto h = rc.bottom - rc.top;					//���ڵĸ߶�
			auto x = (cx - w) >> 1;							//�������ϽǺ�����
			auto y = (cy - h) >> 1;							//�������Ͻ�������

			m_hWnd = CreateWindowEx(
				WS_EX_NOREDIRECTIONBITMAP, wc.lpszClassName,
				m_title.c_str(), dwStyle,
				x, y, w, h, nullptr, nullptr, nullptr, nullptr);

			SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
			instance.Initialize(m_hWnd, m_width, m_height);

			ShowWindow(m_hWnd, SW_SHOWDEFAULT);
			MSG msg = {};
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return static_cast<int>(msg.wParam);
		}
	};

