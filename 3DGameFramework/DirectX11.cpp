#include "DirectX11.h"

// �n�C�u���b�h�O���t�B�b�N�V�X�e���ɑ΂��f�t�H���g�ŌʂɗD�悷���������
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

// �V���O���g���̂��߂̃|�C���^�ϐ�������������
std::unique_ptr<DirectX11> DirectX11::s_directX(nullptr);

// �f�o�C�X�𐶐�����
void DirectX11::CreateDevice() noexcept
{
	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	static const D3D_FEATURE_LEVEL featureLevels[] = 
	{
		// TODO: �T�|�[�g�����Direct3D�@�\���x�����C������(11.1 �t�H���o�b�N�n���h�����O�Ɋ֘A�����R�[�h���Q�l).
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// DX11 API�f�o�C�X�I�u�W�F�N�g�𐶐����Ή�����R���e�L�X�g���擾����
	HRESULT hr = D3D11CreateDevice(
		nullptr,                 // �K��̃A�_�v�^���g�p���邽�߂�nullptr���w�肷��
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		m_device.ReleaseAndGetAddressOf(),		// �������ꂽDirect3D�f�o�C�X��Ԃ�
		&m_featureLevel,						// �������ꂽ�f�o�C�X�̋@�\���x����Ԃ�
		m_context.ReleaseAndGetAddressOf()		// �f�o�C�X�C�~�f�B�G�C�g�R���e�L�X�g��Ԃ�
	);

	if (hr == E_INVALIDARG) 
	{
		// DirectX 11.0�v���b�g�t�H�[����D3D_FEATURE_LEVEL_11_1��F�����Ȃ��ꍇ�A�F�������܂ōĎ��s����K�v������
		hr = D3D11CreateDevice(nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			&featureLevels[1],
			_countof(featureLevels) - 1,
			D3D11_SDK_VERSION,
			m_device.ReleaseAndGetAddressOf(),
			&m_featureLevel,
			m_context.ReleaseAndGetAddressOf()
		);
	}

	DX::ThrowIfFailed(hr);

#ifndef NDEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> d3dDebug;
	if (SUCCEEDED(this->m_device.As(&d3dDebug))) 
	{
		Microsoft::WRL::ComPtr<ID3D11InfoQueue> d3dInfoQueue;
		if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue))) 
		{
#ifdef _DEBUG
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
			D3D11_MESSAGE_ID hide[] = {
				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
				// TODO: �K�v�ɉ����ă��b�Z�[�WID��ǉ�����
			};
			D3D11_INFO_QUEUE_FILTER filter = {};
			filter.DenyList.NumIDs = _countof(hide);
			filter.DenyList.pIDList = hide;
			d3dInfoQueue->AddStorageFilterEntries(&filter);
		}
	}
#endif
	// DirectX 11.1�����݂���ꍇ DirectX 11.1
	if (SUCCEEDED(m_device.As(&m_device1)))
		(void)this->m_context.As(&m_context1);

	// TODO: �f�o�C�X�Ɉˑ������I�u�W�F�N�g������������ 
}

