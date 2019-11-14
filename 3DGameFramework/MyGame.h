#pragma once
#ifndef MYGAME_DEFINED
#define MYGAME_DEFINED

#include "Window.h"
#include "MousePrim.h"
#include "Game.h"
#include "DebugCamera.h"
#include "Scene.h"

class MyGame : public Game
{
public:
	// コンストラクタ
	MyGame(int width, int height) noexcept;
	// Gameオブジェクトを初期する
	void Initialize() noexcept override;
	// リソースを生成する
	void CreateResources()noexcept override;
	// ゲームを更新する
	void Update(const DX::StepTimer& timer) noexcept override;
	// ゲームを描画する
	void Render(const DX::StepTimer& timer) noexcept override;
	// 終了処理をおこなう
	void Finalize() noexcept override;

private:
	// 幅
	int m_width;
	// 高さ
	int m_height;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// スプライトバッチ
	DirectX::SpriteBatch* m_spriteBatch;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;
	// シーン
	std::shared_ptr<Scene> m_scene;

	// DirectX11クラスのインスタンスを取得する
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// MYGAME_DEFINED