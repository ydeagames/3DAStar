#ifndef CUBEMAP_DEFINED
#define CUBEMAP_DEFINED

#include <d3d11.h>
#include <memory>
#include <wrl.h>
#include <wrl/client.h>
#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <Effects.h>

#include "DirectX11.h"
#include "Scene.h"
#include "ITiledMap.h"
#include "TiledMap.h"


class Scene;

class CubeMap
{
public:
	// コンストラクタ
	CubeMap(Scene* scene) noexcept;
	// 初期化する
	void Initialize(const std::string& mapFile) noexcept;
	// 更新する
	void Update(const DX::StepTimer& timer) noexcept;
	// 描画する
	void Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept;
	// 後始末をする
	void Finalize() noexcept;

private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_grass;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_corkBoard;
	// ベイシックエフェクト
	DirectX::BasicEffect* m_basicEffect;
	// インプットレイアウト
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	ID3D11InputLayout* m_inputLayout;

	// キューブモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
	
	// Sceneオブジェクトへのポインタ
	Scene* m_scene;
	// マップ
	std::unique_ptr<ITiledMap> m_tiledMap;

	// DirectX11クラスのインスタンスを取得する
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// CUBEMAP_DEFINED

