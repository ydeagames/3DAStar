#pragma once
#ifndef SCENE_DEFINED
#define SCENE_DEFINED

#include <d3d11.h>
#include <Effects.h>
#include "DirectX11.h"
#include <memory.h>
#include <Keyboard.h>
#include "Enemy.h"
#include "CubeMap.h"
#include "Position.h"

class MyGame;
class CubeMap;

class Scene 
{
public:
	// マップファイルを取得する
	string GetMapFile() const
	{
		return m_mapFile;
	}
	// ベイシックエフェクト
	DirectX::BasicEffect* GetBasicEffect() 
	{
		return m_basicEffect.get();
	}
	// インプットレイアウト
	ID3D11InputLayout* GetInputLayout()
	{
		return m_inputLayout.Get();
	}
	// コンストラクタ
	Scene() noexcept;
	// 初期化する
	void Initialize() noexcept;
	// 更新する
	void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept;
	// 描画する
	void Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept;
	// 後始末をする
	void Finalize() noexcept;

private:
	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// キーボードステートトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projection;
	// ベイシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// キューブマップ
	std::unique_ptr<CubeMap> m_cubeMap;
	// 敵
	std::unique_ptr<Enemy> m_enemy;
	// マップファイル
	std::string m_mapFile;

	// DirectX11クラスのインスタンスを取得する
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// SCENE_DEFINED