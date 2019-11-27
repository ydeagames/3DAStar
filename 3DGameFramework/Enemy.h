#ifndef ENEMY_DEFINED
#define ENEMY_DEFINED

#include <d3d11.h>
#include <SimpleMath.h>

#include "Position.h"
#include "IObject.h"
#include "IState.h"
#include "Idling.h"
#include "Searching.h"
#include "Chasing.h"

#include "Scene.h"

class Idling;
class Searching;
class Chasing;
class Scene;

class Enemy : public IObject
{
public:
	// Idling状態を取得する
	Idling* GetIdlingState() const 
	{
		return m_idlingState.get();
	}

	// Searching状態を取得する
	Searching* GetSearchingState() const
	{
		return m_searchingState.get();
	}

	// Chasing状態を取得する
	Chasing* GetChasingState() const
	{
		return m_chasingState.get();
	}

	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetVectorPosition() const
	{
		return m_position;
	}

	// 位置を設定する
	void SetVectorPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}
	
	// 開始位置を取得する
	Position GetStartPosition() const
	{
		return m_startPosition;
	}
	
	// 開始位置を設定する
	void SetStartPosition(const Position& startPosition)
	{
		m_startPosition = startPosition;
	}

	// 終了位置を取得する
	Position GetEndPosition() const
	{
		return m_endPosition;
	}

	// 終了位置を設定する
	void SetEndPosition(const Position& endPosition)
	{
		m_endPosition = endPosition;
	}
	
	// 最短経路を取得する
	std::vector<Position> GetRoute() const
	{
		return m_route;
	}
	
	// コンストラクタ
	Enemy(Scene* scene) noexcept;
	// 初期化する
	int Initialize() noexcept override;
	// 更新する
	int Update(const DX::StepTimer& timer) noexcept override;
	// 描画する
	void Render(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection) noexcept override;
	// 後始末をする
	void Finalize() noexcept override;
	// 状態を変更する
	void ChangeState(IState* state);

private:
	// アイドル状態
	std::unique_ptr<Idling> m_idlingState;
	// 探索状態
	std::unique_ptr<Searching> m_searchingState;
	// 追跡状態
	std::unique_ptr<Chasing> m_chasingState;
	// 現在の状態
	IState* m_currentState;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// マップ
	ITiledMap* m_tiledMap;

	// 開始位置
	Position m_startPosition;
	// 終了位置
	Position m_endPosition;
	// 最短経路
	std::vector<Position> m_route;

	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 位置
	DirectX::SimpleMath::Vector3 m_position_end;
	// 移動行列
	DirectX::SimpleMath::Matrix m_translation;
	// モデルオブジェクト
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitive;
	// ベイシックエフェクト
	DirectX::BasicEffect* m_basicEffect;
	// インプットレイアウト
	ID3D11InputLayout* m_inputLayout;
	// Sceneオブジェクトへのポインタ
	Scene* m_scene;

	// DirectX11クラスのインスタンスを取得する
	DirectX11& m_directX = DirectX11::Get();
};

#endif // ENEMY_DEFINED

