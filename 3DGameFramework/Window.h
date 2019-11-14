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
	// �E�B���h�E�n���h�����擾����
	const HWND GetHWnd() const
	{
		return m_hWnd;
	}

	// �R���X�g���N�^
	Window(const HINSTANCE& hInstance, int nCmdShow) noexcept : m_hInstance(hInstance), m_nCmdShow(nCmdShow)
	{
	}

	// �N���X��o�^���E�B���h�E�𐶐�����
	int Initialize(int width, int height) noexcept
	{
		// �N���X��o�^����
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
		// �N���X��o�^����
		if (!RegisterClassEx(&wndClassEx))
			return EXIT_FAILURE;

		// �E�B���h�E�𐶐�����
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = static_cast<LONG>(width);
		rect.bottom = static_cast<LONG>(height);

		// �N���C�A���g�̈�̃T�C�Y�ɂ��E�B���h�E�T�C�Y��ύX����
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		
		// �E�B���h�E�𐶐�����
		m_hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);

		if (!m_hWnd)
			return EXIT_FAILURE; 
		
		// TODO: nCmdShow��SW_SHOWMAXIMIZED���Z�b�g���ċK��Ńt���X�N���[���ɕύX����
		// SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_game.get()));

		// GetClientRect(hwnd, &rc);
		// Initialize window
		// g_game->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
		return EXIT_SUCCESS;
	}

	// �E�B���h�E��\������
	void ShowWindow()
	{
		// �E�B���h�E��\������
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// �E�B���h�E�n���h��
	HWND m_hWnd;
	// �C���X�^���X�n���h��
	HINSTANCE m_hInstance;
	// �E�B���h�E�\���t���O
	int m_nCmdShow;
};

#endif	// WINDOW_DEFINED
