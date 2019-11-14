// Game.h

#pragma once
#ifndef GAME_DEFINED
#define GAME_DEFINED

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <windows.h>
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <Effects.h>
#include <Model.h>
#include "Keyboard.h"
//#include "Mouse.h"

#include "StepTimer.h"
#include "Window.h"
#include "DirectX11.h"

class Window;

// ゲームループを提供するゲームクラス
class Game
{
public:
	
	// スプライトバッチを取得する
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}
	// スプライトフォントを取得する
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}

	// ゲームループを実行する
	MSG Run() noexcept;

	// コンストラクタ
    Game(const int width, const int height) noexcept;
    // 初期化をおこなう
    virtual void Initialize() noexcept;
	// リソースを生成する
	virtual void CreateResources() noexcept;
	// 更新する
	virtual void Update(const DX::StepTimer& timer) noexcept;
	// 画面をクリアする
	virtual void Clear() noexcept;
	// シーンを描画する
	virtual void Render(const DX::StepTimer& timer) noexcept;
	// バックバッファをスクリーンに送る
    virtual void Present() noexcept;
	// 後始末をする
	virtual void Finalize() noexcept;

    // メッセージ
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ 
    void GetDefaultSize(int& width, int& height) const;

private:
	// 出力幅
	int m_width;
	// 出力高
	int m_height;
	// ウィンドウハンドル
	HWND m_hWnd;
	// ウィンドウ表示フラグ
	int m_nCmdShow;
	// インスタンスハンドル
	HINSTANCE m_hInstance;

	// タイマー
    DX::StepTimer m_timer;
	// 機能レベル
    D3D_FEATURE_LEVEL m_featureLevel;
	// ウィンドウ
	std::unique_ptr<Window> m_window;
	
	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// DirectX11クラスのインスタンス
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// GAME_DEFINED

