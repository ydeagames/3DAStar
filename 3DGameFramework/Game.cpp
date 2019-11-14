#include "Game.h"

void ExitGame();

// コンストラクタ
Game::Game(int width, int height) noexcept
	: m_hWnd(0), m_width(width), m_height(height), m_featureLevel(D3D_FEATURE_LEVEL_9_1) 
{
	// スタートアップ情報
	STARTUPINFO si{};
	// インスタンスハンドルを取得する
	m_hInstance = ::GetModuleHandle(NULL);

	// STARTUPINFO構造体を取得する
	::GetStartupInfo(&si);
	m_nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	// Windowオブジェクトを生成する
	m_window = make_unique<Window>(m_hInstance, m_nCmdShow);
}

// ゲームリソースを初期化する
void Game::Initialize() noexcept
{
	// Windowオブジェクトを初期化する
	m_window->Initialize(m_width, m_height);
	// Windowオブジェクトの生成後にウィンドウハンドルを取得する
	m_hWnd = m_window->GetHWnd();

	// DirectXの初期化のためウィンドウハンドルを設定する
	m_directX.SetHWnd(m_hWnd);
	// DirectXの初期化のためウィンドウ幅を設定する
	m_directX.SetWidth(m_width);
	// DirectXの初期化のためウィンドウ高を設定する
	m_directX.SetHeight(m_height);

	// デバイスを生成する
	m_directX.CreateDevice();
	// リソースを生成する
	m_directX.CreateResources();

    // TODO: デフォルト変数timestepモード以外のものが必要な場合タイマー設定を変更する
	// 例: 60FPS固定タイムステップ更新ロジックに対しては以下を呼び出す
    
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60.0);

	// SpriteBatchオブジェクトを生成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_directX.GetContext().Get());
	// SpriteFontオブジェクトを生成する
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_directX.GetDevice().Get(), L"Arial.spritefont");
}

// リソースを生成する
void Game::CreateResources() noexcept
{
}

// ゲームループを実行する
MSG Game::Run() noexcept
{
	// メッセージ
	MSG msg = {};

	// Gameオブジェクトを初期化する
	Initialize();
	// ウィンドウを表示する
	m_window->ShowWindow();
	// リソースを生成する
	CreateResources();

	// ゲームループ
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ゲームを更新する
			m_timer.Tick([&]() { Update(m_timer); });
			// ゲームシーンを描画する
			Render(m_timer);
		}
	}
	// Gameオブジェクトの後始末をする
	Finalize();
	return msg;
}

// ゲームを更新する
void Game::Update(const DX::StepTimer& timer) noexcept
{
}

// 後始末をする
void Game::Finalize() noexcept
{
	// Fontオブジェクトを解放する
	m_spriteFont.reset();
	// SpriteBatchオブジェクトを解放する
	m_spriteBatch.reset();

	// DirectX11 Graphicsオブジェクトを解放する
	DirectX11::Dispose();
	// Windowオブジェクトを解放する
	m_window.reset();
}

// シーンを描画する
void Game::Render(const DX::StepTimer& timer) noexcept
{
}

// バックバッファをクリアする
void Game::Clear() noexcept
{	// レンダーターゲットビューをクリアする
	m_directX.GetContext()->ClearRenderTargetView(m_directX.GetRenderTargetView().Get(), DirectX::Colors::DarkSlateGray);
	// デプスステンシルビューをクリアする
	m_directX.GetContext()->ClearDepthStencilView(m_directX.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// レンダータッゲートを設定する
	m_directX.GetContext()->OMSetRenderTargets(1, m_directX.GetRenderTargetView().GetAddressOf(), m_directX.GetDepthStencilView().Get());
    // ビューポートを設定する
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	m_directX.GetContext()->RSSetViewports(1, &viewport);
}

// バックバッファをスクリーンに送る 
void Game::Present() noexcept
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.

	// DirectX11クラスのインスタンスを取得する
	DirectX11& directX = DirectX11::Get();
	HRESULT hr = directX.GetSwapChain()->Present(1, 0);

    // デバイスがリセットされた場合レンダラを再初期化する必要がある 
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) 
		directX.OnDeviceLost();
    else 
        DX::ThrowIfFailed(hr);
}

// メッセージハンドラ
void Game::OnActivated()
{
	// TODO: ゲームがアクティブなウィンドウになる場合
}

void Game::OnDeactivated()
{
    // TODO: ゲームがバックグラウンドウィンドウになる場合 
}

void Game::OnSuspending()
{
    // TODO: ゲームがパワーサスペンデッドになる場合
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

    // TODO: ゲームがパワーレジュームになる場合
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_width = max(width, 1);
    m_height = max(height, 1);
	
	DirectX11::Get().CreateResources();
    // TODO: ゲームウィンドウのサイズが再変更された場合
}

// プロパティ Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: 任意のデフォルトウィンドウサイズに変更する(最小サイズは320x200) 
    width = 800;
    height = 600;
}

// Exitヘルパー関数
void ExitGame() 
{
	PostQuitMessage(0);
}
