#include "Game.h"

void ExitGame();

// �R���X�g���N�^
Game::Game(int width, int height) noexcept
	: m_hWnd(0), m_width(width), m_height(height), m_featureLevel(D3D_FEATURE_LEVEL_9_1) 
{
	// �X�^�[�g�A�b�v���
	STARTUPINFO si{};
	// �C���X�^���X�n���h�����擾����
	m_hInstance = ::GetModuleHandle(NULL);

	// STARTUPINFO�\���̂��擾����
	::GetStartupInfo(&si);
	m_nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	// Window�I�u�W�F�N�g�𐶐�����
	m_window = make_unique<Window>(m_hInstance, m_nCmdShow);
}

// �Q�[�����\�[�X������������
void Game::Initialize() noexcept
{
	// Window�I�u�W�F�N�g������������
	m_window->Initialize(m_width, m_height);
	// Window�I�u�W�F�N�g�̐�����ɃE�B���h�E�n���h�����擾����
	m_hWnd = m_window->GetHWnd();

	// DirectX�̏������̂��߃E�B���h�E�n���h����ݒ肷��
	m_directX.SetHWnd(m_hWnd);
	// DirectX�̏������̂��߃E�B���h�E����ݒ肷��
	m_directX.SetWidth(m_width);
	// DirectX�̏������̂��߃E�B���h�E����ݒ肷��
	m_directX.SetHeight(m_height);

	// �f�o�C�X�𐶐�����
	m_directX.CreateDevice();
	// ���\�[�X�𐶐�����
	m_directX.CreateResources();

    // TODO: �f�t�H���g�ϐ�timestep���[�h�ȊO�̂��̂��K�v�ȏꍇ�^�C�}�[�ݒ��ύX����
	// ��: 60FPS�Œ�^�C���X�e�b�v�X�V���W�b�N�ɑ΂��Ă͈ȉ����Ăяo��
    
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60.0);

	// SpriteBatch�I�u�W�F�N�g�𐶐�����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_directX.GetContext().Get());
	// SpriteFont�I�u�W�F�N�g�𐶐�����
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_directX.GetDevice().Get(), L"Arial.spritefont");
}

// ���\�[�X�𐶐�����
void Game::CreateResources() noexcept
{
}

// �Q�[�����[�v�����s����
MSG Game::Run() noexcept
{
	// ���b�Z�[�W
	MSG msg = {};

	// Game�I�u�W�F�N�g������������
	Initialize();
	// �E�B���h�E��\������
	m_window->ShowWindow();
	// ���\�[�X�𐶐�����
	CreateResources();

	// �Q�[�����[�v
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �Q�[�����X�V����
			m_timer.Tick([&]() { Update(m_timer); });
			// �Q�[���V�[����`�悷��
			Render(m_timer);
		}
	}
	// Game�I�u�W�F�N�g�̌�n��������
	Finalize();
	return msg;
}

// �Q�[�����X�V����
void Game::Update(const DX::StepTimer& timer) noexcept
{
}

// ��n��������
void Game::Finalize() noexcept
{
	// Font�I�u�W�F�N�g���������
	m_spriteFont.reset();
	// SpriteBatch�I�u�W�F�N�g���������
	m_spriteBatch.reset();

	// DirectX11 Graphics�I�u�W�F�N�g���������
	DirectX11::Dispose();
	// Window�I�u�W�F�N�g���������
	m_window.reset();
}

// �V�[����`�悷��
void Game::Render(const DX::StepTimer& timer) noexcept
{
}

// �o�b�N�o�b�t�@���N���A����
void Game::Clear() noexcept
{	// �����_�[�^�[�Q�b�g�r���[���N���A����
	m_directX.GetContext()->ClearRenderTargetView(m_directX.GetRenderTargetView().Get(), DirectX::Colors::DarkSlateGray);
	// �f�v�X�X�e���V���r���[���N���A����
	m_directX.GetContext()->ClearDepthStencilView(m_directX.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// �����_�[�^�b�Q�[�g��ݒ肷��
	m_directX.GetContext()->OMSetRenderTargets(1, m_directX.GetRenderTargetView().GetAddressOf(), m_directX.GetDepthStencilView().Get());
    // �r���[�|�[�g��ݒ肷��
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	m_directX.GetContext()->RSSetViewports(1, &viewport);
}

// �o�b�N�o�b�t�@���X�N���[���ɑ��� 
void Game::Present() noexcept
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.

	// DirectX11�N���X�̃C���X�^���X���擾����
	DirectX11& directX = DirectX11::Get();
	HRESULT hr = directX.GetSwapChain()->Present(1, 0);

    // �f�o�C�X�����Z�b�g���ꂽ�ꍇ�����_�����ď���������K�v������ 
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) 
		directX.OnDeviceLost();
    else 
        DX::ThrowIfFailed(hr);
}

// ���b�Z�[�W�n���h��
void Game::OnActivated()
{
	// TODO: �Q�[�����A�N�e�B�u�ȃE�B���h�E�ɂȂ�ꍇ
}

void Game::OnDeactivated()
{
    // TODO: �Q�[�����o�b�N�O���E���h�E�B���h�E�ɂȂ�ꍇ 
}

void Game::OnSuspending()
{
    // TODO: �Q�[�����p���[�T�X�y���f�b�h�ɂȂ�ꍇ
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

    // TODO: �Q�[�����p���[���W���[���ɂȂ�ꍇ
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_width = max(width, 1);
    m_height = max(height, 1);
	
	DirectX11::Get().CreateResources();
    // TODO: �Q�[���E�B���h�E�̃T�C�Y���ĕύX���ꂽ�ꍇ
}

// �v���p�e�B Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: �C�ӂ̃f�t�H���g�E�B���h�E�T�C�Y�ɕύX����(�ŏ��T�C�Y��320x200) 
    width = 800;
    height = 600;
}

// Exit�w���p�[�֐�
void ExitGame() 
{
	PostQuitMessage(0);
}
