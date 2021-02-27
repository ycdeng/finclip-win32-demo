// FinClip.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "FinClip.h"
#include "finclip-sdk.h"
#include<iostream>

#define MAX_LOADSTRING 100
using namespace std;

HINSTANCE hInst;
HWND gHwnd;// current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
HWND hWnd_appkey;
HWND hWnd_secret;
HWND hWnd_appid;
BOOL is_initialized = FALSE;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FINCLIP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINCLIP));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINCLIP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; //设置窗体样式 

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, 500, 650, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	gHwnd = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

std::string utf8_encode(const std::wstring& wstr, int CP = CP_UTF8)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string& str, int CP = CP_UTF8)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
void init_finclipsdk(int app_store, std::wstring wappkey, std::wstring wsecret) {
	if (is_initialized) {
		return;
	}

	std::string appkey = utf8_encode(wappkey);
	std::string secret = utf8_encode(wsecret);

	IFinConfigPacker* configpacker = NewFinConfigPacker();
	IFinConfig* config = configpacker->NewConfig();
	config->SetAppStore(app_store);
	config->SetApiPrefix("/api/v1/mop");
	config->SetAppKey(appkey.c_str());
	config->SetSecret(secret.c_str());
	config->SetDomain("https://api.finclip.com");
	config->SetEncryptType(1);
	config->SetFinger("");

	configpacker->AddConfig(config);
	Initialize(hInst, configpacker);
	is_initialized = TRUE;
}


void finclip_applet_callback(int ret, IEvent*) {

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwndButtonCintinue;

	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDM_START_APPLET) {
			WCHAR key[1024];
			GetWindowText(hWnd_appkey, key, 1023);
			WCHAR secret[1024];
			GetWindowText(hWnd_secret, secret, 1023);
			WCHAR appid[1024];
			GetWindowText(hWnd_appid, appid, 1023);
			std::wstring wappkey(key);
			std::wstring wsecret(secret);
			std::wstring wappid(appid);
			if (wappkey.length() == 0) {
				MessageBox(NULL, L"请输入appKey", L"提示", 0);
				return 0;
			}
			if (wsecret.length() == 0) {
				MessageBox(NULL, L"请输入Secret", L"提示", 0);
				return 0;
			}
			if (wappid.length() == 0) {
				MessageBox(NULL, L"请输入appid", L"提示", 0);
				return 0;
			}
			int appstore = 1;
			init_finclipsdk(appstore, wappkey, wsecret);
			IFinPacker* packer = NewFinPacker();
			packer->BeginPacker();
			packer->Add("appId", utf8_encode(wappid).c_str());
			packer->Add("query", "1");
			packer->EndPacker();
			int len = packer->GetBufferSize() + 1;
			unsigned char* ret = new unsigned char[len];
			memset(ret, 0, len);
			packer->Dump(ret, &len);
			delete[] ret;
			StartApplet(appstore, utf8_encode(wappid).c_str(), packer, finclip_applet_callback);
			packer->Release();
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		CreateWindowW(
			L"static",
			L"AppKEY",
			WS_CHILD | WS_VISIBLE,
			20, 20, 60, 30, hWnd,
			(HMENU)1,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);

		CreateWindowW(
			L"static",
			L"Secret",
			WS_CHILD | WS_VISIBLE,
			20, 60, 60, 30, hWnd,
			(HMENU)2,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);

		CreateWindowW(
			L"static",
			L"appid",
			WS_CHILD | WS_VISIBLE,
			20, 100, 60, 30, hWnd,
			(HMENU)2,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);
		hWnd_appkey = CreateWindowW(L"EDIT", L"22LyZEib0gLTQdU3MUauAfJ/xujwNfM6OvvEqQyH4igA",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			100, 20, 300, 30,
			hWnd,
			(HMENU)IDM_APPLET_APPKEY, ((LPCREATESTRUCT)lParam)->hInstance, NULL);


		hWnd_secret = CreateWindowW(L"EDIT", L"703b9026be3d6bc5",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			100, 60, 300, 30,
			hWnd,
			(HMENU)IDM_APPLET_SECRET, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		hWnd_appid = CreateWindowW(L"EDIT", L"5ea0401463cb900001d73865",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			100, 100, 300, 30,
			hWnd,
			(HMENU)IDM_APPLET_APPID, ((LPCREATESTRUCT)lParam)->hInstance, NULL);




		HWND hwndButton = CreateWindowW(
			L"BUTTON",
			L"打开小程序",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			100,
			250,
			200,
			50,
			hWnd,
			(HMENU)IDM_START_APPLET,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

	}
	break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}