// SizeChanged�C�x���g�ŃE�B���h�E��ύX���邷�ׂẴ��������\�[�X��z�u����
void DirectX11::CreateResources() noexcept
{
	// ���O�̃E�B���h�E�T�C�Y���w�肳�ꂽ�R���e�L�X�g�ŃN���A����
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	m_context->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
	m_renderTargetView.Reset();
	m_depthStencilView.Reset();
	m_context->Flush();

	UINT backBufferWidth = static_cast<UINT>(m_width);
	UINT backBufferHeight = static_cast<UINT>(m_height);
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	UINT backBufferCount = 2;

	// �X���b�v�`�F�C�������ɑ��݂���ꍇ�T�C�Y��ύX���邩�X���b�v�`�F�C���𐶐�����
	if (m_swapChain) 
	{
		HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) 
		{
			// �f�o�C�X�����炩�̗��R�ō폜���ꂽ�ꍇ�V�����f�o�C�X�ƃX���b�v�`�F�C���𐶐�����K�v������
			OnDeviceLost();
			// ���ׂĂ��Z�b�g�A�b�v���ꂽ�B���̊֐��͂���ȏ�p�����Ȃ�
			return;
		}
		else 
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else 
	{
		// �܂��AD3D�f�o�C�X����DirectX Graphics Interface(DXGI)�f�o�C�X����������
		Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
		DX::ThrowIfFailed(m_device.As(&dxgiDevice));

		// �f�o�C�X�����s���̕����A�_�v�^(GPU�܂��̓J�[�h)�����ʂ���
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

		// �������ꂽ�t�@�N�g���I�u�W�F�N�g���擾����
		Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory;
		DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

		Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2;
		if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2))) 
		{
			// DirectX 11.1�܂��͂���ȍ~�̏ꍇ�X���b�v�`�F�C���̂��߂̃f�B�X�N���v�^�𐶐�����
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
			swapChainDesc.Width = backBufferWidth;
			swapChainDesc.Height = backBufferHeight;
			swapChainDesc.Format = backBufferFormat;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = backBufferCount;

			DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
			fsSwapChainDesc.Windowed = TRUE;

			// Win32�E�B���h�E����X���b�v�`�F�C���𐶐�����
			DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
				m_device.Get(),
				m_hWnd,
				&swapChainDesc,
				&fsSwapChainDesc,
				nullptr,
				m_swapChain1.ReleaseAndGetAddressOf()
			));

			DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
		}
		else 
		{
			DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
			swapChainDesc.BufferCount = backBufferCount;
			swapChainDesc.BufferDesc.Width = backBufferWidth;
			swapChainDesc.BufferDesc.Height = backBufferHeight;
			swapChainDesc.BufferDesc.Format = backBufferFormat;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow = m_hWnd;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.Windowed = TRUE;

			DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_device.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
		}

		// ���̃e���v���[�g�͔r���I�ȃt���X�N���[�����[�h���T�|�[�g���Ȃ�
		// DXGI�ɑ΂���ALT+ENTER�V���[�g�J�b�g�̉�����h�~����
		DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER));
	}

	// �ŏI�I��3D�����_�[�^�[�Q�b�g�ƂȂ�E�B���h�E�ւ̃o�b�N�o�b�t�@���擾����
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

	// �o�C���h���Ɏg�p���郌���_�[�^�[�Q�b�g��̃r���[�C���^�[�t�F�[�X�𐶐�����
	DX::ThrowIfFailed(m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

	// �[�x/�X�e���V���o�b�t�@�Ƃ���2D�T�[�t�F�C�X��z�u���A�o�C���h���Ɏg�p����
	// �T�[�t�F�C�X��̃f�v�X�X�e���V���r���[�𐶐�����
	CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	// Texture2D�I�u�W�F�N�g�𐶐�����
	DX::ThrowIfFailed(m_device->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	// DepthStencilView�I�u�W�F�N�g�𐶐�����
	DX::ThrowIfFailed(m_device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

	// TODO: �E�B���h�E�T�C�Y�Ɉˑ������I�u�W�F�N�g������������
}

// �f�o�C�X���X�g�����������ꍇ�ɌĂяo�����
void DirectX11::OnDeviceLost() 
{
	// DepthStencilView�I�u�W�F�N�g���������
	m_depthStencilView.Reset();
	// RenderTargetView�I�u�W�F�N�g���������
	m_renderTargetView.Reset();
	// SwapChain1�I�u�W�F�N�g���������
	m_swapChain1.Reset();
	// SwapChain�I�u�W�F�N�g���������
	m_swapChain.Reset();
	// DeviceContext�I�u�W�F�N�g���������
	m_context1.Reset();
	// DeviceContext�I�u�W�F�N�g���������
	m_context.Reset();
	// Device1�I�u�W�F�N�g���������
	m_device1.Reset();
	// Device�I�u�W�F�N�g���������
	m_device.Reset();
	// �f�o�C�X�𐶐�����
	CreateDevice();
	// ���\�[�X�𐶐�����
	CreateResources();
}
