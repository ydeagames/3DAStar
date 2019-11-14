#pragma once
#ifndef DIRECTX11_DEFINED
#define DIRECTX11_DEFINED
#include <memory>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <windows.h>
#include <wrl.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <SimpleMath.h>

#include "StepTimer.h"
#include "NonCopyable.h"

using namespace std;

// DirectX11�N���X
class DirectX11 : public NonCopyable
{
private:
	// �R���X�g���N�^
	DirectX11() noexcept
	{
	}

public:
	// DirectX11�N���X�̃C���X�^���X���擾����
	static DirectX11& Get() noexcept
	{
		if (s_directX.get() == nullptr)
		{
			// DirectX11�I�u�W�F�N�g�𐶐�����
			s_directX.reset(new DirectX11());
		}
		return *s_directX.get();
	}

	// DirectX11�I�u�W�F�N�g��j������
	static void Dispose() noexcept
	{
		s_directX.reset();
	}

	// �E�B���h�E�����擾����
	int GetWidth() const
	{
		return m_width;
	}

	// �E�B���h�E����ݒ肷��
	void SetWidth(const int& width) 
	{
		m_width = width;
	}

	// �E�B���h�E�����擾����
	int GetHeight() const 
	{
		return m_height;
	}

	// �E�B���h�E����ݒ肷��
	void SetHeight(const int& height) 
	{
		m_height = height;
	}

	// �E�B���h�E�n���h�����擾����
	HWND GetHWnd() const
	{
		return m_hWnd;
	}

	// �E�B���h�E�n���h����ݒ肷��
	void SetHWnd(const HWND& hWnd)
	{
		m_hWnd = hWnd;
	}

	// �f�o�C�X���擾����
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const
	{ 
		return m_device; 
	}

	// �f�o�C�X�R���e�L�X�g���擾����
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() const
	{
		return m_context;
	}

	// �X���b�v�`�F�C�����擾����
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() const
	{
		return m_swapChain;
	}

	// �X���b�v�`�F�C����ݒ肷��
	void SetSwapChain(const Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) 
	{
		m_swapChain = swapChain;
	}

	// �����_�[�^�[�Q�b�g�r���[���擾����
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const
	{
		return m_renderTargetView;
	}

	// �f�v�X�X�e���V���r���[���擾����
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const
	{
		return m_depthStencilView;
	}

	// �f�o�C�X�𐶐�����
	void CreateDevice() noexcept;

	// ���\�[�X�𐶐�����
	void CreateResources() noexcept;

	// �f�o�C�X���X�g�����������ꍇ
	void OnDeviceLost();

private:
	// DirectX11�I�u�W�F�N�g�ւ̐ÓI�|�C���^
	static std::unique_ptr<DirectX11> s_directX;

	// ��
	int  m_width;
	// ����
	int  m_height;
	// �E�B���h�E�n���h��
	HWND m_hWnd;
	// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11Device1> m_device1;
	// �f�o�C�X�R���e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>	m_context;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_context1;
	// �@�\���x��
	D3D_FEATURE_LEVEL  m_featureLevel;
	// �X���b�v�`�F�[��
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain1;
	// �����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	// �f�v�X�X�e���V���r���[
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
};

#endif	// DIRECTX11_DEFINED

