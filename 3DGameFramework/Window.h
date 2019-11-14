#pragma once
#ifndef  WINDOW_DEFINED
#define  WINDOW_DEFINED

#include <windows.h>
#include <mouse.h>
#include <keyboard.h>
#include "Game.h"

#define  CLASS_NAME		L"DirectX11 Game Framework"
#define  WINDOW_NAME	L"DirectX11 Game Framework"

class Window 
{
public:
	// ウィンドウハンドルを取得する
	const HWND GetHWnd() const
	{
		return m_hWnd;
	}

	// コンストラクタ
	Window(const HINSTANCE& hInstance, int nCmdShow) noexcept : m_hInstance(hInstance), m_nCmdShow(nCmdShow)
	{
	}

	// クラスを登録しウィンドウを生成する
	int Initialize(int width, int height) noexcept
	{
		// クラスを登録する
		WNDCLASSEX wndClassEx;
		wndClassEx.cbSize = sizeof(WNDCLASSEX);
		wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
		wndClassEx.lpfnWndProc = WndowProc;
		wndClassEx.cbClsExtra = 0;
		wndClassEx.cbWndExtra = 0;
		wndClassEx.hInstance = m_hInstance;
		wndClassEx.hIcon = LoadIcon(m_hInstance, L"IDI_ICON");
		wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClassEx.lpszMenuName = nullptr;
		wndClassEx.lpszClassName = CLASS_NAME;
		wndClassEx.hIconSm = LoadIcon(wndClassEx.hInstance, L"IDI_ICON");
		// クラスを登録する
		if (!RegisterClassEx(&wndClassEx))
			return EXIT_FAILURE;

		// ウィンドウを生成する
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = static_cast<LONG>(width);
		rect.bottom = static_cast<LONG>(height);

		// クライアント領域のサイズによりウィンドウサイズを変更する
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		
		// ウィンドウを生成する
		m_hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);

		if (!m_hWnd)
			return EXIT_FAILURE; 
		
		// TODO: nCmdShowにSW_SHOWMAXIMIZEDをセットして規定でフルスクリーンに変更する
		// SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_game.get()));

		// GetClientRect(hwnd, &rc);
		// Initialize window
		// g_game->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
		return EXIT_SUCCESS;
	}

	// ウィンドウを表示する
	void ShowWindow()
	{
		// ウィンドウを表示する
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// ウィンドウハンドル
	HWND m_hWnd;
	// インスタンスハンドル
	HINSTANCE m_hInstance;
	// ウィンドウ表示フラグ
	int m_nCmdShow;
};

#endif	// WINDOW_DEFINED
